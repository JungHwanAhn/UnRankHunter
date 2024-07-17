// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KYG/Weapon/WeaponModule/Base/ACBaseWeaponModule.h"
#include "Weapon/Interface/ShooterModuleInterface.h"
#include "ACBaseShooterModule.generated.h"

/**
 * 
 */
UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNRANKHUNTER_API UACBaseShooterModule : public UACBaseWeaponModule, public IShooterModuleInterface
{
	GENERATED_BODY()
	
};
