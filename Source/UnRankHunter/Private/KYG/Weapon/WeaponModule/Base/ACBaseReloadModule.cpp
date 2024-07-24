// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/WeaponModule/Base/ACBaseReloadModule.h"

UACBaseReloadModule::UACBaseReloadModule()
{
}

void UACBaseReloadModule::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	OnReloadTick();
}

bool UACBaseReloadModule::SetReloadInput(bool bInput)
{
	if (bInput == bInputState)
	{
		return false;
	}

	bInputState = bInput;

	if (bInputState == true && bCanReload)
	{
		OnReloadBegin();
	}
	else if (bInputState == false)
	{
		OnReloadEnd();
	}

	return true;
}

void UACBaseReloadModule::OnReloadBegin_Implementation()
{
}

void UACBaseReloadModule::OnReloadEnd_Implementation()
{
}

void UACBaseReloadModule::OnReloadTick_Implementation()
{
}