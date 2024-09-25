// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/WeaponModule/Base/ACBaseShooterModule.h"
#include "Weapon/Core/BaseClass/BaseWeapon.h"
#include "Kismet/GameplayStatics.h"

void UACBaseShooterModule::ShotBullet_Implementation(float TriggerRate) {}

UACBaseShooterModule::UACBaseShooterModule()
{
	FString Path = "/Game/01_Core/KYG/ElementalSystem/DamageClass/KYG_DMG_WeaponDamage.KYG_DMG_WeaponDamage_C";
	ConstructorHelpers::FClassFinder<UDamageType> DmgTypeFinder(*Path);
	if (DmgTypeFinder.Succeeded())
	{
		DamageClass = DmgTypeFinder.Class;
	}
}

FTransform UACBaseShooterModule::GetMuzzlePosition()
{
	if (OwnerWeapon == nullptr || OwnerWeapon->GetMuzzlePosition() == nullptr)
		return FTransform{};

	return OwnerWeapon->GetMuzzlePosition()->GetComponentTransform();
}

FTransform UACBaseShooterModule::GetCameraPosition()
{
	if (OwnerWeapon == nullptr || OwnerWeapon->GetCameraPosition() == nullptr)
		return FTransform{};

	FTransform CameraOriginTr = OwnerWeapon->GetCameraPosition()->GetComponentTransform();

	// Calculate a cross position with camera and muzzle point.
	// axis dot v = length of v on the axis.
	FVector MuzzleLoc = GetMuzzlePosition().GetLocation();

	FVector CamForwardVector = CameraOriginTr.GetRotation().GetForwardVector();
	FVector CamToMuzzleVector = MuzzleLoc - CameraOriginTr.GetLocation();

	float Distance = FVector::DotProduct(CamForwardVector, CamToMuzzleVector);
	FVector FinalVector = CamForwardVector * Distance;

	CameraOriginTr.SetLocation(CameraOriginTr.GetLocation() + FinalVector);
	// End calculate.

	return CameraOriginTr;
}

FTransform UACBaseShooterModule::GetSettingPosition()
{
	if (OwnerWeapon == nullptr)
		return FTransform{};

	USceneComponent* PositionComp{};

	switch (WeaponShooterOrigin)
	{
	case EWeaponShooterOrigin::MainCameraCenter:
		PositionComp = OwnerWeapon->GetCameraPosition();
		break;
	case EWeaponShooterOrigin::MuzzlePosition:
		PositionComp = OwnerWeapon->GetMuzzlePosition();
		break;
	default:
		break;
	}

	return PositionComp == nullptr ? FTransform{} : PositionComp->GetComponentTransform();
}

void UACBaseShooterModule::ApplyWeaponDamage(AActor* DamagedActor, float Damage)
{
	AController* OwnerController{ nullptr };

	if (GetOwnerWeapon())
	{
		AActor* WeaponOwner = GetOwnerWeapon()->GetWeaponParent();
		if (WeaponOwner)
		{
			APawn* OwnerAsPawn = Cast<APawn>(WeaponOwner);

			if (OwnerAsPawn)
			{
				OwnerController = OwnerAsPawn->GetController();
			}
		}
	}

	UGameplayStatics::ApplyDamage(DamagedActor, Damage, OwnerController, GetOwnerWeapon(), DamageClass);

	OwnerWeapon->OnWeaponHit.Broadcast(OwnerWeapon, DamagedActor, Damage, FHitResult{});
}

void UACBaseShooterModule::ApplyWeaponPointDamage(AActor* DamagedActor, float Damage, FVector HitFromVector, const FHitResult& HitResult)
{
	AController* OwnerController{ nullptr };

	if (GetOwnerWeapon())
	{
		AActor* WeaponOwner = GetOwnerWeapon()->GetWeaponParent();
		if (WeaponOwner)
		{
			APawn* OwnerAsPawn = Cast<APawn>(WeaponOwner);

			if (OwnerAsPawn)
			{
				OwnerController = OwnerAsPawn->GetController();
			}
		}
	}

	UGameplayStatics::ApplyPointDamage(DamagedActor, Damage, HitFromVector, HitResult, OwnerController, GetOwnerWeapon(), nullptr);

	OwnerWeapon->OnWeaponHit.Broadcast(OwnerWeapon, DamagedActor, Damage, HitResult);
}
