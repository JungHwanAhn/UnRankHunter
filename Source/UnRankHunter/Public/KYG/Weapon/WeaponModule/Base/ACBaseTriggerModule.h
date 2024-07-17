// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KYG/Weapon/WeaponModule/Base/ACBaseWeaponModule.h"
#include "Weapon/Interface/TriggerModuleInterface.h"
#include "ACBaseTriggerModule.generated.h"

/**
 * 
 */
UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNRANKHUNTER_API UACBaseTriggerModule : public UACBaseWeaponModule, public ITriggerModuleInterface
{
	GENERATED_BODY()
	
};
