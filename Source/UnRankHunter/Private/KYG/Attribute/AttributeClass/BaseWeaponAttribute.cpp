// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Attribute/AttributeClass/BaseWeaponAttribute.h"

void UBaseWeaponAttribute::ApplyBonusStat(UPARAM(ref) FWeaponBonusStat& InWeapon) const
{
	InWeapon = InWeapon + BonusStat;
}
