// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/WeaponModule/Base/ACBaseShooterModule.h"


void UACBaseShooterModule::ShotBullet_Implementation(float TriggerRate) {}

const FTransform& UACBaseShooterModule::GetShooterOrigin(EWeaponShooterOrigin Type)
{
	if (OwnerWeapon == nullptr)
		return FTransform{};



	return 
}
