// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/Interface/WeaponInterface.h"
//#include "Weapon/Core/BaseClass/BaseWeapon.h"
#include "Engine/DataTable.h"
#include "ACWeaponManager.generated.h"

USTRUCT(BlueprintType)
struct FWeaponFactoryParams
{
	GENERATED_USTRUCT_BODY()


};

USTRUCT(BlueprintType)
struct FWeaponDataTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName WeaponID{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABaseWeapon> WeaponClass;
};

UCLASS(BlueprintType, Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNRANKHUNTER_API UACWeaponManager : public UActorComponent, public IWeaponInterface
{
	GENERATED_BODY()

public:
	UACWeaponManager();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon Manager")
	void InitializeBlueprint();

public:
	IWeaponInterface* GetEquippedWeapon();

	// Create and add a weapon to the slot position.
	UFUNCTION(BlueprintCallable, Category = "Weapon Manager")
	bool AddWeaponToSlot(int32 SlotIndex, FName WeaponID, FWeaponFactoryParams Params, bool bForceAdd = false, bool bImmediatelyEquip = false);

	// Removes the weapon at the specified slot index and returns the result.
	// Use the bDestroyInstance parameter to choose whether to completely destroy the instance or just remove it from the manager.
	UFUNCTION(BlueprintCallable, Category = "Weapon Manager")
	bool RemoveWeaponFromSlot(class ABaseWeapon*& OutWeaponInstance, int32 SlotIndex, bool bDestroyInstance = true);

	// Change the currently active weapon.
	// Does not activate if attempting to activate an already active weapon.
	UFUNCTION(BlueprintCallable, Category = "Weapon Manager")
	void SelectWeaponSlot(int32 SlotIndex);

	// Always change the currently active weapon.
	UFUNCTION(BlueprintCallable, Category = "Weapon Manager")
	void ForceEquipWeaponSlot(int32 SlotIndex);

	// Returns the currently equipped weapon index.
	UFUNCTION(BlueprintCallable, Category = "Weapon Manager")
	int32 GetEquippedSlot();

	// Returns the index of the inactive weapon slot.
	UFUNCTION(BlueprintCallable, Category = "Weapon Manager")
	int32 GetSubSlot();


private:
	// Returns the weapon blueprint class for the given weapon ID.
	UClass* GetWeaponBlueprintClass(FName WeaponID) const;

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

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon Manager Setting")
	UDataTable* WeaponTable;

protected:
	const int ContainerSize{ 2 };

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon Manager")
	TArray<class ABaseWeapon*> WeaponArray{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon Manager")
	class ABaseWeapon* EquippedWeapon{};

	UPROPERTY()
	int32 EquippedSlot{ -1 };
};
