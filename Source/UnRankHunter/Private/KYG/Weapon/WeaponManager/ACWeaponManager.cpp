// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/WeaponManager/ACWeaponManager.h"
#include "Weapon/Interface/WeaponInterface.h"
#include "Kismet/GameplayStatics.h"

UACWeaponManager::UACWeaponManager()
{
	PrimaryComponentTick.bCanEverTick = false;


}

IWeaponInterface* UACWeaponManager::GetEquiptedWeapon()
{
	return EquiptedWeapon;
}

bool UACWeaponManager::AddWeaponToSlot(int SlotIndex, FName WeaponID, FWeaponFactoryParams Params, bool bForceAdd)
{
	if (!WeaponArray.IsValidIndex(SlotIndex))
	{
		return false;
	}

	if (bForceAdd == false && WeaponArray[SlotIndex] != nullptr)
	{
		return false;
	}

	auto WeaponBlueprintClass = GetWeaponBlueprintClass(WeaponID);

	if (!WeaponBlueprintClass)
	{
		return false;
	}

	IWeaponInterface* WeaponInst{};

	auto TempObj = GetWorld()->SpawnActor(WeaponBlueprintClass->GetClass());
	WeaponInst = Cast<IWeaponInterface>(TempObj);

	if (!WeaponInst)
	{
		return false;
	}

	if (WeaponArray[SlotIndex] != nullptr)
	{
		// Remove Weapon Logic.
	}

	WeaponArray[SlotIndex] = WeaponInst;

	USceneComponent* AttachParent = GetOwner()->FindComponentByTag<USceneComponent>("Equip Body");
	FName SocketName = "";

	IWeaponInterface::Execute_SetupWeaponAttachment(WeaponInst->_getUObject(), GetOwner(), AttachParent, SocketName);

	return true;
}

TSubclassOf<IWeaponInterface> UACWeaponManager::GetWeaponBlueprintClass(FName WeaponID) const
{
	UE_LOG(LogTemp, Log, TEXT("%s: Not Implement Function"), __FUNCTION__);
	return nullptr;
}

#pragma region [Weapon Interface Implementation]

void UACWeaponManager::SetFireInput_Implementation(bool bInput)
{
	if (EquiptedWeapon)
	{
		IWeaponInterface::Execute_SetFireInput(EquiptedWeapon->_getUObject(), bInput);
	}
}

void UACWeaponManager::SetReloadInput_Implementation(bool bInput)
{
	if (EquiptedWeapon)
	{
		IWeaponInterface::Execute_SetReloadInput(EquiptedWeapon->_getUObject(), bInput);
	}
}

void UACWeaponManager::SetZoomInput_Implementation(bool bInput)
{
	if (EquiptedWeapon)
	{
		IWeaponInterface::Execute_SetZoomInput(EquiptedWeapon->_getUObject(), bInput);
	}
}

bool UACWeaponManager::CanFire_Implementation()
{
	return EquiptedWeapon ? IWeaponInterface::Execute_CanFire(EquiptedWeapon->_getUObject()) : false;
}

bool UACWeaponManager::CanReload_Implementation()
{
	return EquiptedWeapon ? IWeaponInterface::Execute_CanReload(EquiptedWeapon->_getUObject()) : false;
}

bool UACWeaponManager::CanZoom_Implementation()
{
	return EquiptedWeapon ? IWeaponInterface::Execute_CanZoom(EquiptedWeapon->_getUObject()) : false;
}

bool UACWeaponManager::IsFiring_Implementation()
{
	return EquiptedWeapon ? IWeaponInterface::Execute_IsFiring(EquiptedWeapon->_getUObject()) : false;
}

bool UACWeaponManager::IsReloading_Implementation()
{
	return EquiptedWeapon ? IWeaponInterface::Execute_IsReloading(EquiptedWeapon->_getUObject()) : false;
}

bool UACWeaponManager::IsZooming_Implementation()
{
	return EquiptedWeapon ? IWeaponInterface::Execute_IsZooming(EquiptedWeapon->_getUObject()) : false;
}

void UACWeaponManager::SetWeaponEnabled_Implementation(bool bNewEnabled)
{
	if (EquiptedWeapon)
	{
		IWeaponInterface::Execute_SetWeaponEnabled(EquiptedWeapon->_getUObject(), bNewEnabled);
	}
}

bool UACWeaponManager::GetWeaponEnabled_Implementation()
{
	return EquiptedWeapon ? IWeaponInterface::Execute_GetWeaponEnabled(EquiptedWeapon->_getUObject()) : false;
}

void UACWeaponManager::SetupWeaponAttachment_Implementation(AActor* WeaponOwner, USceneComponent* AttachParent, FName SocketName)
{
	if (EquiptedWeapon)
	{
		IWeaponInterface::Execute_SetupWeaponAttachment(EquiptedWeapon->_getUObject(), WeaponOwner, AttachParent, SocketName);
	}
}

FName UACWeaponManager::GetWeaponID_Implementation()
{
	return EquiptedWeapon ? IWeaponInterface::Execute_GetWeaponID(EquiptedWeapon->_getUObject()) : FName("Invalid");
}

int32 UACWeaponManager::GetRemainAmmoCount_Implementation()
{
	return EquiptedWeapon ? IWeaponInterface::Execute_GetRemainAmmoCount(EquiptedWeapon->_getUObject()) : 0;
}

void UACWeaponManager::RefillAmmoCount_Implementation(int32 AmmoCount)
{
	if (EquiptedWeapon)
	{
		IWeaponInterface::Execute_RefillAmmoCount(EquiptedWeapon->_getUObject(), AmmoCount);
	}
}

#pragma endregion

