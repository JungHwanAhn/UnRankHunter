// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Weapon/Core/BaseClass/BaseWeapon.h"
#include "WeaponHudInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UWeaponHudInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNRANKHUNTER_API IWeaponHudInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Weapon HUD")
	void SetUIEnabled(bool bEnabled);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Weapon HUD")
	void SetupBaseWeapon(class ABaseWeapon* Weapon);
};
