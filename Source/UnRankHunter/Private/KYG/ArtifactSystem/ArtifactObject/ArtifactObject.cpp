// Fill out your copyright notice in the Description page of Project Settings.

#include "KYG/ArtifactSystem/ArtifactObject/ArtifactObject.h"
#include "PoolSubsystem.h"
#include "Weapon/Core/BaseClass/BaseWeapon.h"

void UArtifactObject::InitializeArtifact(AActor* Owner)
{
	ArtifactOwner = Owner;
	WorldContext = ArtifactOwner->GetWorld();

	EnableArtifact();
}

void UArtifactObject::EnableArtifact()
{
	bIsEnabled = true;
	bIsTickEnabled = bUseTick;
}

void UArtifactObject::DisableArtifect()
{
	bIsEnabled = false;
	bIsTickEnabled = false;
}

bool UArtifactObject::IsActive()
{
	return bIsActive;
}

bool UArtifactObject::IsEnabled()
{
	return bIsEnabled;
}

AActor* UArtifactObject::SpawnActor(TSubclassOf<AActor> ActorClass, FVector Location, FRotator Rotation)
{
	UPoolSubsystem* PoolSubsystem = WorldContext->GetSubsystem<UPoolSubsystem>();
	AActor* OutActor{};
	PoolSubsystem->SpawnFromPool(ActorClass, Location, Rotation, OutActor);
	return OutActor;
}
