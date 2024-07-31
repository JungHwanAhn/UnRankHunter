// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KYG/Weapon/WeaponModule/Base/ACBaseWeaponModule.h"
#include "ACBaseScopeModule.generated.h"

/**
 *
 */
UCLASS(Abstract, BlueprintType, Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNRANKHUNTER_API UACBaseScopeModule : public UACBaseWeaponModule
{
	GENERATED_BODY()

public:
	UACBaseScopeModule();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon Module|Scope Module")
	bool CanZoom()
	{
		return bCanZoom;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon Module|Scope Module")
	bool IsZooming()
	{
		return bIsZooming;
	}

	UFUNCTION(BlueprintCallable, Category = "Weapon Module|Scope Module")
	bool SetZoomInput(bool bInput);

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon Module|Scope Module")
	void OnScopeBegin();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon Module|Scope Module")
	void OnScopeEnd();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon Module|Scope Module")
	void OnScopeTick();

protected:

protected:
	bool bInputState{ false };

	bool bIsZooming{ false };

	bool bCanZoom{ true };

};
