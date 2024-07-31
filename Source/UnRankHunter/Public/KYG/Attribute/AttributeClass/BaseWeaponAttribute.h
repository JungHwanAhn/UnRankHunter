// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Weapon/Structure/WeaponStructure.h"
#include "Weapon/Core/BaseClass/BaseWeapon.h"
#include "BaseWeaponAttribute.generated.h"


/**
 *
 */
UCLASS(Abstract)
class UNRANKHUNTER_API UBaseWeaponAttribute : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnAttributeAttached(ABaseWeapon* ParentWeapon) PURE_VIRTUAL(UBaseWeaponAttribute::OnAttributeAttached, ;);
	virtual void OnAttributeDetached(ABaseWeapon* ParentWeapon) PURE_VIRTUAL(UBaseWeaponAttribute::OnAttributeDetached, ;);

	virtual void OnAttributeEnabled() PURE_VIRTUAL(UBaseWeaponAttribute::OnAttributeEnabled, ;);
	virtual void OnAttributeDisabled() PURE_VIRTUAL(UBaseWeaponAttribute::OnAttributeDisabled, ;);

	UFUNCTION(BlueprintCallable, Category = "Weapon Attribute")
	virtual void ApplyBonusStat(FWeaponBonusStat& InWeapon) const;

protected:
	FName AttributeID;

	FWeaponBonusStat BonusStat;
};
