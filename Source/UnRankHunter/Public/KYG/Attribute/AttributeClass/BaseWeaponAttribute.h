// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Weapon/Structure/WeaponStructure.h"
#include "Weapon/Core/BaseClass/BaseWeapon.h"
#include "BaseWeaponAttribute.generated.h"

USTRUCT()
struct FWeaponAttributeStat 
{
	GENERATED_BODY()
};

/**
 * 
 */
UCLASS()
class UNRANKHUNTER_API UBaseWeaponAttribute : public UObject
{
	GENERATED_BODY()
	
public:
	//virtual void OnAttributeAttached(ABaseWeapon* ParentWeapon) = 0;
	//virtual void OnAttributeDetached(ABaseWeapon* ParentWeapon) = 0;

	//virtual void OnAttributeEnabled() = 0;
	//virtual void OnAttributeDisabled() = 0;


};
