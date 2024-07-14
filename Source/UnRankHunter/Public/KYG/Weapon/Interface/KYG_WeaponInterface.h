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


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Interface", meta = (ForceAsFunction))
	bool CanFire();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Interface", meta = (ForceAsFunction))
	bool CanReload();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Interface", meta = (ForceAsFunction))
	bool CanZoom();


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Interface", meta = (ForceAsFunction))
	bool IsFiring();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Interface", meta = (ForceAsFunction))
	bool IsReloading();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Interface", meta = (ForceAsFunction))
	bool IsZooming();


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon", meta = (ForceAsFunction))
	void SetWeaponEnabled(bool bNewEnabled);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon", meta = (ForceAsFunction))
	bool GetWeaponEnabled();

	// Deprecated Function. Use SetupWeaponAttachment instead of this.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon", meta = (ForceAsFunction, DeprecatedFunction))
	void AttachWeaponToSocket(AActor* Player, USkeletalMeshComponent* Mesh, FName SocketName = "");

	// Setup and initialize weapon attachment.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon", meta = (ForceAsFunction))
	void SetupWeaponAttachment(AActor* Owner, USceneComponent* AttachParent, FName SocketName = "");


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Properties", meta = (ForceAsFunction))
	void GetFinalStat(FKYG_WeaponStat& Output);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Properties", meta = (ForceAsFunction))
	int GetRemainAmmoCount();
};
