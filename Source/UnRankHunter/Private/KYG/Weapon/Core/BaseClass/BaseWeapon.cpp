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

	SetupModule();
	LoadParameter();
	SetupWeaponProperties();

	// Initialize weapon variables.
	auto AttachParent = GetAttachParentActor();

	if (AttachParent)
	{
		CameraPositionComponent = AttachParent->FindComponentByTag<USceneComponent>("Main Camera");
	}
}

void ABaseWeapon::SetupModule()
{
	// Find module components.
	TriggerModule = GetComponentByClass<UACBaseTriggerModule>();
	ShooterModule = GetComponentByClass<UACBaseShooterModule>();
	ReloadModule = GetComponentByClass<UACBaseReloadModule>();
	ScopeModule = GetComponentByClass<UACBaseScopeModule>();

	// Generate base module. (not implemented)
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

	// Setup.
	TriggerModule->OnFireNotified.AddDynamic(this, &ABaseWeapon::ReceiveFireNotify);
}

void ABaseWeapon::LoadParameter()
{
	// Load parameter data.
	FString ParamDTPath = "DataTable'/Game/01_Core/KYG/Weapon/DataTable/KYG_DT_WeaponParamTable.KYG_DT_WeaponParamTable'";
	UDataTable* ParamTable = LoadObject<UDataTable>(nullptr, *ParamDTPath);
	if (ParamTable != nullptr)
	{
		FWeaponParameter* ParamRow = ParamTable->FindRow<FWeaponParameter>(WeaponID, "");

		if (ParamRow != nullptr)
		{
			WeaponParameter = *ParamRow;
			UE_LOG(LogTemp, Log, TEXT("[BaseWeapon] Load weapon parameter process is SUCCESS"));
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
}

void ABaseWeapon::SetupWeaponProperties()
{
	RemainAmmoCount = GetFinalStat().AmmoCapacity;
}

void ABaseWeapon::ConstructWeapon(const FWeaponConstructParams& Params)
{
	InitializeWeaponAttribute(Params.AttributeIDs);
	SetupWeaponProperties();
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

#pragma region [Stat System]
const FWeaponParameter& ABaseWeapon::GetFinalStat()
{
	if (bIsStatRecent == false)
	{
		UpdateFinalStat();
	}

	return FinalStat;
}

void ABaseWeapon::UpdateFinalStat()
{
	FWeaponParameter NewFinalStat = WeaponParameter;
	FWeaponBonusStat Bonus = GetTotalBonusStat();

	// Calculate Parameter + BonusStat.
	//NewFinalStat.Damage *= 1.0f + Bonus.AllDamageUp;	// No apply AllDamageUp to damage stat. AllDamageUp will apply on final damage calculation.

	NewFinalStat.AmmoCapacity = FMath::FloorToInt32(NewFinalStat.AmmoCapacity * (1.0f + Bonus.AddAmmoMultiple)) + Bonus.AddAmmoCount; // baseCap * MultipleCap + AddCap

	NewFinalStat.ElementalStrength *= (1.0f + Bonus.ElementalStrengthUp);
	NewFinalStat.ReloadRate *= (1.0f + Bonus.ReloadSpeedUp);
	NewFinalStat.RapidRate *= (1.0f + Bonus.FireSpeedUp);
	NewFinalStat.BulletSize *= (1.0f + Bonus.AttackRange);
	NewFinalStat.EffectiveDistance *= (1.0f + Bonus.EffecientDistanceUp);

	NewFinalStat.AccuracyRatio *= 1.0f + Bonus.AccuracyUp;
	NewFinalStat.CritDamage += Bonus.CritDamageUp;
	// End calculate.

	FinalStat = MoveTemp(NewFinalStat);

	bIsStatRecent = true;
}

FWeaponBonusStat ABaseWeapon::GetTotalBonusStat()
{
	return DynamicStat + StaticStat;
}

void ABaseWeapon::UpdateStaticStat()
{
	FWeaponBonusStat Bonus{};
	for (auto Attribute : AttributeArray)
	{
		Attribute->ApplyBonusStat(Bonus);
	}
	StaticStat = MoveTemp(Bonus);

	bIsStatRecent = false;
}

void ABaseWeapon::ModifyDynamicStat(const FBonusStatModifier Callback)
{
	Callback.ExecuteIfBound(DynamicStat);

	bIsStatRecent = false;
}

void ABaseWeapon::InitializeWeaponAttribute(TArray<FName> AttributeIDs)
{
	// Clear all attributes.
	for (auto attribute : AttributeArray)
	{
		attribute->DisableAttribute();
	}

	AttributeArray.Empty();

	// Create new attributes.
	for (auto id : AttributeIDs)
	{
		AddAttribute(id);
	}

	UpdateStaticStat();
}

TSubclassOf<UBaseWeaponAttribute> ABaseWeapon::FindAttributeClass(FName ID)
{
	// !FUNCTION IS NOT IMPLEMENTED NOW!
	FString AttributeDTPath = "DataTable'/Game/01_Core/KYG/WeaponAttribute/DataTable/KYG_DT_AttributeTable.KYG_DT_AttributeTable'";
	UDataTable* AttributeDT = LoadObject<UDataTable>(nullptr, *AttributeDTPath);
	if (AttributeDT == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("[BaseWeapon] Finding Attribute Class is FAILURE! Data table is missing."));
		return nullptr;
	}

	FWeaponAttributeRow* Row = AttributeDT->FindRow<FWeaponAttributeRow>(ID, nullptr);

	if (Row == nullptr || Row->AttributeClass == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("[BaseWeapon] Finding Attribute Class is FAILURE! Data table row is empty."));
		return nullptr;
	}

	return Row->AttributeClass;
}

void ABaseWeapon::AddAttribute(FName AttributeID)
{
	// Find class.
	auto AttributeClass = FindAttributeClass(AttributeID);

	if (ensure(AttributeClass == nullptr))
	{
		UE_LOG(LogTemp, Warning, TEXT("[BaseWeapon] Add attribute is FAILURE! Can't find attribute class of '%s' id."), *AttributeID.ToString());
		return;
	}

	// Construct instance.
	UBaseWeaponAttribute* AttributeInstance = NewObject<UBaseWeaponAttribute>(this, AttributeClass);

	if (ensure(AttributeInstance == nullptr))
	{
		UE_LOG(LogTemp, Warning, TEXT("[BaseWeapon] Add attribute is FAILURE! Fail to instantiate new attribute instance."), *AttributeID.ToString());
		return;
	}

	AttributeArray.Emplace(AttributeInstance);

	// Initialize instance.
	AttributeInstance->InitializeOnCreated(this);
}
#pragma endregion


const float ABaseWeapon::CalculateDamage(const AActor* Target, ABaseWeapon* Weapon, const FWeaponDamageContext& Context)
{
	const FWeaponParameter& BaseStat = Weapon->GetFinalStat();
	FWeaponBonusStat BonusStat = Weapon->GetTotalBonusStat();

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