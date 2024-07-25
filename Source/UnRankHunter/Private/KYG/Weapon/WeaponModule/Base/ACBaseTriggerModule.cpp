// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/WeaponModule/Base/ACBaseTriggerModule.h"

UACBaseTriggerModule::UACBaseTriggerModule()
{
}

void UACBaseTriggerModule::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	OnTriggerTick(DeltaTime);
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
		if (bUseTick)
		{
			SetComponentTickEnabled(true);
		}
	}
	else if (bInputState == false)
	{
		OnTriggerEnd();
		if (bUseTick)
		{
			SetComponentTickEnabled(false);
		}
	}

	return true;
}

void UACBaseTriggerModule::ExecuteTriggerEvent()
{
	if (OnFireNotified.IsBound())
	{
		//UE_LOG(LogTemp, Log, TEXT("Fire!"));
		OnFireNotified.Broadcast(TriggerValue);
	}
	//else
	//{
	//	UE_LOG(LogTemp, Log, TEXT("No Fire!"));
	//}

	//if(OnFireNotified__.ExecuteIfBound(TriggerValue))
	//	UE_LOG(LogTemp, Log, TEXT("Fire!"));
	//else
	//	UE_LOG(LogTemp, Log, TEXT("Fire!"));
}

void UACBaseTriggerModule::OnTriggerBegin_Implementation()
{
}

void UACBaseTriggerModule::OnTriggerEnd_Implementation()
{
}

void UACBaseTriggerModule::OnTriggerTick_Implementation(float DeltaTime)
{
}