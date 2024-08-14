// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon/Interface/WeaponInterface.h"
#include "Elemental/Enum/ElementalEnums.h"
#include "Weapon/Structure/WeaponStructure.h"
#include "BaseWeapon.generated.h"

UENUM(BlueprintType)
enum class EBulletType
{
	None = 0,
	Hitscan,
	Projectile,
	Area,
};

USTRUCT(BlueprintType)
struct FWeaponFireInfo
{
	GENERATED_BODY()

	FWeaponFireInfo() {}
	FWeaponFireInfo(EBulletType BulletType, TArray<AActor*> Bullets, TArray<FHitResult> HitResults, int32 BulletCount)
	{
		this->BulletType = BulletType;
		this->Bullets = Bullets;
		this->HitResults = HitResults;
		this->BulletCount = BulletCount;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBulletType BulletType{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Bullets{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FHitResult> HitResults{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BulletCount{};
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FBonusStatModifier, FWeaponBonusStat&, StatReference);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponFireEvent, ABaseWeapon*, Weapon, UPARAM(ref) const FWeaponFireInfo&, WeaponInfo);

UCLASS(BlueprintType, Blueprintable)
class UNRANKHUNTER_API ABaseWeapon : public AActor, public IWeaponInterface
{
	GENERATED_BODY()

public:
	ABaseWeapon();

protected:
	virtual void BeginPlay() override;

private:
	// Initialize function. Find or create weapon modules.
	void SetupModule();

	// Initialize function. Load weapon data table and apply parameter.
	void LoadParameter();

	// Initialize function. Set up properties that need to be initialized upon creation. (ex. ammo count)
	void SetupWeaponProperties();

public:
	void ConstructWeapon(const FWeaponConstructParams& Params);

private:
	UFUNCTION()
	void ReceiveFireNotify(float Value);

#pragma region [Weapon Interface Implementation]
	// Set start or stop weapon firing.
	virtual void SetFireInput_Implementation(bool bInput) override;

	// Set start or stop weapon reloading.
	virtual void SetReloadInput_Implementation(bool bInput) override;

	// Set start or stop weapon zooming.
	virtual void SetZoomInput_Implementation(bool bInput) override;


	// Return this weapon can fire now.
	// If CanFire() is false, this weapon must not be fired.
	virtual bool CanFire_Implementation() override;

	// Return this weapon can reload now.
	// If CanReload() is false, this weapon must not be reloaded.
	virtual bool CanReload_Implementation() override;

	// Return this weapon can zoom now.
	// If CanZoom() is false, this weapon must not be zoomed.
	virtual bool CanZoom_Implementation() override;


	// Return this weapon is firing now.
	virtual bool IsFiring_Implementation() override;

	// Return this weapon is reloading now.
	virtual bool IsReloading_Implementation() override;

	// Return this weapon is zooming now.
	virtual bool IsZooming_Implementation() override;



	// Function to safely stop the weapon action.
	virtual void CancelWeaponAction_Implementation(EWeaponAbortSelection AbortSelection) override;


	// Set weapon enable state.
	// If you set this property false, this weapon become invisible, no collision, tick disabled.
	virtual void SetWeaponEnabled_Implementation(bool bNewEnabled) override;

	// Return weapon enable state.
	virtual bool GetWeaponEnabled_Implementation() override;

	// Setup and initialize weapon attachment.
	// When this weapon is created, must use this function to initialize.
	virtual void SetupWeaponAttachment_Implementation(AActor* WeaponOwner) override;


	virtual FName GetWeaponID_Implementation() override;

	virtual EWeaponType GetWeaponType_Implementation() override;

	virtual int32 GetRemainAmmoCount_Implementation() override;

	virtual void RefillAmmoCount_Implementation(int32 AmmoCount) override;
#pragma endregion

public:
	// Toggles the weapon's active state.
	// This function always works regardless of the current active state of the weapon, and frequent use may cause performance issues.
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ForceSetWeaponEnable(bool bNewEnabled);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon Data|Ammo")
	int32 GetAmmoCapacity();

	// Decreases the remaining ammo count based on the provided cost.
	// If bFailOnLess is true, no ammo is reduced if there is insufficient ammo.
	// Returns the remaining ammo and the actual ammo cost.
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool ConsumeAmmo(int32& OutRemainAmmo, int32& OutReduceAmmo, int32 Cost, bool bFailOnLess = false);

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	USceneComponent* GetCameraPosition() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	USceneComponent* GetMuzzlePosition() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	USkeletalMeshComponent* GetWeaponMesh() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	const bool GetWeaponSocket(FTransform& OutTransfrom, const FName SocketName) const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	UChildActorComponent* MeshActorComp{};

protected:
	// Assign On Begin Play
	class UACBaseTriggerModule* TriggerModule{};
	class UACBaseShooterModule* ShooterModule{};
	class UACBaseReloadModule* ReloadModule{};
	class UACBaseScopeModule* ScopeModule{};

protected:
	UPROPERTY()
	USceneComponent* CameraPositionComponent{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UArrowComponent* MuzzlePositionComponent{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AActor* WeaponParent{};

public:
	AActor* GetWeaponParent()
	{
		return WeaponParent;
	}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Option")
	bool bUseWeaponTick{ false };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Option")
	FName WeaponSocket{};

protected:
	// [Weapon Datas]

	// Weapon ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName WeaponID;

	// Weapon Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data|Ammo")
	int32 RemainAmmoCount{ 0 };

	// Test Parameter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data|Ammo")
	int32 AmmoCapacity{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Ammo")
	bool bIsInfiniteAmmo{ false };

private:
	bool bWeaponEnabled{ true };


#pragma region [ Elemental ]

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Data|Elemental")
	TEnumAsByte<EElementalType> ElementalType{ EElementalType::None };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Data|Elemental")
	float ElementalValue{ 0.0f };

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon Data|Elemental")
	TEnumAsByte<EElementalType> GetElementalType()
	{
		return ElementalType;
	}

	UFUNCTION(BlueprintCallable, Category = "Weapon Data|Elemental")
	void SetElementalType(TEnumAsByte<EElementalType> Value)
	{
		this->ElementalType = Value;
	}

	UFUNCTION(BlueprintCallable, Category = "Weapon Data|Elemental")
	float GetElementalValue()
	{
		return ElementalValue;
	}

	UFUNCTION(BlueprintCallable, Category = "Weapon Data|Elemental")
	void SetElementalValue(float Value)
	{
		this->ElementalValue = Value;
	}

#pragma endregion
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "Weapon Event")
	FWeaponFireEvent OnWeaponFireEvent{};

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static const float CalculateDamage(const AActor* const Target, ABaseWeapon* Weapon, UPARAM(ref) const FWeaponDamageContext& Context);

#pragma region [ Stat System ]

#pragma region [Method]
public:
	// Get weapon stat of bonus applied.
	// Use this function if you want to get current weapon stat.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon Data|Stat")
	const FWeaponParameter& GetFinalStat();

	// Re-calculate final stat to recent version.
	// If now final stat is not recent version, GetFinalStat() function will call this.
	UFUNCTION(BlueprintCallable, Category = "Weapon Data|Stat")
	void UpdateFinalStat();

	// Return StaticStat + DynamicStat
	FWeaponBonusStat GetTotalBonusStat();

	// Re-calculate static stat(e.g. attribute stat).
	// It calls once on weapon is created.
	// If you want to update static stat immediately, you can use this.
	UFUNCTION(BlueprintCallable, Category = "Weapon Data|Stat")
	void UpdateStaticStat();

	// Modify dynamic stat and change stat-recent state.
	UFUNCTION(BlueprintCallable, Category = "Weapon Data|Stat")
	void ModifyDynamicStat(const FBonusStatModifier Callback);

	UFUNCTION()
	TSubclassOf<UBaseWeaponAttribute> FindAttributeClass(FName ID);

	// Create and initialzie attributes by id.
	// It calls on weapon initialize time.
	UFUNCTION(BlueprintCallable, Category = "Weapon Construct")
	void InitializeWeaponAttribute(TArray<FName> AttributeIDs);

	// Add attribute procedure.
protected:
	UFUNCTION(BlueprintCallable, Category = "Weapon Construct")
	void AddAttribute(FName AttributeID);
#pragma endregion
#pragma region [Field]
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Attributes")
	TArray<class UBaseWeaponAttribute*> AttributeArray{};

private:
	bool bIsStatRecent{ false };

	FWeaponBonusStat StaticStat{};

	FWeaponBonusStat DynamicStat{};

	FWeaponParameter FinalStat{};

	FWeaponParameter WeaponParameter{};

#pragma endregion
#pragma endregion
};