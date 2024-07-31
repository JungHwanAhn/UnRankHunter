// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KYG/Attribute/AttributeClass/BaseWeaponAttribute.h"
#include "BlueprintableWeaponAttribute.generated.h"

/**
 *
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class UNRANKHUNTER_API UBlueprintableWeaponAttribute : public UBaseWeaponAttribute
{
	GENERATED_BODY()

protected:
	virtual void OnAttributeEnabled() override;
	virtual void OnAttributeDisabled() override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon Attribute")
	void OnAttributeEnabled_Blueprint();

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon Attribute")
	void OnAttributeDisabled_Blueprint();
};
