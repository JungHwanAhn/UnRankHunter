// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/WeaponModule/Base/ACBaseTriggerModule.h"

UACBaseTriggerModule::UACBaseTriggerModule()
{
	PrimaryComponentTick.bCanEverTick = bUseTriggerTick;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UACBaseTriggerModule::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	OnTriggerTick();
}

void UACBaseTriggerModule::BeginPlay()
{
	Super::BeginPlay();
}

bool UACBaseTriggerModule::SetTriggerInput(bool bInput)
{
	if (bInput == bInputState)
	{
		return false;
	}

	bInputState = bInput;

	if (bInputState == true && bCanTrigger)
	{
		OnTriggerBegin();
		if (bUseTriggerTick)
		{
			SetComponentTickEnabled(true);
		}
	}
	else if (bInputState == false)
	{
		OnTriggerEnd();
		if (bUseTriggerTick)
		{
			SetComponentTickEnabled(false);
		}
	}

	return true;
}

void UACBaseTriggerModule::ExecuteTriggerEvent()
{
	OnFireNotified.ExecuteIfBound(TriggerValue);
}

void UACBaseTriggerModule::OnTriggerBegin_Implementation()
{
}

void UACBaseTriggerModule::OnTriggerEnd_Implementation()
{
}

void UACBaseTriggerModule::OnTriggerTick_Implementation()
{
}