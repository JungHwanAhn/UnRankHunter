// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/Structure/WeaponStructure.h"

WeaponStructure::WeaponStructure()
{
}

WeaponStructure::~WeaponStructure()
{
}

FWeaponBonusStat FWeaponBonusStat::operator+(const FWeaponBonusStat& Other)
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

FWeaponBonusStat FWeaponBonusStat::operator-(const FWeaponBonusStat& Other)
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
