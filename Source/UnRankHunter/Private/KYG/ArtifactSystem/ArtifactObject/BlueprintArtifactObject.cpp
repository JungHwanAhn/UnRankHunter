// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/ArtifactSystem/ArtifactObject/BlueprintArtifactObject.h"
#include "Weapon/WeaponManager/ACWeaponManager.h"

void UBlueprintArtifactObject::EnableArtifact()
{
	WeaponManager = ArtifactOwner->GetComponentByClass<UACWeaponManager>();

	EnableArtifact_Blueprint();
}

void UBlueprintArtifactObject::DisableArtifect()
{
	DisableArtifect_Blueprint();
}

void UBlueprintArtifactObject::Tick(float DeltaTime)
{
	Tick_Blueprint(DeltaTime);
}

void UBlueprintArtifactObject::ModifyWeaponStat_Blueprint(UPARAM(ref) const FWeaponBonusStat& RefStat)
{
	TempStat = RefStat;
	FWeaponStatSetterCallback Callback{};
	Callback.BindDynamic(this, &UBlueprintArtifactObject::ModifyStatCallback);
	WeaponManager->ModifyDynamicStat(Callback);
}

void UBlueprintArtifactObject::ModifyStatCallback(FWeaponBonusStat& WeaponStat)
{
	WeaponStat = WeaponStat + TempStat;
}

