// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/Interface/WeaponInterface.h"
#include "ACBaseWeaponModule.generated.h"


UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNRANKHUNTER_API UACBaseWeaponModule : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UACBaseWeaponModule();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void GetOwnerWeapon(IWeaponInterface*& IWeaponInterface)
	{
		IWeaponInterface = OwnerWeapon;
	}

protected:
	IWeaponInterface* OwnerWeapon{};
};
