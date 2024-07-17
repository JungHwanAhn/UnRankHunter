// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/WeaponModule/Base/ACBaseScopeModule.h"

UACBaseScopeModule::UACBaseScopeModule()
{
	PrimaryComponentTick.bCanEverTick = bUseScopeTick;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UACBaseScopeModule::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	OnScopeTick();
}

bool UACBaseScopeModule::SetZoomInput(bool bInput)
{
	if (bInput == bInputState)
	{
		return false;
	}

	bInputState = bInput;

	if (bInputState == true && bCanZoom)
	{
		OnScopeBegin();
		SetComponentTickEnabled(true);
	}
	else if (bInputState == false)
	{
		OnScopeEnd();
		SetComponentTickEnabled(false);
	}

	return true;
}
