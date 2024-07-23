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
		TriggerModule->SetTriggerInput(bInput);
	}
}

void ABaseWeapon::SetReloadInput_Implementation(bool bInput)
{
	if(ReloadModule)
	{
		ReloadModule->SetReloadInput(bInput);
	}
}

void ABaseWeapon::SetZoomInput_Implementation(bool bInput)
{
	if(ScopeModule)
	{
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
		&& RemainAmmoCount < GetMaxAmmoCapacity();

	return false;
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

	CameraPositionComponent = WeaponOwner->FindComponentByTag<USceneComponent>("Main Camera");
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
	return AmmoCapacity;
}

bool ABaseWeapon::ConsumeAmmo(int32& OutRemainAmmo, int32& OutReduceAmmo, int32 Cost, bool bFailOnLess)
{
	OutRemainAmmo = RemainAmmoCount;
	OutReduceAmmo = 0;

	if (bIsInfiniteAmmo)
	{
		return true;
	}

	int32 FinalAmmo = RemainAmmoCount - Cost;

	if (FinalAmmo < 0)
	{
		if (bFailOnLess)
		{
			return false;
		}

		OutReduceAmmo = Cost + RemainAmmoCount;
		RemainAmmoCount = 0;
		OutRemainAmmo = 0;
		return OutReduceAmmo > 0;	// Return ammo is decrease?
	}
	else
	{
		RemainAmmoCount = FinalAmmo;
		OutRemainAmmo = RemainAmmoCount;
		OutReduceAmmo = Cost;
		return true;
	}
}

USceneComponent* ABaseWeapon::GetCameraPosition()
{
	return CameraPositionComponent;
}

USceneComponent* ABaseWeapon::GetMuzzlePosition()
{
	return MuzzlePositionComponent;
}


int32 ABaseWeapon::GetMaxAmmoCapacity()
{
	FWeaponParameter Param;
	FWeaponStat FinStat;

	Execute_GetWeaonParameter(this, Param);
	Execute_GetWeaponFinalStat(this, FinStat);

	int Result = Param.AmmoCapacity * FinStat.AmmoCapacityMultiplier + FinStat.AmmoCapacityAdditive;

	return Result;
}

float ABaseWeapon::GetDamageAmount(EDamageEffectType DamageType, float Distance, FName HitTag, EDamageElementalType Type, bool bIsCritical)
{
	FWeaponParameter Param;
	FWeaponStat FinStat;

	Execute_GetWeaonParameter(this, Param);
	Execute_GetWeaponFinalStat(this, FinStat);

	// Base Damage = Default Damage * Multiplier
	float BaseDamage = Param.BaseDamage *
		(DamageType == EDamageEffectType::Explosion ? Param.ExplosionDamageMultiplier :
			DamageType == EDamageEffectType::Bullet ? Param.BulletDamageMultiplier :
			DamageType == EDamageEffectType::Special ? Param.DamageMultiplier0 :
			Param.DamageMultiplier1);

	float BonusByDamageType =
		DamageType == EDamageEffectType::Explosion ? FinStat.ExplosionDamage :
		DamageType == EDamageEffectType::Bullet ? FinStat.ProjectileDamage :
		DamageType == EDamageEffectType::Special ? FinStat.SpecialDamage :
		0.0f;

	float BonusByElementalType =
		Type == EDamageElementalType::Basic ? FinStat.BasicDamage :
		Type == EDamageElementalType::Bleeding ? FinStat.BleedingElementalDamage :
		Type == EDamageElementalType::Frozen ? FinStat.FrozenElementalDamage :
		Type == EDamageElementalType::Lightning ? FinStat.LightningElementalDamage :
		0.0f;

	float BonusByHitTarget =
		HitTag == "Common" ? FinStat.CommonDamage :
		HitTag == "Elite" ? FinStat.EliteDamage :
		HitTag == "Boss" ? FinStat.BossDamage :
		0.0f;

	// Sum all bonus damages.
	float AllBonus = FinStat.AllDamage + BonusByDamageType + BonusByElementalType + BonusByHitTarget;

	// Calculate critical damage.
	float CritDamage = bIsCritical ? FinStat.CritDamage : 1.0f;

	float FinalDamage = BaseDamage * (1.0f + AllBonus) * CritDamage;

	return FinalDamage;

}
