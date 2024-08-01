// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Attribute/AttributeClass/BlueprintableWeaponAttribute.h"

void UBlueprintableWeaponAttribute::OnAttributeEnabled()
{
	OnAttributeEnabled_Blueprint();
}

void UBlueprintableWeaponAttribute::OnAttributeDisabled()
{
	OnAttributeDisabled_Blueprint();
}
