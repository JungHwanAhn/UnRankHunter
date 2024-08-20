// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/ArtifactSystem/Tester/ArtifactTestActor.h"
#include "Weapon/WeaponManager/ACWeaponManager.h"

// Sets default values
AArtifactTestActor::AArtifactTestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AArtifactTestActor::BeginPlay()
{
	Super::BeginPlay();

	if (Target == nullptr)
		return;
	auto Manager = Target->GetComponentByClass<UACWeaponManager>();
	if (Manager)
	{
		FWeaponStatSetterCallback Modifier;
		Modifier.BindDynamic(this, &AArtifactTestActor::TestModifier);
		Manager->ModifyDynamicStat(Modifier);
	}
}

// Called every frame
void AArtifactTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArtifactTestActor::TestModifier(FWeaponBonusStat& Stat)
{
	Stat.AddAmmoCount += 100;
}

