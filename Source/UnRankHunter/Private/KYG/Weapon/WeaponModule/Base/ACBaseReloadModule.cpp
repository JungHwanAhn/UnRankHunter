// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/WeaponModule/Base/ACBaseReloadModule.h"

UACBaseReloadModule::UACBaseReloadModule()
{
	PrimaryComponentTick.bCanEverTick = bUseReloadTick;
	PrimaryComponentTick.bStartWithTickEnabled = false;
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
		SetComponentTickEnabled(true);
	}
	else if (bInputState == false)
	{
		OnReloadEnd();
		SetComponentTickEnabled(false);
	}

	return true;
}