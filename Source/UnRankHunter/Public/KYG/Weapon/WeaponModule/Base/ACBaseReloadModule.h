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
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon Module|Reload Module")
	bool CanReload()
	{
		return bCanReload && !bIsReloading;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon Module|Reload Module")
	bool IsReloading()
	{
		return bIsReloading;
	}

	UFUNCTION(BlueprintCallable, Category = "Weapon Module|Reload Module")
	bool SetReloadInput(bool bInput);

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon Module|Reload Module")
	void OnReloadBegin();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon Module|Reload Module")
	void OnReloadEnd();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon Module|Reload Module")
	void OnReloadTick();

protected:

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Module|Reload Module")
	bool bInputState{ false };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon Module|Reload Module")
	bool bIsReloading{ false };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon Module|Reload Module")
	bool bCanReload{ true };
};
