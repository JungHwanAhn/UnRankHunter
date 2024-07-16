// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponDataInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWeaponDataInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNRANKHUNTER_API IWeaponDataInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	FName GetWeaponID();

};
