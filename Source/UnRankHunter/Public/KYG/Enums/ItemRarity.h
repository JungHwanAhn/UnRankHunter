// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Common = 0,
	Uncommon,
	Rare,
	Unique,
	Legend
};

class UNRANKHUNTER_API ItemRarity
{
public:
	ItemRarity();
	~ItemRarity();
};
