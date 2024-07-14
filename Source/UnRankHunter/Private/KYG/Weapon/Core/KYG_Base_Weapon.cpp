// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/Core/KYG_Base_Weapon.h"

// Sets default values
AKYG_Base_Weapon::AKYG_Base_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKYG_Base_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKYG_Base_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

