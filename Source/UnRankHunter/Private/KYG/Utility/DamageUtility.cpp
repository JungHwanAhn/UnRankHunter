// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Utility/DamageUtility.h"

float UDamageUtility::CalculateWeapon(const ABaseWeapon* const BaseWeapon, const AActor* const HitTarget, const float Damage, const FDamageContext& DamageContext)
{
	float FinalDamage = Damage;

	// Apply bonus damage by enemy type.
	if (HitTarget->ActorHasTag("Boss"))
	{

	}
	else if (HitTarget->ActorHasTag("Elite"))
	{

	}
	else if (HitTarget->ActorHasTag("Common"))
	{

	}

	// Apply bonus damage by attack type.

	// Apply critical increase damage.

	return FinalDamage;
}