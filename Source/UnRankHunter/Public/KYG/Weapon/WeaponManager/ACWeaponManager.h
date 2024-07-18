// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/Interface/WeaponInterface.h"
#include "ACWeaponManager.generated.h"

struct FWeaponFactoryParams
{

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNRANKHUNTER_API UACWeaponManager : public UActorComponent, public IWeaponInterface
{
	GENERATED_BODY()

public:
	UACWeaponManager();

public:
	IWeaponInterface* GetEquiptedWeapon();

	// Create and add a weapon to the slot position.
	bool AddWeaponToSlot(int SlotIndex, FName WeaponID, FWeaponFactoryParams Params, bool bForceAdd = false);

private:

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

protected:
	int ContainerSize{ 2 };

private:
	UPROPERTY()
	TArray<IWeaponInterface*> WeaponArray{};

	IWeaponInterface* EquiptedWeapon{};
};
