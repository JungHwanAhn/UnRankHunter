// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon/Interface/WeaponInterface.h"
#include "Weapon/WeaponModule/Base/ACBaseTriggerModule.h"
#include "Weapon/WeaponModule/Base/ACBaseShooterModule.h"
#include "Weapon/WeaponModule/Base/ACBaseReloadModule.h"
#include "Weapon/WeaponModule/Base/ACBaseScopeModule.h"
#include "Elemental/Enum/ElementalEnums.h"
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

USTRUCT(BlueprintType)
struct FWeaponPrimeStat
{
	GENERATED_BODY()

	// 기본 피해량.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage{ 0.0f };

	// 최대 장탄량.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AmmoCapacity{ 0 };

	// 속성 누적치 배율.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ElementalStrength{ 0.0f };

	// 재장전 속도.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadRate{ 0.0f };

	// 무기의 공격 속도.
	// 차지 무기는 이 수치에 비례해 차지 속도가 증가한다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RapidRate{ 0.0f };

	// 공격의 확장 범위.
	// 일부 히트스캔의 범위, 발사체 오브젝트의 스케일, 폭발 범위 등에 영향을 준다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ImpactArea{ 0.0f };

	// 발사체의 유효범위 확장 배율.
	// 대상이 발사체 오브젝트라면 발사 속도에 영향을 준다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EffectiveRange{ 0.0f };
};


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
	void GenerateBasicModule();


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
	UFUNCTION()
	USceneComponent* GetCameraPosition();

	UFUNCTION()
	USceneComponent* GetMuzzlePosition();

protected:
	// Assign On Begin Play
	UACBaseTriggerModule* TriggerModule{};
	UACBaseShooterModule* ShooterModule{};
	UACBaseReloadModule* ReloadModule{};
	UACBaseScopeModule* ScopeModule{};

protected:
	UPROPERTY()
	USceneComponent* CameraPositionComponent{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UArrowComponent* MuzzlePositionComponent{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AActor* WeaponParent{};

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Option")
	bool bUseWeaponTick{ false };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Option")
	FName WeaponSocket{};

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data|Ammo")
	int32 RemainAmmoCount{ 0 };

	// Test Parameter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data|Ammo")
	int32 AmmoCapacity{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Ammo")
	bool bIsInfiniteAmmo{ false };

private:
	bool bWeaponEnabled{ true };


#pragma region [ WeaponStat ] 
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon Data/Stat")
	const FWeaponPrimeStat& CalculateStat();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Data/Stat")
	FWeaponPrimeStat BaseStat{};
#pragma endregion

	// Events
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "Weapon Event")
	FWeaponFireEvent OnWeaponFireEvent{};
};
