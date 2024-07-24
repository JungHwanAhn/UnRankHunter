// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KYG/Weapon/WeaponModule/Base/ACBaseWeaponModule.h"
#include "ACBaseReloadModule.generated.h"

/**
 *
 */
UCLASS(Abstract, BlueprintType, Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNRANKHUNTER_API UACBaseReloadModule : public UACBaseWeaponModule
{
	GENERATED_BODY()

public:
	UACBaseReloadModule();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Modules|Reload Module")
	bool CanReload()
	{
		return bCanReload;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Modules|Reload Module")
	bool IsReloading()
	{
		return bIsReloading;
	}

	UFUNCTION(BlueprintCallable, Category = "Modules|Reload Module")
	bool SetReloadInput(bool bInput);

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Modules|Reload Module")
	void OnReloadBegin();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Modules|Reload Module")
	void OnReloadEnd();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Modules|Reload Module")
	void OnReloadTick();

protected:

protected:
	bool bInputState{ false };

	bool bIsReloading{ false };

	bool bCanReload{ true };
};
