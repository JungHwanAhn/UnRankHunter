// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyStatProvider.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyStatProvider : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNRANKHUNTER_API IEnemyStatProvider
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Enemy Stat Provider")
	float GetMoveSpeed();
};
