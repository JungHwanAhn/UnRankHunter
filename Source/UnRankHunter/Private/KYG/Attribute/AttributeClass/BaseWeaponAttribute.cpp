// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Attribute/AttributeClass/BaseWeaponAttribute.h"

void UBaseWeaponAttribute::InitializeOnCreated(ABaseWeapon* BaseWeapon)
{
	ParentWeapon = BaseWeapon;
}

void UBaseWeaponAttribute::ApplyBonusStat(UPARAM(ref) FWeaponBonusStat& InWeapon) const
{
	InWeapon = InWeapon + BonusStat;
}

void UBaseWeaponAttribute::EnableAttribute(bool bUpdate)
{
	OnAttributeEnabled();
	if (bUpdate)
		ParentWeapon->UpdateFinalStat();
}

void UBaseWeaponAttribute::DisableAttribute(bool bUpdate)
{
	OnAttributeDisabled();
	if (bUpdate)
		ParentWeapon->UpdateFinalStat();
}
