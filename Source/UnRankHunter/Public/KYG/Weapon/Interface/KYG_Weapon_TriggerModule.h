// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KYG_WeaponModuleInterface.h"
#include "KYG_Weapon_TriggerModule.generated.h"

DECLARE_DYNAMIC_DELEGATE(FKYG_OnWeaponTriggeredDelegate);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UKYG_Weapon_TriggerModule : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class UNRANKHUNTER_API IKYG_Weapon_TriggerModule : public IKYG_WeaponModuleInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Trigger Module")
	void SetTriggerInput(bool bInput);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Trigger Module")
	bool CanTrigger();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Trigger Module")
	bool IsTriggered();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Trigger Module")
	void SetTriggerCallback(FKYG_OnWeaponTriggeredDelegate Callback);
};
