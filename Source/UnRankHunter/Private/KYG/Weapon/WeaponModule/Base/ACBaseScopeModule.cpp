// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/WeaponModule/Base/ACBaseScopeModule.h"

void UACBaseScopeModule::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	OnScopeTick();
}

UACBaseScopeModule::UACBaseScopeModule()
{
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

void UACBaseScopeModule::OnScopeBegin_Implementation()
{
}

void UACBaseScopeModule::OnScopeEnd_Implementation()
{
}

void UACBaseScopeModule::OnScopeTick_Implementation()
{
}