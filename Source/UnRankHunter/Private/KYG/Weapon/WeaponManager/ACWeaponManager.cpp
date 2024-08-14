// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/WeaponManager/ACWeaponManager.h"
#include "Weapon/Interface/WeaponInterface.h"
#include "Weapon/Core/BaseClass/BaseWeapon.h"
#include "Kismet/GameplayStatics.h"

UACWeaponManager::UACWeaponManager()
{
	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_WepTb(TEXT("DataTable'/Game/01_Core/KYG/Weapon/DataTable/KYG_DT_WeaponTable.KYG_DT_WeaponTable'"));
	if (DT_WepTb.Succeeded())
	{
		WeaponTable = DT_WepTb.Object;
	}
}

void UACWeaponManager::BeginPlay()
{
	Super::BeginPlay();

	WeaponArray.Init(nullptr, ContainerSize);

	//UE_LOG(LogTemp, Warning, TEXT("Weapon Manager Begin Play : %d"), WeaponArray.Num());

	InitializeBlueprint();
}

IWeaponInterface* UACWeaponManager::GetEquippedWeapon()
{
	return EquippedWeapon;
}

bool UACWeaponManager::AddWeaponToSlot(int32 SlotIndex, FName WeaponID, FWeaponConstructParams Params, bool bForceAdd, bool bImmediatelyEquip)
{
	// Exception handling: Index out of range.
	if (!WeaponArray.IsValidIndex(SlotIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponManager: Fail to add weapon. %d is out of range index. Container size is %d."), SlotIndex, WeaponArray.Num());
		return false;
	}

	// If slot already contains weapon, return fail.
	if (bForceAdd == false && WeaponArray[SlotIndex] != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponManager: Fail to add weapon. Trying to add weapon to assigned slot."));
		return false;
	}

	auto WeaponBlueprintClass = GetWeaponBlueprintClass(WeaponID);

	// Exception handling: No weapon class exists for the given WeaponID.
	if (WeaponBlueprintClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponManager: Fail to add weapon. %s is invalid id."), *WeaponID.ToString());
		return false;
	}

	// Create weapon instance.
	ABaseWeapon* WeaponInst{};

	auto TempObj = GetWorld()->SpawnActor(WeaponBlueprintClass);
	WeaponInst = Cast<ABaseWeapon>(TempObj);

	if (WeaponInst == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponManager: Fail to add weapon. Weapon is not ABaseWeapon"));
		return false;
	}

	// Destroy the previous weapon instance in the slot.
	if (WeaponArray[SlotIndex] != nullptr)
	{
		// Remove Weapon Logic.
		ABaseWeapon* RemoveWeapon{};
		RemoveWeaponFromSlot(RemoveWeapon, SlotIndex, true);
	}

	WeaponArray[SlotIndex] = WeaponInst;

	// Initialize the instance.
	IWeaponInterface::Execute_SetupWeaponAttachment(WeaponInst->_getUObject(), GetOwner());
	WeaponInst->ForceSetWeaponEnable(false);
	WeaponInst->ConstructWeapon(Params);

	UE_LOG(LogTemp, Log, TEXT("WeaponManager: Success to add weapon. SUCCESS Add weapon to slot."));

	if (bImmediatelyEquip)
	{
		SelectWeaponSlot(SlotIndex);
	}

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
		SelectWeaponSlot(GetSubSlot());
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

void UACWeaponManager::SelectWeaponSlot(int32 SlotIndex)
{
	if (WeaponArray.IsValidIndex(SlotIndex) == false && SlotIndex != -1)
	{
		UE_LOG(LogTemp, Log, TEXT("Weapon Manager: Fail to select weapon slot. %d is out of range."), SlotIndex);
		return;
	}

	if (EquippedSlot == SlotIndex)
	{
		UE_LOG(LogTemp, Log, TEXT("Weapon Manager: Pass to select weapon slot. %d is already selected."), SlotIndex);
		return;
	}

	ABaseWeapon* Previous = nullptr;	// Event parameter, weapon instance of before changing.

	// If manager equip any weapon, Disable this weapon.
	if (WeaponArray.IsValidIndex(GetEquippedSlot()) == true && WeaponArray[GetEquippedSlot()] != nullptr)
	{
		Previous = WeaponArray[GetEquippedSlot()];

		IWeaponInterface::Execute_SetWeaponEnabled(Previous, false);
	}

	if (SlotIndex == -1)	// -1 is code of disarming weapon.
	{
		EquippedSlot = -1;
		EquippedWeapon = nullptr;

		UE_LOG(LogTemp, Log, TEXT("Weapon Manager: Success to disarm."), EquippedSlot, SlotIndex);
	}
	else
	{
		auto NewWeaponInst = WeaponArray[SlotIndex];
		if (NewWeaponInst)
		{
			IWeaponInterface::Execute_SetWeaponEnabled(NewWeaponInst, true);

			UE_LOG(LogTemp, Log, TEXT("Weapon Manager: Success to select weapon slot from %d to %d"), EquippedSlot, SlotIndex);

			// Change controlled weapon.
			EquippedSlot = SlotIndex;
			EquippedWeapon = NewWeaponInst;
		}
	}

	// Invoke change event.
	OnWeaponChanged.Broadcast(this, Previous, EquippedWeapon);
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
	// If Table is invalid, return fail.
	if (!WeaponTable)
	{
		return nullptr;
	}

	auto Row = WeaponTable->FindRow<FWeaponDataTableRow>(WeaponID, TEXT(""));

	if (Row == nullptr)
		return nullptr;

	return Row->WeaponClass;
}

#pragma region [Weapon Interface Implementation]

void UACWeaponManager::SetFireInput_Implementation(bool bInput)
{
	if (EquippedWeapon && IWeaponInterface::Execute_CanFire(this))
	{
		IWeaponInterface::Execute_SetFireInput(EquippedWeapon->_getUObject(), bInput);
	}
}

void UACWeaponManager::SetReloadInput_Implementation(bool bInput)
{
	if (EquippedWeapon && IWeaponInterface::Execute_CanReload(this))
	{
		IWeaponInterface::Execute_SetReloadInput(EquippedWeapon->_getUObject(), bInput);
	}
}

void UACWeaponManager::SetZoomInput_Implementation(bool bInput)
{
	if (EquippedWeapon && IWeaponInterface::Execute_CanZoom(this))
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

void UACWeaponManager::CancelWeaponAction_Implementation(EWeaponAbortSelection AbortSelection)
{
	if (EquippedWeapon)
	{
		IWeaponInterface::Execute_CancelWeaponAction(EquippedWeapon, AbortSelection);
	}
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

EWeaponType UACWeaponManager::GetWeaponType_Implementation()
{
	return EquippedWeapon ? IWeaponInterface::Execute_GetWeaponType(EquippedWeapon->_getUObject()) : EWeaponType::None;
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

