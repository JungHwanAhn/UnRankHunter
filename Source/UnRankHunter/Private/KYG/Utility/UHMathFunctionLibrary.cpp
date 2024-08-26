// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Utility/UHMathFunctionLibrary.h"

FWeaponBonusStat UUHMathFunctionLibrary::Add_FWeaponBonusStat(const FWeaponBonusStat& a, const FWeaponBonusStat& b)
{
	auto ret = a + b;
	return ret;
}
