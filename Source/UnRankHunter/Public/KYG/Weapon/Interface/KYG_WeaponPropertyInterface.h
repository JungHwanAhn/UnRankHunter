// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Weapon/Structure/KYG_WeaponStuctContainer.h"
#include "KYG_WeaponPropertyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UKYG_WeaponPropertyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class UNRANKHUNTER_API IKYG_WeaponPropertyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Property")
	FName GetWeaponID();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Property")
	void GetWeaponParameter(FKYG_WeaponParameter& Output);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Property")
	void GetFinalStat(FKYG_WeaponStat& Output);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon|Property")
	void GetBasicStat(FKYG_WeaponStat& Output);
};
