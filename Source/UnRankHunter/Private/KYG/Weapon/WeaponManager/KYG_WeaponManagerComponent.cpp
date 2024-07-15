// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/WeaponManager/KYG_WeaponManagerComponent.h"

// Sets default values for this component's properties
UKYG_WeaponManagerComponent::UKYG_WeaponManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UKYG_WeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UKYG_WeaponManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

