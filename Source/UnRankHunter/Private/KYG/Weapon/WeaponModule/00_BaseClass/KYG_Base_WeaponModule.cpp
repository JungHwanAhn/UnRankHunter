// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/WeaponModule/00_BaseClass/KYG_Base_WeaponModule.h"

// Sets default values for this component's properties
UKYG_Base_WeaponModule::UKYG_Base_WeaponModule()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UKYG_Base_WeaponModule::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UKYG_Base_WeaponModule::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

