// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/Structure/WeaponStructure.h"
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

	// Called when the module is initialized.
	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon Module")
	void BeginModule(class ABaseWeapon* ParentWeapon);

public:
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon Module")
	class ABaseWeapon* GetOwnerWeapon();

	// Change the module activation state.
	UFUNCTION(BlueprintCallable, Category = "Weapon Module")
	void SetModuleEnabled(bool bNewEnabled, bool bForce = false);

	// Gracefully terminate the currently running module action.
	UFUNCTION(BlueprintCallable, Category = "Weapon Module")
	void CancelModuleAction();

protected:
	// Module action cancel event implemented in C++.
	virtual void OnModuleActionCancelled();

	// Module action cancel event implemented in Blueprint.
	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon Module", meta = (DisplayName = "On Module Action Cancelled"))
	void OnModuleActionCancelled_Blueprint();


protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon Module")
	void OnModuleEnableChanged(bool bNewEnabled);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon Module")
	const FWeaponParameter GetWeaponStat();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Module")
	ABaseWeapon* OwnerWeapon{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Module")
	bool bUseTick{ false };

private:
	bool bIsEnabled{ false };
};
