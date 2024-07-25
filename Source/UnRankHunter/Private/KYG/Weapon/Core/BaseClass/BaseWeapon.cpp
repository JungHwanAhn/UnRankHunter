// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/Core/BaseClass/BaseWeapon.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/WeaponModule/Base/ACBaseTriggerModule.h"
#include "Weapon/WeaponModule/Base/ACBaseWeaponModule.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	auto RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootComponent"));
	SetRootComponent(RootComp);

	MuzzlePositionComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePointComponent"));
	MuzzlePositionComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	TriggerModule = GetComponentByClass<UACBaseTriggerModule>();
	ShooterModule = GetComponentByClass<UACBaseShooterModule>();
	ReloadModule = GetComponentByClass<UACBaseReloadModule>();
	ScopeModule = GetComponentByClass<UACBaseScopeModule>();

	TriggerModule->OnFireNotified.AddDynamic(this, &ABaseWeapon::ReceiveFireNotify);

	auto AttachParent = GetAttachParentActor();

	if (AttachParent)
	{
		CameraPositionComponent = AttachParent->FindComponentByTag<USceneComponent>("Main Camera");
	}

	RemainAmmoCount = GetAmmoCapacity();
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

void ABaseWeapon::ReceiveFireNotify(float Value)
{
	ShooterModule->ShotBullet(Value);

	FWeaponFireInfo Info{};
	OnWeaponFireEvent.Broadcast(this, Info);
}





#pragma region [Weapon Interface Implementation]
// 'IWeaponInterface' U인터페이스 구현부.

void ABaseWeapon::SetFireInput_Implementation(bool bInput)
{
	if (TriggerModule)
	{
		if (bInput == true && !IWeaponInterface::Execute_CanFire(this))
		{
			return;
		}
		TriggerModule->SetTriggerInput(bInput);
	}
}

void ABaseWeapon::SetReloadInput_Implementation(bool bInput)
{
	if (ReloadModule)
	{
		if (bInput == true && !IWeaponInterface::Execute_CanReload(this))
		{
			return;
		}
		ReloadModule->SetReloadInput(bInput);
	}
}

void ABaseWeapon::SetZoomInput_Implementation(bool bInput)
{
	if (ScopeModule)
	{
		if (bInput == true && !IWeaponInterface::Execute_CanZoom(this))
		{
			return;
		}
		ScopeModule->SetZoomInput(bInput);
	}
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
		&& (bIsInfiniteAmmo || RemainAmmoCount > 0);

	return bCanFire;
}

bool ABaseWeapon::CanReload_Implementation()
{
	if (TriggerModule == nullptr || ReloadModule == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: %s Weapon Class Should Contains All Modules Components!"), __FUNCTION__);
		return false;
	}

	bool bCanReload = TriggerModule->IsTrigger() == false
		&& ReloadModule->CanReload()
		&& RemainAmmoCount < GetAmmoCapacity();

	return bCanReload;
}

bool ABaseWeapon::CanZoom_Implementation()
{
	if (ScopeModule == nullptr || ReloadModule == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: %s Weapon Class Should Contains All Modules Components!"), __FUNCTION__);
		return false;
	}

	bool bCanZoom = ReloadModule->IsReloading() == false
		&& ScopeModule->CanZoom();
	return bCanZoom;
}

bool ABaseWeapon::IsFiring_Implementation()
{
	if (TriggerModule == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: %s Weapon Class Should Contains All Modules Components!"), __FUNCTION__);
		return false;
	}

	return TriggerModule->IsTrigger();
}

bool ABaseWeapon::IsReloading_Implementation()
{
	if (ReloadModule == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: %s Weapon Class Should Contains All Modules Components!"), __FUNCTION__);
		return false;
	}

	return ReloadModule->IsReloading();
}

bool ABaseWeapon::IsZooming_Implementation()
{
	if (ScopeModule == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: %s Weapon Class Should Contains All Modules Components!"), __FUNCTION__);
		return false;
	}

	return ScopeModule->IsZooming();
}

void ABaseWeapon::CancelWeaponAction_Implementation(EWeaponAbortSelection AbortSelection)
{
	if (AbortSelection == EWeaponAbortSelection::None)
		return;

	if ((static_cast<uint8>(AbortSelection) & static_cast<uint8>(EWeaponAbortSelection::Fire)))
	{
		TriggerModule->CancelModuleAction();
	}

	if ((static_cast<uint8>(AbortSelection) & static_cast<uint8>(EWeaponAbortSelection::Reload)))
	{
		ReloadModule->CancelModuleAction();
	}

	if ((static_cast<uint8>(AbortSelection) & static_cast<uint8>(EWeaponAbortSelection::Zoom)))
	{
		ScopeModule->CancelModuleAction();
	}
}

void ABaseWeapon::SetWeaponEnabled_Implementation(bool bNewEnabled)
{
	if (bWeaponEnabled == bNewEnabled)
	{
		return;
	}

	ForceSetWeaponEnable(bNewEnabled);

	//bWeaponEnabled = bNewEnabled;
	//SetActorTickEnabled(bNewEnabled && bUseWeaponTick);

	//auto AllComps = GetComponents();
	//for (auto Comp : AllComps)
	//{
	//	Comp->SetActive(bNewEnabled);

	//	auto Col = Cast<UPrimitiveComponent>(Comp);
	//	if (Col != nullptr)
	//	{
	//		Col->SetCollisionEnabled(bNewEnabled ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
	//	}

	//	auto Mesh = Cast<USceneComponent>(Comp);
	//	if (Mesh != nullptr)
	//	{
	//		Mesh->SetVisibility(bNewEnabled);
	//	}

	//	auto Module = Cast<UACBaseWeaponModule>(Comp);
	//	if (Module != nullptr)
	//	{
	//		Module->SetModuleEnabled(bNewEnabled);
	//	}
	//}
}

bool ABaseWeapon::GetWeaponEnabled_Implementation()
{
	return bWeaponEnabled;
}

void ABaseWeapon::SetupWeaponAttachment_Implementation(AActor* WeaponOwner)
{
	// Weapon Detached.
	if (WeaponOwner == nullptr)
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		WeaponParent = nullptr;
		return;
	}

	// Weapon Attached.

	WeaponParent = WeaponOwner;

	auto OwnerCharacter = Cast<ACharacter>(WeaponOwner);

	// Attach to character.
	if (OwnerCharacter != nullptr)
	{
		FName SocketName = WeaponSocket;
		this->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketName);
	}
	// Attach to non-character.
	else
	{
		AttachToActor(WeaponOwner, FAttachmentTransformRules::KeepRelativeTransform);
	}

	CameraPositionComponent = WeaponOwner->FindComponentByTag<USceneComponent>("MainCamera");
}

FName ABaseWeapon::GetWeaponID_Implementation()
{
	// Implementation logic here
	return FName();  // Placeholder return value
}

int32 ABaseWeapon::GetRemainAmmoCount_Implementation()
{
	return RemainAmmoCount;
}

void ABaseWeapon::RefillAmmoCount_Implementation(int32 AmmoCount)
{
	// -1 means infinite ammo.
	if (RemainAmmoCount == -1)
		return;

	RemainAmmoCount = (RemainAmmoCount + AmmoCount);
	RemainAmmoCount = (RemainAmmoCount > GetAmmoCapacity()) ? GetAmmoCapacity() : (RemainAmmoCount < 0) ? 0 : RemainAmmoCount;
}

#pragma endregion


void ABaseWeapon::ForceSetWeaponEnable(bool bNewEnabled)
{
	//UE_LOG(LogTemp, Log, TEXT("Weapon Set Enabled"));

	bWeaponEnabled = bNewEnabled;
	//SetActorTickEnabled(bNewEnabled && bUseWeaponTick);

	auto AllComps = GetComponents();
	for (auto Comp : AllComps)
	{
		//Comp->SetActive(bNewEnabled);

		auto Col = Cast<UPrimitiveComponent>(Comp);
		if (Col != nullptr)
		{
			Col->SetCollisionEnabled(bNewEnabled ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		}

		auto Mesh = Cast<USceneComponent>(Comp);
		if (Mesh != nullptr)
		{
			Mesh->SetVisibility(bNewEnabled);

			//UE_LOG(LogTemp, Log, TEXT("Weapon Set Enabled Is Scene Component %s"), *Mesh->GetName());
		}

		auto Module = Cast<UACBaseWeaponModule>(Comp);
		if (Module != nullptr)
		{
			Module->SetModuleEnabled(bNewEnabled);
		}
	}
}

int32 ABaseWeapon::GetAmmoCapacity()
{
	return GetFinalStat().AmmoCapacity;
}

bool ABaseWeapon::ConsumeAmmo(int32& OutRemainAmmo, int32& OutReduceAmmo, int32 Cost, bool bFailOnLess)
{
	OutRemainAmmo = RemainAmmoCount;
	OutReduceAmmo = Cost;

	if (bIsInfiniteAmmo)
	{
		return true;
	}

	int32 FinalAmmo = RemainAmmoCount - Cost;

	// Amount of remain ammo is bigger than cost.
	if (FinalAmmo >= 0)
	{
		RemainAmmoCount = FinalAmmo;
		OutRemainAmmo = RemainAmmoCount;
		OutReduceAmmo = Cost;
		return true;
	}

	// Ammo is lack, so fail this function.
	if (bFailOnLess)
	{
		OutReduceAmmo = 0;
		return false;
	}

	OutReduceAmmo = RemainAmmoCount;	// Consume all remains ammo.
	RemainAmmoCount = 0;
	OutRemainAmmo = 0;
	return OutReduceAmmo > 0;	// Return ammo is decrease?
}

USceneComponent* ABaseWeapon::GetCameraPosition()
{
	return CameraPositionComponent;
}

USceneComponent* ABaseWeapon::GetMuzzlePosition()
{
	return MuzzlePositionComponent;
}

const FWeaponPrimeStat& ABaseWeapon::GetFinalStat()
{
	// 차후 
	return BaseStat;
}
