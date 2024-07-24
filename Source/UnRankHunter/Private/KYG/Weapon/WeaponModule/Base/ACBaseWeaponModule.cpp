// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/WeaponModule/Base/ACBaseWeaponModule.h"
#include "Weapon/Core/BaseClass/BaseWeapon.h"

// Sets default values for this component's properties
UACBaseWeaponModule::UACBaseWeaponModule()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}


// Called when the game starts
void UACBaseWeaponModule::BeginPlay()
{
	Super::BeginPlay();

	auto OwnerInst = Cast<ABaseWeapon>(GetOwner());

	OwnerWeapon = OwnerInst;
}

ABaseWeapon* UACBaseWeaponModule::GetOwnerWeapon()
{
	return OwnerWeapon;
}

void UACBaseWeaponModule::OnModuleEnableChanged_Implementation(bool bNewEnabled)
{
}

void UACBaseWeaponModule::SetModuleEnabled(bool bNewEnabled, bool bForce)
{
	if (bForce || bNewEnabled != bIsEnabled)
	{
		bIsEnabled = bNewEnabled;
		OnModuleEnableChanged(bNewEnabled);

		if (bNewEnabled == false)
		{
			SetComponentTickEnabled(false);
			CancelModuleAction();	// cancel to running module actions safety.
		}
	}
}

void UACBaseWeaponModule::CancelModuleAction()
{
	OnModuleActionCancelled();
	OnModuleActionCancelled_Blueprint();
}

void UACBaseWeaponModule::OnModuleActionCancelled()
{
}
