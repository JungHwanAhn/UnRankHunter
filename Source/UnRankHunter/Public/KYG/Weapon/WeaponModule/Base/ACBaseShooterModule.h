// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KYG/Weapon/WeaponModule/Base/ACBaseWeaponModule.h"
#include "ACBaseShooterModule.generated.h"

UENUM()
enum class EWeaponShooterOrigin
{
	MainCameraCenter,
	MuzzlePosition,
};

UCLASS(Abstract, BlueprintType, Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNRANKHUNTER_API UACBaseShooterModule : public UACBaseWeaponModule
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Modules|Shooter Module")
	void ShotBullet(float TriggerRate);

public:
	// Returns the muzzle firing position of the weapon.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Modules|Shooter Module")
	FTransform GetMuzzlePosition();

	// Returns the camera position.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Modules|Shooter Module")
	FTransform GetCameraPosition();

	// Returns the position of either the camera or the muzzle based on the WeaponShooterOrigin setting.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Modules|Shooter Module")
	FTransform GetSettingPosition();


protected:
	// Sets the firing point of the weapon to either the camera or the muzzle.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modules|Shooter Module")
	EWeaponShooterOrigin WeaponShooterOrigin;
};