// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnRankHunter/UnRankHunter.h"
#include "UObject/NoExportTypes.h"
#include "Weapon/Structure/WeaponStructure.h"
#include "ArtifactObject.generated.h"


UCLASS(Abstract, BlueprintType)
class UNRANKHUNTER_API UArtifactObject : public UObject
{
	GENERATED_BODY()

public:
	bool bUseTick{ false };


public:
	void InitializeArtifact(AActor* Owner);

	void EnableArtifact() {};

	void DisableArtifect() {};

	virtual void Tick(float DeltaTime) {};

protected:
	AActor* ArtifactOwner;
};
