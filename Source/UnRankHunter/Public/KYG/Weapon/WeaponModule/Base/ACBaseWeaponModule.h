// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACBaseWeaponModule.generated.h"


UCLASS(Abstract, BlueprintType, Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
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
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon Module")
	class ABaseWeapon* GetOwnerWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon Module")
	void SetModuleEnabled(bool bNewEnabled, bool bForce = false);

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon Module")
	void OnModuleEnableChanged(bool bNewEnabled);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Module")
	ABaseWeapon* OwnerWeapon{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Module")
	bool bUseTick{ false };

private:
	bool bIsEnabled{ false };
};
