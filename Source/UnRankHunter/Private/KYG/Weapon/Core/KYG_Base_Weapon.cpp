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


void AKYG_Base_Weapon::SetFireInput_Implementation(bool bInput)
{
	if (bInput == bFireInputState)
		return;

	// Update input state.
	bFireInputState = bInput;

	// Check can fire weapon now.
	bool bCanTrigger = TriggerModule->CanTrigger();
	bool bIsAmmoEnough = RemainAmmo > 0;

	if (bInput && bCanTrigger && bIsAmmoEnough)
	{
		TriggerModule->SetTriggerInput(true);
	}
	else
	{
		TriggerModule->SetTriggerInput(false);
	}
}

void AKYG_Base_Weapon::SetReloadInput_Implementation(bool bInput)
{
}

void AKYG_Base_Weapon::SetZoomInput_Implementation(bool bInput)
{
}

bool AKYG_Base_Weapon::CanFire_Implementation()
{
	bool bCanFire = !TriggerModule->IsTriggered()
		|| !ReloadModule->IsReloading()
		|| RemainAmmo > 0;

	return bCanFire;
}

bool AKYG_Base_Weapon::CanReload_Implementation()
{
	bool bCanReload = !TriggerModule->IsTriggered()
		|| !ReloadModule->IsReloading()
		|| RemainAmmo > 0;

	return true;
}

bool AKYG_Base_Weapon::CanZoom_Implementation()
{
	return true;
}

