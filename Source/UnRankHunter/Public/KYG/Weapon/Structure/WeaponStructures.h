// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponStructures.generated.h"

/**
 * 
 */
class UNRANKHUNTER_API WeaponStructures
{
public:
	WeaponStructures();
	~WeaponStructures();
};


UENUM(BlueprintType)
enum class EScopeType : uint8
{
	None = 0,
	Closer,
	Sniper,
};

UENUM(BlueprintType)
enum class EDamageEffectType : uint8
{
	None = 0,
	Bullet,
	Explosion,
	Special
};

USTRUCT(Atomic, BlueprintType)
struct FWeaponStat
{
	GENERATED_BODY()

	// Bonus damage ratio of all kinds damage.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AllDamage{ 0.0f };

	// Bonus damage ratio of critical damage.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CritDamage{ 0.0f };

	// Bonus ratio of damage that common enemy taken.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CommonDamage{ 0.0f };

	// Bonus ratio of damage that elite enemy taken.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EliteDamage{ 0.0f };

	// Bonus ratio of damage that boss enemy taken.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BossDamage{ 0.0f };


	// Bonus ratio of explosion type damage.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExplosionDamage{ 0.0f };

	// Bonus ratio of projectile type damage.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectileDamage{ 0.0f };

	// Bonus ratio of special type damage.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpecialDamage{ 0.0f };


	// Bonus ratio of no elemental type weapon damage.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BasicDamage{ 0.0f };

	// Bonus ratio of all kinds of elemental type weapon damage.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AllElementalDamage{ 0.0f };

	// Bonus ratio of lightning elemental type weapon damage.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LightningElementalDamage{ 0.0f };

	// Bonus ratio of bleeing elemental type weapon damage.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BleedingElementalDamage{ 0.0f };

	// Bonus ratio of frozen elemental type weapon damage.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FrozenElementalDamage{ 0.0f };

	// Bonus elemental power of lightning type.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LightningElementality{ 0.0f };

	// Bonus elemental power of bleeding type.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BleedingElementality{ 0.0f };

	// Bonus elemental power of frozen type.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FrozenElementality{ 0.0f };



	// Bonus rate of weapon fire speed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate{ 0.0f };

	// Bonus rate of weapon reload speed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadRate{ 0.0f };

	// Additive ammo capacity. (+)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AmmoCapacityAdditive{ 0 };

	// Additive ammo capacity. (*)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AmmoCapacityMultiplier{ 0.0f };



	// Bonus rate of weapon charge.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChargeRate{ 0.0f };

	// Bonus capacity of weapon charge.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChargeCapacity{ 0.0f };

	// Bonus ratio of projectile speed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectileSpeed{ 0.0f };

	// Bonus ratio of effect range. (ex. explosion)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EffectRange{ 0.0f };

	// Bonus ratio of bullet size. (ex. projectile, hitscan)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BulletSize{ 0.0f };
};

USTRUCT(Atomic, BlueprintType)
struct FWeaponParameter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName WeaponID{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDamage{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BulletDamageMultiplier{ 1.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExplosionDamageMultiplier{ 1.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageMultiplier0{ 1.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageMultiplier1{ 1.0f };


	// [Explosion]

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExplosionRange{ 1.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExplosionFalloff{ 1.0f };


	// [Bullet]

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageFalloff{ 1.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BulletSize{ 1.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectileSpeed{ 1.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HitscanDistance{ 1.0f };


	// [Reload]

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AmmoCapacity{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AmmoCost{ 1 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ReloadRefillAmount{ -1 };


	// [Scope]

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TEnumAsByte<EScopeType> ScopeType{ EScopeType::None };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ScopeRatio{ 1.0f };


	// [Trigger]

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TriggerCooldown{ 0.0f };


	// [Charge]

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChargeCapacity{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChargeRate{ 1.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChargeFalloff{ 0.0f };


	// [Rapid]

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireInterval{ 0.0f };


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeaponStat WeaponStat{};
};