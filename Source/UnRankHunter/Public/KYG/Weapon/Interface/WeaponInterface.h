// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponInterface.generated.h"

UENUM(BlueprintType, meta = (Bitflags))
enum class EWeaponAbortSelection : uint8
{
	None = 0,
	Fire = 1 << 0,
	Reload = 1 << 1,
	Zoom = 1 << 2,
	All = 255U
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None,
	Rifle_0,
	Sniper_0,
	MachineGun_0,
	Pistol_0,
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNRANKHUNTER_API IWeaponInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// Set start or stop weapon firing.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Control", meta = (ForceAsFunction))
	void SetFireInput(bool bInput);

	// Set start or stop weapon reloading.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Control", meta = (ForceAsFunction))
	void SetReloadInput(bool bInput);

	// Set start or stop weapon zooming.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Control", meta = (ForceAsFunction))
	void SetZoomInput(bool bInput);


	// Return this weapon can fire now.
	// If CanFire() is false, this weapon must not be fired.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Control", meta = (ForceAsFunction))
	bool CanFire();

	// Return this weapon can reload now.
	// If CanReload() is false, this weapon must not be reloaded.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Control", meta = (ForceAsFunction))
	bool CanReload();

	// Return this weapon can zoom now.
	// If CanZoom() is false, this weapon must not be zoomed.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Control", meta = (ForceAsFunction))
	bool CanZoom();


	// Return this weapon is firing now.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Control", meta = (ForceAsFunction))
	bool IsFiring();

	// Return this weapon is reloading now.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Control", meta = (ForceAsFunction))
	bool IsReloading();

	// Return this weapon is zooming now.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Control", meta = (ForceAsFunction))
	bool IsZooming();


	// Function to safely stop the weapon action.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Control", meta = (ForceAsFunction))
	void CancelWeaponAction(EWeaponAbortSelection AbortSelection);


	// Set weapon enable state.
	// If you set this property false, this weapon become invisible, no collision, tick disabled.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon", meta = (ForceAsFunction))
	void SetWeaponEnabled(bool bNewEnabled);

	// Return weapon enable state.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon", meta = (ForceAsFunction))
	bool GetWeaponEnabled();

	// Setup and initialize weapon attachment.
	// When this weapon is created, must use this function to initialize.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon", meta = (ForceAsFunction))
	void SetupWeaponAttachment(AActor* WeaponOwner);



	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon", meta = (ForceAsFunction))
	FName GetWeaponID();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon", meta = (ForceAsFunction))
	EWeaponType GetWeaponType();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Bullet", meta = (ForceAsFunction))
	int32 GetRemainAmmoCount();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Bullet", meta = (ForceAsFunction))
	void RefillAmmoCount(int32 AmmoCount);

};
