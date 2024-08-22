// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Weapon/Structure/WeaponStructure.h"
#include "UHMathFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UNRANKHUNTER_API UUHMathFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Math")
	static FWeaponBonusStat Add_FWeaponBonusStat(const FWeaponBonusStat& a, const FWeaponBonusStat& b);
};
