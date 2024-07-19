// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/WeaponModule/Base/ACBaseShooterModule.h"
#include "Weapon/Core/BaseClass/BaseWeapon.h"

void UACBaseShooterModule::ShotBullet_Implementation(float TriggerRate) {}

FTransform UACBaseShooterModule::GetMuzzlePosition()
{
	if (OwnerWeapon == nullptr)
		return FTransform{};

	return OwnerWeapon->GetMuzzlePosition()->GetComponentTransform();
}

FTransform UACBaseShooterModule::GetCameraPosition()
{
	if (OwnerWeapon == nullptr)
		return FTransform{};

	return OwnerWeapon->GetCameraPosition()->GetComponentTransform();
}

FTransform UACBaseShooterModule::GetSettingPosition()
{
	if (OwnerWeapon == nullptr)
		return FTransform{};

	return (WeaponShooterOrigin == EWeaponShooterOrigin::MuzzlePosition) ?
		OwnerWeapon->GetMuzzlePosition()->GetComponentTransform() :
		OwnerWeapon->GetCameraPosition()->GetComponentTransform();
}
