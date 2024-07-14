// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KYG_Base_WeaponModule.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNRANKHUNTER_API UKYG_Base_WeaponModule : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UKYG_Base_WeaponModule();
};
