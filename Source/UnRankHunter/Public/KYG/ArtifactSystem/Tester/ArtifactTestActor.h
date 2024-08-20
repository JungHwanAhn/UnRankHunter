// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon/Structure/WeaponStructure.h"
#include "ArtifactTestActor.generated.h"

UCLASS()
class UNRANKHUNTER_API AArtifactTestActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AArtifactTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void TestModifier(FWeaponBonusStat& Stat);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Target{};
};
