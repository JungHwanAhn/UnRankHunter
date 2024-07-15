// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KYG_WeaponInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UKYG_WeaponInterface : public UInterface
{
	GENERATED_BODY()
};

class UNRANKHUNTER_API IKYG_WeaponInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// Set start or stop weapon firing.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Interface", meta = (ForceAsFunction))
	void SetFireInput(bool bInput);

	// Set start or stop weapon reloading.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Interface", meta = (ForceAsFunction))
	void SetReloadInput(bool bInput);

	// Set start or stop weapon zooming.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Interface", meta = (ForceAsFunction))
	void SetZoomInput(bool bInput);


	// Return this weapon can fire now.
	// If CanFire() is false, this weapon must not be fired.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Interface", meta = (ForceAsFunction))
	bool CanFire();

	// Return this weapon can reload now.
	// If CanReload() is false, this weapon must not be reloaded.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Interface", meta = (ForceAsFunction))
	bool CanReload();

	// Return this weapon can zoom now.
	// If CanZoom() is false, this weapon must not be zoomed.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Interface", meta = (ForceAsFunction))
	bool CanZoom();


	// Return this weapon is firing now.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Interface", meta = (ForceAsFunction))
	bool IsFiring();

	// Return this weapon is reloading now.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Interface", meta = (ForceAsFunction))
	bool IsReloading();

	// Return this weapon is zooming now.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Interface", meta = (ForceAsFunction))
	bool IsZooming();


	// Set weapon enable state.
	// If you set this property false, this weapon become invisible, no collision, tick disabled.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon", meta = (ForceAsFunction))
	void SetWeaponEnabled(bool bNewEnabled);

	// Return weapon enable state.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon", meta = (ForceAsFunction))
	bool GetWeaponEnabled();

	// Deprecated Function. Use SetupWeaponAttachment instead of this.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon", meta = (ForceAsFunction, DeprecatedFunction))
	void AttachWeaponToSocket(AActor* Player, USkeletalMeshComponent* Mesh, FName SocketName = "");

	// Setup and initialize weapon attachment.
	// When this weapon is created, must use this function to initialize.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon", meta = (ForceAsFunction))
	void SetupWeaponAttachment(AActor* Owner, USceneComponent* AttachParent, FName SocketName = "");
};
