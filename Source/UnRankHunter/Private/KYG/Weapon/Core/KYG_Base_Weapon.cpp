// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/Core/KYG_Base_Weapon.h"

// Sets default values
AKYG_Base_Weapon::AKYG_Base_Weapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AKYG_Base_Weapon::BeginPlay()
{
	Super::BeginPlay();

	WeaponOwner = GetAttachParentActor();
}

// Called every frame
void AKYG_Base_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKYG_Base_Weapon::SetWeaponActive(bool bActive)
{
	bIsActive = bActive;

	// Enable Tick
	SetActorTickEnabled(bActive);

	// Enable Meshes
	TArray<UMeshComponent*> AllMyMeshes;
	GetComponents(AllMyMeshes, true);

	for (auto Mesh : AllMyMeshes)
	{
		Mesh->SetHiddenInGame(!bActive);
	}

	// Enable Collisions
	TArray<UPrimitiveComponent*> AllMyCollisions;
	GetComponents(AllMyCollisions, true);

	for (auto Collision : AllMyCollisions)
	{
		Collision->SetCollisionEnabled(bActive ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
	}
}


void AKYG_Base_Weapon::SetFireInput_Implementation(bool bInput)
{
	if (bInput == bFireInputState)
		return;

	// Update input state.
	bFireInputState = bInput;

	// Check can fire weapon now.
	bool bCanTrigger = Execute_CanFire(this);

	if (bInput && bCanTrigger)
	{
		TriggerModule->Execute_SetTriggerInput(this, true);
	}
	else
	{
		TriggerModule->Execute_SetTriggerInput(this, false);
	}
}

void AKYG_Base_Weapon::SetReloadInput_Implementation(bool bInput)
{
	if (bInput == bReloadInputState)
		return;

	// Update input state.
	bReloadInputState = bInput;

	// Check can fire weapon now.
	bool bCondition = Execute_CanReload(this);

	if (bInput && bCondition)
	{
		ReloadModule->Execute_SetReloadInput(this, true);
	}
	else
	{
		ReloadModule->Execute_SetReloadInput(this, false);
	}
}

void AKYG_Base_Weapon::SetZoomInput_Implementation(bool bInput)
{
}

bool AKYG_Base_Weapon::CanFire_Implementation()
{
	bool bCanFire = !TriggerModule->Execute_IsTriggered(this)
		|| !ReloadModule->Execute_IsReloading(this)
		|| RemainAmmo > 0;

	return bCanFire;
}

bool AKYG_Base_Weapon::CanReload_Implementation()
{
	bool bCanReload = !TriggerModule->Execute_IsTriggered(this)
		|| !ReloadModule->Execute_IsReloading(this)
		|| RemainAmmo > 0;

	return true;
}

bool AKYG_Base_Weapon::CanZoom_Implementation()
{
	return true;
}

bool AKYG_Base_Weapon::IsFiring_Implementation()
{
	return TriggerModule->Execute_IsTriggered(this);
}

bool AKYG_Base_Weapon::IsReloading_Implementation()
{
	return ReloadModule->Execute_IsReloading(this);
}

bool AKYG_Base_Weapon::IsZooming_Implementation()
{
	return false;
}

void AKYG_Base_Weapon::SetWeaponEnabled_Implementation(bool bNewEnabled)
{
	if (bIsActive != bNewEnabled)
	{
		SetWeaponActive(bNewEnabled);
	}
}

bool AKYG_Base_Weapon::GetWeaponEnabled_Implementation()
{
	return bIsActive;
}

//void AKYG_Base_Weapon::AttachWeaponToSocket_Implementation(AActor* Player, USkeletalMeshComponent* Mesh, FName SocketName)
//{
//}

void AKYG_Base_Weapon::SetupWeaponAttachment_Implementation(AActor* NewOwner, USceneComponent* AttachParent, FName SocketName)
{
	AttachToComponent(AttachParent, FAttachmentTransformRules::KeepRelativeTransform, SocketName);
	WeaponOwner = NewOwner;
}

FName AKYG_Base_Weapon::GetWeaponID_Implementation()
{
	return FName();
}

void AKYG_Base_Weapon::GetWeaponParameter_Implementation(FKYG_WeaponParameter& Output)
{
	Output = WeaponParameter;
}

void AKYG_Base_Weapon::GetFinalStat_Implementation(FKYG_WeaponStat& Output)
{
	Output = BasicStat;
}


void AKYG_Base_Weapon::GetBasicStat_Implementation(FKYG_WeaponStat& Output)
{
	Output = BasicStat;
}

const FKYG_WeaponParameter& AKYG_Base_Weapon::GetWeaponParameter() const
{
	return WeaponParameter;
}

const FKYG_WeaponStat& AKYG_Base_Weapon::GetFinalStat() const
{
	return BasicStat;
}

const FKYG_WeaponStat& AKYG_Base_Weapon::GetBasicStat() const
{
	return BasicStat;
}
