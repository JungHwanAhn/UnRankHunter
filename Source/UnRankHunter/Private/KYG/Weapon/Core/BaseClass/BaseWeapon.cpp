// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/Core/BaseClass/BaseWeapon.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	TriggerModule = GetComponentByClass<UACBaseTriggerModule>();
	ShooterModule = GetComponentByClass<UACBaseShooterModule>();
	ReloadModule = GetComponentByClass<UACBaseReloadModule>();
	ScopeModule = GetComponentByClass<UACBaseScopeModule>();

	TriggerModule->OnFireNotified.BindDynamic(this, ABaseWeapon::ReceiveFireNotify);
}

void ABaseWeapon::GenerateBasicModule()
{
	if (TriggerModule != nullptr)
	{
		// Create Basic Trigger Module.
	}
	if (ShooterModule != nullptr)
	{
		// Create Basic Shooter Module.
	}
	if (ReloadModule != nullptr)
	{
		// Create Basic Reload Module.
	}
	if (ScopeModule != nullptr)
	{
		// Create Basic Scope Module.
	}
}

void ABaseWeapon::ReceiveFireNotify(float TriggerValue)
{
	ShooterModule->ShotBullet(TriggerValue);
}





#pragma region [Weapon Interface Implementation]
// 'IWeaponInterface' U인터페이스 구현부.

void ABaseWeapon::SetFireInput_Implementation(bool bInput)
{
	TriggerModule->SetTriggerInput(bInput);
}

void ABaseWeapon::SetReloadInput_Implementation(bool bInput)
{
	ReloadModule->SetReloadInput(bInput);
}

void ABaseWeapon::SetZoomInput_Implementation(bool bInput)
{
	ScopeModule->SetZoomInput(bInput);
}

bool ABaseWeapon::CanFire_Implementation()
{
	if (TriggerModule == nullptr || ReloadModule == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: %s Weapon Class Should Contains All Modules Components!"), __FUNCTION__);
		return false;
	}

	bool bCanFire = TriggerModule->CanTrigger()
		&& ReloadModule->IsReloading() == false
		&& RemainAmmoCount > 0;

	return bCanFire;
}

bool ABaseWeapon::CanReload_Implementation()
{
	bool bCanReload = TriggerModule->IsTrigger() == false
		&& ReloadModule->CanReload();

	return false;
}

bool ABaseWeapon::CanZoom_Implementation()
{
	// Implementation logic here
	return false;  // Placeholder return value
}

bool ABaseWeapon::IsFiring_Implementation()
{
	// Implementation logic here
	return false;  // Placeholder return value
}

bool ABaseWeapon::IsReloading_Implementation()
{
	// Implementation logic here
	return false;  // Placeholder return value
}

bool ABaseWeapon::IsZooming_Implementation()
{
	// Implementation logic here
	return false;  // Placeholder return value
}

void ABaseWeapon::SetWeaponEnabled_Implementation(bool bNewEnabled)
{
	// Implementation logic here
}

bool ABaseWeapon::GetWeaponEnabled_Implementation()
{
	// Implementation logic here
	return false;  // Placeholder return value
}

void ABaseWeapon::SetupWeaponAttachment_Implementation(AActor* Owner, USceneComponent* AttachParent, FName SocketName /*= ""*/)
{
	// Implementation logic here
}

FName ABaseWeapon::GetWeaponID_Implementation()
{
	// Implementation logic here
	return FName();  // Placeholder return value
}

int32 ABaseWeapon::GetRemainAmmoCount_Implementation()
{
	// Implementation logic here
	return 0;  // Placeholder return value
}

void ABaseWeapon::RefillAmmoCount_Implementation(int32 AmmoCount)
{
	// Implementation logic here
}

#pragma endregion




int32 ABaseWeapon::GetMaxAmmoCapacity()
{
	FWeaponParameter Param;
	FWeaponStat FinStat;

	Execute_GetWeaonParameter(this, Param);
	Execute_GetWeaponFinalStat(this, FinStat);

	int Result = Param.AmmoCapacity * FinStat.AmmoCapacityMultiplier + FinStat.AmmoCapacityAdditive;

	return Result;
}