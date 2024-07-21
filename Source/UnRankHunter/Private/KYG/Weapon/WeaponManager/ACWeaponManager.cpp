// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/WeaponManager/ACWeaponManager.h"
#include "Weapon/Interface/WeaponInterface.h"
#include "Weapon/Core/BaseClass/BaseWeapon.h"
#include "Kismet/GameplayStatics.h"

UACWeaponManager::UACWeaponManager()
{
	PrimaryComponentTick.bCanEverTick = false;


}

IWeaponInterface* UACWeaponManager::GetEquippedWeapon()
{
	return EquippedWeapon;
}

bool UACWeaponManager::AddWeaponToSlot(int32 SlotIndex, FName WeaponID, FWeaponFactoryParams Params, bool bForceAdd)
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

	if (WeaponBlueprintClass)
	{
		return false;
	}

	ABaseWeapon* WeaponInst{};

	auto TempObj = GetWorld()->SpawnActor(WeaponBlueprintClass);
	WeaponInst = Cast<ABaseWeapon>(TempObj);

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

	IWeaponInterface::Execute_SetupWeaponAttachment(WeaponInst->_getUObject(), GetOwner());

	return true;
}

bool UACWeaponManager::RemoveWeaponFromSlot(ABaseWeapon*& OutWeaponInstance, int32 SlotIndex, bool bDestroyInstance)
{
	OutWeaponInstance = nullptr;

	// Escape if index out of range.
	if (WeaponArray.IsValidIndex(SlotIndex) == false)
	{
		return false;
	}

	// Escape if empty slot.
	if (WeaponArray[SlotIndex] == nullptr)
	{
		return false;
	}

	if (SlotIndex == EquippedSlot)
	{
		ChangeWeaponSlot(GetSubSlot());
	}

	auto WeaponInst = WeaponArray[SlotIndex];
	WeaponArray[SlotIndex] = nullptr;

	if (bDestroyInstance)
	{
		WeaponInst->Destroy();
	}
	else
	{
		OutWeaponInstance = WeaponInst;
	}

	return true;
}

void UACWeaponManager::ChangeWeaponSlot(int32 SlotIndex)
{
	if (WeaponArray.IsValidIndex(SlotIndex) == false)
	{
		return;
	}

	if (EquippedSlot == SlotIndex)
	{
		return;
	}

	// If manager equip any weapon, Disable this weapon.
	if (WeaponArray.IsValidIndex(GetEquippedSlot()) == true && WeaponArray[GetEquippedSlot()] != nullptr)
	{
		auto PreWeaponInst = WeaponArray[GetEquippedSlot()];

		IWeaponInterface::Execute_SetWeaponEnabled(PreWeaponInst, false);
	}

	auto NewWeaponInst = WeaponArray[SlotIndex];
	IWeaponInterface::Execute_SetWeaponEnabled(NewWeaponInst, true);

	// Change controlled weapon.
	EquippedSlot = SlotIndex;
	EquippedWeapon = NewWeaponInst;
}

void UACWeaponManager::ForceEquipWeaponSlot(int32 SlotIndex)
{

}

int32 UACWeaponManager::GetEquippedSlot()
{
	return EquippedSlot;
}

int32 UACWeaponManager::GetSubSlot()
{
	return EquippedSlot == 0 ? 1 : 0;
}

UClass* UACWeaponManager::GetWeaponBlueprintClass(FName WeaponID) const
{
	UE_LOG(LogTemp, Log, TEXT("%s: Not Implement Function"), __FUNCTION__);



	return nullptr;
}

#pragma region [Weapon Interface Implementation]

void UACWeaponManager::SetFireInput_Implementation(bool bInput)
{
	if (EquippedWeapon)
	{
		IWeaponInterface::Execute_SetFireInput(EquippedWeapon->_getUObject(), bInput);
	}
}

void UACWeaponManager::SetReloadInput_Implementation(bool bInput)
{
	if (EquippedWeapon)
	{
		IWeaponInterface::Execute_SetReloadInput(EquippedWeapon->_getUObject(), bInput);
	}
}

void UACWeaponManager::SetZoomInput_Implementation(bool bInput)
{
	if (EquippedWeapon)
	{
		IWeaponInterface::Execute_SetZoomInput(EquippedWeapon->_getUObject(), bInput);
	}
}

bool UACWeaponManager::CanFire_Implementation()
{
	return EquippedWeapon ? IWeaponInterface::Execute_CanFire(EquippedWeapon->_getUObject()) : false;
}

bool UACWeaponManager::CanReload_Implementation()
{
	return EquippedWeapon ? IWeaponInterface::Execute_CanReload(EquippedWeapon->_getUObject()) : false;
}

bool UACWeaponManager::CanZoom_Implementation()
{
	return EquippedWeapon ? IWeaponInterface::Execute_CanZoom(EquippedWeapon->_getUObject()) : false;
}

bool UACWeaponManager::IsFiring_Implementation()
{
	return EquippedWeapon ? IWeaponInterface::Execute_IsFiring(EquippedWeapon->_getUObject()) : false;
}

bool UACWeaponManager::IsReloading_Implementation()
{
	return EquippedWeapon ? IWeaponInterface::Execute_IsReloading(EquippedWeapon->_getUObject()) : false;
}

bool UACWeaponManager::IsZooming_Implementation()
{
	return EquippedWeapon ? IWeaponInterface::Execute_IsZooming(EquippedWeapon->_getUObject()) : false;
}

void UACWeaponManager::SetWeaponEnabled_Implementation(bool bNewEnabled)
{
	if (EquippedWeapon)
	{
		IWeaponInterface::Execute_SetWeaponEnabled(EquippedWeapon->_getUObject(), bNewEnabled);
	}
}

bool UACWeaponManager::GetWeaponEnabled_Implementation()
{
	return EquippedWeapon ? IWeaponInterface::Execute_GetWeaponEnabled(EquippedWeapon->_getUObject()) : false;
}

void UACWeaponManager::SetupWeaponAttachment_Implementation(AActor* WeaponOwner)
{
	if (EquippedWeapon)
	{
		IWeaponInterface::Execute_SetupWeaponAttachment(EquippedWeapon->_getUObject(), WeaponOwner);
	}
}

FName UACWeaponManager::GetWeaponID_Implementation()
{
	return EquippedWeapon ? IWeaponInterface::Execute_GetWeaponID(EquippedWeapon->_getUObject()) : FName("Invalid");
}

int32 UACWeaponManager::GetRemainAmmoCount_Implementation()
{
	return EquippedWeapon ? IWeaponInterface::Execute_GetRemainAmmoCount(EquippedWeapon->_getUObject()) : 0;
}

void UACWeaponManager::RefillAmmoCount_Implementation(int32 AmmoCount)
{
	if (EquippedWeapon)
	{
		IWeaponInterface::Execute_RefillAmmoCount(EquippedWeapon->_getUObject(), AmmoCount);
	}
}

#pragma endregion

