// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponStructure.generated.h"

USTRUCT(BlueprintType)
struct FWeaponPrimeStat
{
	GENERATED_BODY()

	// Basic damage.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage{ 0.0f };

	// Maximum ammo capacity.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AmmoCapacity{ 0 };

	// Elemental strength multiplier.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ElementalStrength{ 0.0f };

	// Reload speed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadRate{ 0.0f };

	// Weapon attack speed.
	// For charge weapons, the charging speed increases proportionally to this value.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RapidRate{ 0.0f };

	// Expansion range of the attack.
	// Affects the range of some hitscan, projectile object scale, explosion range, etc.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ImpactArea{ 0.0f };

	// Effective range expansion multiplier.
	// If the target is a projectile object, it affects the projectile speed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EffectiveDistance{ 0.0f };

};

class UNRANKHUNTER_API WeaponStructure
{
public:
	WeaponStructure();
	~WeaponStructure();
};
