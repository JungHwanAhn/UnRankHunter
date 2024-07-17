// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KYG/Weapon/WeaponModule/Base/ACBaseWeaponModule.h"
#include "ACBaseShooterModule.generated.h"

UENUM()
enum class EWeaponShooterOrigin
{
	MainCameraCenter,
	WeaponPoint,
};

UCLASS(Abstract, BlueprintType, Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNRANKHUNTER_API UACBaseShooterModule : public UACBaseWeaponModule
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Modules|Shooter Module")
	void ShotBullet(float TriggerRate);

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Modules|Shooter Module")
	const FTransform& GetShooterOrigin(EWeaponShooterOrigin Type);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modules|Shooter Module")
	EWeaponShooterOrigin WeaponShooterOrigin;
};
