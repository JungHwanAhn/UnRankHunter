// Fill out your copyright notice in the Description page of Project Settings.

#include "KYG/ArtifactSystem/ArtifactObject/ArtifactObject.h"
#include "Weapon/Core/BaseClass/BaseWeapon.h"

void UArtifactObject::InitializeArtifact(AActor* Owner)
{
	ArtifactOwner = Owner;
}
