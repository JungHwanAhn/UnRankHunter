// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerStatInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPlayerStatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNRANKHUNTER_API IPlayerStatInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Player Stat Interface")
	float GetMaxHealth();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Player Stat Interface")
	float GetHealth();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Player Stat Interface")
	float GetMaxShield();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Player Stat Interface")
	float GetShield();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Player Stat Interface")
	int32 GetLevel();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Player Stat Interface")
	float GetMaxXP();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Player Stat Interface")
	float GetXP();
};
