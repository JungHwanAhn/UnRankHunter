// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KYG/Weapon/WeaponModule/Base/ACBaseWeaponModule.h"
#include "ACBaseScopeModule.generated.h"

/**
 *
 */
UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNRANKHUNTER_API UACBaseScopeModule : public UACBaseWeaponModule
{
	GENERATED_BODY()

public:
	UACBaseScopeModule();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Modules|Scope Module")
	bool CanZoom()
	{
		return bCanZoom;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Modules|Scope Module")
	bool IsZooming()
	{
		return bIsZooming;
	}

	UFUNCTION(BlueprintCallable, Category = "Modules|Scope Module")
	bool SetZoomInput(bool bInput);

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Modules|Scope Module")
	void OnScopeBegin();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Modules|Scope Module")
	void OnScopeEnd();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Modules|Scope Module")
	void OnScopeTick();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Modules|Scope Module")
	bool bUseScopeTick{ false };

protected:
	bool bInputState{ false };

	bool bIsZooming{ false };

	bool bCanZoom{ true };

};
