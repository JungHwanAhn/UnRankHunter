// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/WeaponModule/Base/ACBaseWeaponModule.h"
#include "Weapon/Core/BaseClass/BaseWeapon.h"

// Sets default values for this component's properties
UACBaseWeaponModule::UACBaseWeaponModule()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
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