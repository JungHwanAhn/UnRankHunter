// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KYG/Weapon/WeaponModule/Base/ACBaseWeaponModule.h"
#include "Weapon/Interface/ReloadModuleInterface.h"
#include "ACBaseReloadModule.generated.h"

/**
 * 
 */
UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNRANKHUNTER_API UACBaseReloadModule : public UACBaseWeaponModule, public IReloadModuleInterface
{
	GENERATED_BODY()
	
};
