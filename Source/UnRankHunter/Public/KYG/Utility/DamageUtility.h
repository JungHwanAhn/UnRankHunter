// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DamageUtility.generated.h"

USTRUCT(BlueprintType)
struct FDamageContext
{
	GENERATED_BODY()

	
};

UCLASS()
class UNRANKHUNTER_API UDamageUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "URH|Weapon Utilities")
	static float CalculateWeapon(const class ABaseWeapon* const BaseWeapon, const AActor* const HitTarget, const float Damage, const FDamageContext& DamageContext);
};
