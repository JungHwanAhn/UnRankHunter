// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerStatStructure.generated.h"

USTRUCT(BlueprintType)
struct FPlayerRewardStat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Shield{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShiledRegen{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Agility{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireSpeed{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SkillDamage{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WeaponDamage{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DashCooldown{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SkillCooldown{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CriticalDamage{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AmmoCapacity{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BossDamage{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Luck{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Greed{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EXP{};
};

class UNRANKHUNTER_API PlayerStatStructure
{
public:
	PlayerStatStructure();
	~PlayerStatStructure();
};
