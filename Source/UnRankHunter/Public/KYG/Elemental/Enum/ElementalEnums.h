// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UNRANKHUNTER_API ElementalEnums
{
public:
	ElementalEnums();
	~ElementalEnums();
};

UENUM()
enum class EDamageElementalType
{
	None = 0,
	Basic,
	Lightning,
	Frozen,
	Bleeding
};