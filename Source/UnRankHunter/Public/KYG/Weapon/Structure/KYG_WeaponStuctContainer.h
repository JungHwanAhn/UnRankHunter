// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KYG_WeaponStuctContainer.generated.h"

class UNRANKHUNTER_API KYG_WeaponStuctContainer
{
public:
};

UENUM()
enum class EScopeType
{
	None = 0,
	Zoom,
	Sniper,
};

USTRUCT(Atomic, BlueprintType)
struct FWeaponStat
{
	GENERATED_USTRUCT_BODY()

	// Bonus damage ratio of all kinds damage.
	float AllDamage{ 0.0f };

	// Bonus damage ratio of critical damage.
	float CritDamage{ 0.0f };

	// Bonus ratio of damage that common enemy taken.
	float CommonDamage{ 0.0f };

	// Bonus ratio of damage that elite enemy taken.
	float EliteDamage{ 0.0f };

	// Bonus ratio of damage that boss enemy taken.
	float BossDamage{ 0.0f };


	// Bonus ratio of explosion type damage.
	float ExplosionDamage{ 0.0f };

	// Bonus ratio of projectile type damage.
	float ProjectileDamage{ 0.0f };

	// Bonus ratio of special type damage.
	float SpecialDamage{ 0.0f };


	// Bonus ratio of no elemental type weapon damage.
	float BasicDamage{ 0.0f };

	// Bonus ratio of all kinds of elemental type weapon damage.
	float AllElementalDamage{ 0.0f };

	// Bonus ratio of lightning elemental type weapon damage.
	float LightningElementalDamage{ 0.0f };

	// Bonus ratio of bleeing elemental type weapon damage.
	float BleedingElementalDamage{ 0.0f };

	// Bonus ratio of frozen elemental type weapon damage.
	float FrozenElementalDamage{ 0.0f };

	// Bonus elemental power of lightning type.
	float LightningElementality{ 0.0f };

	// Bonus elemental power of bleeding type.
	float BleedingElementality{ 0.0f };

	// Bonus elemental power of frozen type.
	float FrozenElementality{ 0.0f };



	// Bonus rate of weapon fire speed.
	float FireRate{ 0.0f };

	// Bonus rate of weapon reload speed.
	float ReloadRate{ 0.0f };

	// Additive ammo capacity. (+)
	int32 AmmoCapacityAdditive{ 0 };

	// Additive ammo capacity. (*)
	float AmmoCapacityMultiplier{ 0.0f };



	// Bonus rate of weapon charge.
	float ChargeRate{ 0.0f };

	// Bonus capacity of weapon charge.
	float ChargeCapacity{ 0.0f };

	// Bonus ratio of projectile speed.
	float ProjectileSpeed{ 0.0f };

	// Bonus ratio of effect range. (ex. explosion)
	float EffectRange{ 0.0f };

	// Bonus ratio of bullet size. (ex. projectile, hitscan)
	float BulletSize{ 0.0f };
};

USTRUCT(Atomic, BlueprintType)
struct FWeaponParameter
{
	GENERATED_USTRUCT_BODY()

	FName WeaponID{};

	float BaseDamage{};

	float BulletDamageMultiplier{ 1.0f };

	float ExplosionDamageMultiplier{ 1.0f };

	float DamageMultiplier0{ 1.0f };

	float DamageMultiplier1{ 1.0f };


	// [Explosion]

	float ExplosionRange{ 1.0f };

	float ExplosionFalloff{ 1.0f };


	// [Bullet]

	float DamageFalloff{ 1.0f };

	float BulletSize{ 1.0f };

	float ProjectileSpeed{ 1.0f };

	float HitscanDistance{ 1.0f };


	// [Reload]

	int32 AmmoCapacity{ 0 };

	int32 AmmoCost{ 1 };

	int32 ReloadRefillAmount{ -1 };


	// [Scope]

	TEnumAsByte<EScopeType> ScopeType{ EScopeType::None };

	float ScopeRatio{ 1.0f };


	// [Trigger]

	float TriggerCooldown{ 0.0f };


	// [Charge]

	float ChargeCapacity{ 0.0f };

	float ChargeRate{ 1.0f };

	float ChargeFalloff{ 0.0f };


	// [Rapid]

	float FireInterval{ 0.0f };


	FWeaponStat WeaponStat{};
};