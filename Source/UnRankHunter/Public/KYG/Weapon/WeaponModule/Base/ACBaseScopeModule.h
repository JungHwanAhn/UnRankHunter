// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KYG/Weapon/WeaponModule/Base/ACBaseWeaponModule.h"
#include "Weapon/Interface/ScopeModuleInterface.h"
#include "ACBaseScopeModule.generated.h"

/**
 * 
 */
UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNRANKHUNTER_API UACBaseScopeModule : public UACBaseWeaponModule, public IScopeModuleInterface
{
	GENERATED_BODY()
	
};
