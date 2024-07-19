// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KYG_WeaponStuctContainer.generated.h"

class UNRANKHUNTER_API KYG_WeaponStuctContainer
{
public:
};

USTRUCT(Atomic, BlueprintType)
struct FKYG_WeaponStat
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName WeaponID{};
};

USTRUCT(Atomic, BlueprintType)
struct FKYG_WeaponParameter
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName WeaponID{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxBulletCount{ -1 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDamage{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageMultiplier1{ 1 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageMultiplier2{ 1 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageMultiplier3{ 1 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageMultiplier4{ 1 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageFalloff{ 1 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ScopeRatio{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadSpeed{ 1 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireSpeed{ 1 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireCooldownDuration{ 0.1f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BulletDistance{ 10000 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BulletSize{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExplosionRange{ 0 };
};