// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/ItemRarity.h"
#include "WeaponStructure.generated.h"

USTRUCT(BlueprintType)
struct FWeaponParameter : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName WeaponID{};

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
	float BulletSize{ 0.0f };

	// Effective range expansion multiplier.
	// If the target is a projectile object, it affects the projectile speed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EffectiveDistance{ 0.0f };

	// The higher this value, the greater the weapon's accuracy.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AccuracyRatio{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CritDamage{ 1.5f };
};

USTRUCT(BlueprintType)
struct FWeaponBonusStat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AllDamageUp{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BossDamageUp{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EliteDamageUp{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CommonEnemyDamageUp{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CritDamageUp{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AddAmmoCount{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AddAmmoMultiple{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireSpeedUp{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadSpeedUp{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRange{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EffecientDistanceUp{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AccuracyUp{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ElementalStrengthUp{ 0.0f };

	FWeaponBonusStat operator+(const FWeaponBonusStat& Other) const;

	FWeaponBonusStat operator-(const FWeaponBonusStat& Other) const;

	FString ToString();
};

UENUM(BlueprintType)
enum class EElementalType : uint8
{
	None = 0,
	Lightning,
	Bleeding,
	Frozen
};

USTRUCT(BlueprintType)
struct FWeaponDamageContext
{
	GENERATED_BODY()

	AActor* DamagedActor{};
	AActor* DamageCause{};
	float Damage{};
	bool bIsCrit{};
};


USTRUCT(BlueprintType)
struct FWeaponConstructParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName WeaponID{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> AttributeIDs{};
};

USTRUCT(BlueprintType)
struct FWeaponAttributeRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName AttributeID{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UBaseWeaponAttribute> AttributeClass{};
};

USTRUCT(BlueprintType, meta=(DisableSplitPin))
struct FVirtualWeaponInstance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName WeaponID{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemRarity> Rarity{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> AttributeIDs{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Price{};
};


DECLARE_DYNAMIC_DELEGATE_OneParam(FWeaponStatSetterCallback, FWeaponBonusStat&, BonusStat);


class UNRANKHUNTER_API WeaponStructure
{
public:
	WeaponStructure();
	~WeaponStructure();
};