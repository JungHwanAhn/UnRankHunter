// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/Weapon/Core/BaseClass/BaseWeapon.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/WeaponModule/Base/ACBaseTriggerModule.h"
#include "Weapon/WeaponModule/Base/ACBaseShooterModule.h"
#include "Weapon/WeaponModule/Base/ACBaseReloadModule.h"
#include "Weapon/WeaponModule/Base/ACBaseScopeModule.h"
#include "Weapon/Structure/WeaponStructure.h"
#include "Attribute/AttributeClass/BaseWeaponAttribute.h"
#include "Engine/DataTable.h"

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

	MeshActorComp = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponMeshActor"));
	MeshActorComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	// Load parameter data.
	FString ParamDTPath = "DataTable'/Game/01_Core/KYG/Weapon/DataTable/KYG_DT_WeaponParamTable.KYG_DT_WeaponParamTable'";
	UDataTable* ParamTable = LoadObject<UDataTable>(nullptr, *ParamDTPath);
	if (ParamTable != nullptr)
	{
		FWeaponParameter* ParamRow = ParamTable->FindRow<FWeaponParameter>(WeaponID, "");

		if (ParamRow != nullptr)
		{
			WeaponParameter = *ParamRow;

			UE_LOG(LogTemp, Warning, TEXT("[BaseWeapon] Test Log_ParamRow->Damage = %.2f"), ParamRow->Damage);
			UE_LOG(LogTemp, Warning, TEXT("[BaseWeapon] Test Log_ParamRow->Damage = %.2f"), WeaponParameter.Damage);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("[BaseWeapon] Can't not found '%s' ID in Weapon Parameter Table."), WeaponID);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[BaseWeapon] Can't not found Weapon Parameter Table asset."));
	}

	// Find module components.
	TriggerModule = GetComponentByClass<UACBaseTriggerModule>();
	ShooterModule = GetComponentByClass<UACBaseShooterModule>();
	ReloadModule = GetComponentByClass<UACBaseReloadModule>();
	ScopeModule = GetComponentByClass<UACBaseScopeModule>();

	TriggerModule->OnFireNotified.AddDynamic(this, &ABaseWeapon::ReceiveFireNotify);


	// Initialize weapon variables.
	auto AttachParent = GetAttachParentActor();

	if (AttachParent)
	{
		CameraPositionComponent = AttachParent->FindComponentByTag<USceneComponent>("Main Camera");
	}

	RemainAmmoCount = GetFinalStat().AmmoCapacity;
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
	return WeaponID;
}

EWeaponType ABaseWeapon::GetWeaponType_Implementation()
{
	return WeaponType;
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
	// (FinalAmmoCapacity) = (Base) * (1 + (Bonus%)) + (Bonus+)
	int32 ApplyMultiple = FMath::FloorToInt32(GetFinalStat().AmmoCapacity * (1.0f + GetFinalBonusStat().AddAmmoMultiple));
	int32 FinalAmmo = ApplyMultiple + GetFinalBonusStat().AddAmmoCount;
	return FinalAmmo;
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

USceneComponent* ABaseWeapon::GetCameraPosition() const
{
	return CameraPositionComponent;
}

USceneComponent* ABaseWeapon::GetMuzzlePosition() const
{
	return MuzzlePositionComponent;
}

USkeletalMeshComponent* ABaseWeapon::GetWeaponMesh() const
{
	if (!MeshActorComp || !MeshActorComp->GetChildActor())
		return nullptr;

	USceneComponent* MeshRootComp = MeshActorComp->GetChildActor()->GetRootComponent();

	USkeletalMeshComponent* MainSkeletal = Cast<USkeletalMeshComponent>(MeshRootComp);

	return MainSkeletal;
}

const bool ABaseWeapon::GetWeaponSocket(FTransform& OutTransfrom, const FName SocketName) const
{
	auto WeaponMesh = GetWeaponMesh();

	if (!WeaponMesh)
	{
		OutTransfrom = FTransform{};
		return false;
	}

	OutTransfrom = WeaponMesh->GetSocketTransform(SocketName);
	return true;
}

const FWeaponParameter ABaseWeapon::GetFinalStat() const
{
	FWeaponParameter FinalStat = WeaponParameter;
	const FWeaponBonusStat& Bonus = GetFinalBonusStat();

	FinalStat.Damage *= 1.0f + Bonus.AllDamageUp;

	FinalStat.AmmoCapacity = FMath::FloorToInt32(FinalStat.AmmoCapacity * (1.0f + Bonus.AddAmmoMultiple)) + Bonus.AddAmmoCount;

	FinalStat.ElementalStrength *= (1.0f + Bonus.ElementalStrengthUp);
	FinalStat.ReloadRate *= (1.0f + Bonus.ReloadSpeedUp);
	FinalStat.RapidRate *= (1.0f + Bonus.FireSpeedUp);
	FinalStat.BulletSize *= (1.0f + Bonus.AttackRange);
	FinalStat.EffectiveDistance *= (1.0f + Bonus.EffecientDistanceUp);

	FinalStat.AccuracyRatio *= 1.0f + Bonus.AccuracyUp;
	FinalStat.CritDamage += Bonus.CritDamageUp;

	return FinalStat;
}

void ABaseWeapon::UpdateFinalStat()
{
	FWeaponParameter FinalStat = WeaponParameter;
	const FWeaponBonusStat& Bonus = GetFinalBonusStat();

	FinalStat.Damage *= 1.0f + Bonus.AllDamageUp;

	FinalStat.AmmoCapacity = FinalStat.AmmoCapacity * Bonus.AddAmmoMultiple * Bonus.AddAmmoCount;

	FinalStat.ElementalStrength *= (1.0f + Bonus.ElementalStrengthUp);
	FinalStat.ReloadRate *= (1.0f + Bonus.ReloadSpeedUp);
	FinalStat.RapidRate *= (1.0f + Bonus.FireSpeedUp);
	FinalStat.BulletSize *= (1.0f + Bonus.AttackRange);
	FinalStat.EffectiveDistance *= (1.0f + Bonus.EffecientDistanceUp);

	FinalStat.AccuracyRatio *= 1.0f + Bonus.AccuracyUp;
	FinalStat.CritDamage += Bonus.CritDamageUp;
}

const FWeaponParameter& ABaseWeapon::GetBaseStat() const
{
	return WeaponParameter;
}

const FWeaponBonusStat& ABaseWeapon::GetFinalBonusStat() const
{
	return BonusStat;
}

FWeaponBonusStat ABaseWeapon::CalculateAttributeStat()
{
	FWeaponBonusStat Result{};

	for (UBaseWeaponAttribute* Attribute : AttributeArray)
	{
		if (Attribute == nullptr)
			continue;

		Attribute->ApplyBonusStat(Result);
	}

	return Result;
}

// Instantiate new attribute class.
void ABaseWeapon::AttachNewAttribute(TSubclassOf<UBaseWeaponAttribute> NewAttributeClass)
{
	if (NewAttributeClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("[BaseWeapon] Attach attribute FAILURE. Attribute class is nullptr."));
	}

	UBaseWeaponAttribute* AttributeInstance = NewObject<UBaseWeaponAttribute>(nullptr, NewAttributeClass);

	AttributeInstance->InitializeOnCreated(this);

	AttributeArray.Add(AttributeInstance);
}

const float ABaseWeapon::CalculateDamage(const AActor* const Target, const ABaseWeapon* const Weapon, const FWeaponDamageContext& Context)
{
	const FWeaponParameter& BaseStat = Weapon->GetFinalStat();
	const FWeaponBonusStat& BonusStat = Weapon->GetFinalBonusStat();

	float BonusByTargetType{ 0.0f };
	if (Target->ActorHasTag("Boss"))
	{
		BonusByTargetType = BonusStat.BossDamageUp;
	}
	else if (Target->ActorHasTag("Elite"))
	{
		BonusByTargetType = BonusStat.EliteDamageUp;
	}
	else if (Target->ActorHasTag("Common"))
	{
		BonusByTargetType = BonusStat.CommonEnemyDamageUp;
	}

	float AllBonus = BonusStat.AllDamageUp + BonusByTargetType;

	float FinalDamage = Context.Damage * (1.0f + AllBonus);

	if (Context.bIsCrit)
	{
		float CritMultiple = BaseStat.CritDamage + BonusStat.CritDamageUp;

		FinalDamage *= CritMultiple;
	}

	// (FinalDamage) = (BaseStat) * (1 + (TotalDamageBonus)) * (BaseCritMultiple + BonusCritMultiple)
	return FinalDamage;
}