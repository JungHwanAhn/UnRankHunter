// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/Structure/WeaponStructure.h"
#include "Attribute/AttributeClass/BaseWeaponAttribute.h"

WeaponStructure::WeaponStructure()
{
}

WeaponStructure::~WeaponStructure()
{
}

FWeaponBonusStat FWeaponBonusStat::operator+(const FWeaponBonusStat& Other) const
{
	FWeaponBonusStat NewStat{};

	NewStat.AllDamageUp = this->AllDamageUp + Other.AllDamageUp;
	NewStat.BossDamageUp = this->BossDamageUp + Other.BossDamageUp;
	NewStat.EliteDamageUp = this->EliteDamageUp + Other.EliteDamageUp;
	NewStat.CommonEnemyDamageUp = this->CommonEnemyDamageUp + Other.CommonEnemyDamageUp;
	NewStat.AddAmmoCount = this->AddAmmoCount + Other.AddAmmoCount;
	NewStat.AddAmmoMultiple = this->AddAmmoMultiple + Other.AddAmmoMultiple;
	NewStat.FireSpeedUp = this->FireSpeedUp + Other.FireSpeedUp;
	NewStat.ReloadSpeedUp = this->ReloadSpeedUp + Other.ReloadSpeedUp;
	NewStat.AttackRange = this->AttackRange + Other.AttackRange;
	NewStat.EffecientDistanceUp = this->EffecientDistanceUp + Other.EffecientDistanceUp;
	NewStat.AccuracyUp = this->AccuracyUp + Other.AccuracyUp;
	NewStat.ElementalStrengthUp = this->ElementalStrengthUp + Other.ElementalStrengthUp;

	return NewStat;
}

FWeaponBonusStat FWeaponBonusStat::operator-(const FWeaponBonusStat& Other) const
{
	FWeaponBonusStat NewStat{};

	NewStat.AllDamageUp = this->AllDamageUp - Other.AllDamageUp;
	NewStat.BossDamageUp = this->BossDamageUp - Other.BossDamageUp;
	NewStat.EliteDamageUp = this->EliteDamageUp - Other.EliteDamageUp;
	NewStat.CommonEnemyDamageUp = this->CommonEnemyDamageUp - Other.CommonEnemyDamageUp;
	NewStat.AddAmmoCount = this->AddAmmoCount - Other.AddAmmoCount;
	NewStat.AddAmmoMultiple = this->AddAmmoMultiple - Other.AddAmmoMultiple;
	NewStat.FireSpeedUp = this->FireSpeedUp - Other.FireSpeedUp;
	NewStat.ReloadSpeedUp = this->ReloadSpeedUp - Other.ReloadSpeedUp;
	NewStat.AttackRange = this->AttackRange - Other.AttackRange;
	NewStat.EffecientDistanceUp = this->EffecientDistanceUp - Other.EffecientDistanceUp;
	NewStat.AccuracyUp = this->AccuracyUp - Other.AccuracyUp;
	NewStat.ElementalStrengthUp = this->ElementalStrengthUp - Other.ElementalStrengthUp;

	return NewStat;
}

FString FWeaponBonusStat::ToString()
{
	FString str;
	str.Append(TEXT("{\n"));
	str.Appendf(TEXT("  AllDamageUp = %.2f,\n"), this->AllDamageUp);
	str.Appendf(TEXT("  BossDamageUp = %.2f,\n"), this->BossDamageUp);
	str.Appendf(TEXT("  EliteDamageUp = %.2f,\n"), this->EliteDamageUp);
	str.Appendf(TEXT("  CommonEnemyDamageUp = %.2f,\n"), this->CommonEnemyDamageUp);
	str.Appendf(TEXT("  CritDamageUp = %.2f,\n"), this->CritDamageUp);
	str.Appendf(TEXT("  AddAmmoCount = %d,\n"), this->AddAmmoCount);
	str.Appendf(TEXT("  AddAmmoMultiple = %.2f,\n"), this->AddAmmoMultiple);
	str.Appendf(TEXT("  FireSpeedUp = %.2f,\n"), this->FireSpeedUp);
	str.Appendf(TEXT("  ReloadSpeedUp = %.2f,\n"), this->ReloadSpeedUp);
	str.Appendf(TEXT("  AttackRange = %.2f,\n"), this->AttackRange);
	str.Appendf(TEXT("  EffecientDistanceUp = %.2f,\n"), this->EffecientDistanceUp);
	str.Appendf(TEXT("  AccuracyUp = %.2f,\n"), this->AccuracyUp);
	str.Appendf(TEXT("  ElementalStrengthUp = %.2f\n"), this->ElementalStrengthUp);
	str.Append(TEXT("}"));

	return str;
}