// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KYG/Weapon/WeaponModule/Base/ACBaseWeaponModule.h"
#include "ACBaseTriggerModule.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTriggerModuleCallback, float, Value);
//DECLARE_DELEGATE_OneParam(FTriggerModuleCallback__, float Value);

UCLASS(Abstract, BlueprintType, Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNRANKHUNTER_API UACBaseTriggerModule : public UACBaseWeaponModule
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UACBaseTriggerModule();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma region [Weapon Control Method]
public:
	// Do fire.
	UFUNCTION(BlueprintCallable, Category = "Weapon Module|Trigger Module")
	bool SetTriggerInput(bool bInput);

	// Return this weapon can fire now.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon Module|Trigger Module")
	bool CanTrigger()
	{
		return bCanTrigger && !bIsTrigger;
	}

	// Return this weapon is firing.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon Module|Trigger Module")
	bool IsTrigger()
	{
		return bIsTrigger;
	}

	// Return trigger value; charge energy, rapid count, etc.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon Module|Trigger Module")
	float GetTriggerValue()
	{
		return TriggerValue;
	}
#pragma endregion [Weapon Control Method]

protected:
	// Notify weapon fire event.
	UFUNCTION(BlueprintCallable, Category = "Weapon Module|Trigger Module")
	void ExecuteTriggerEvent();

#pragma region [Implementation Method]
protected:
	// A event on trigger input started.
	UFUNCTION(BlueprintNativeEvent, Category = "Weapon Module|Trigger Module")
	void OnTriggerBegin();

	// A event on trigger input ended.
	UFUNCTION(BlueprintNativeEvent, Category = "Weapon Module|Trigger Module")
	void OnTriggerEnd();

	// A event on tick while input stay.
	// This method is not nessessory. It's old code.
	UFUNCTION(BlueprintNativeEvent, Category = "Weapon Module|Trigger Module")
	void OnTriggerTick(float DeltaTime);


#pragma endregion

public:
	UPROPERTY(BlueprintAssignable, Category = "Weapon Module|Trigger Module")
	FTriggerModuleCallback OnFireNotified{};

	//UPROPERTY()
	//FTriggerModuleCallback__ OnFireNotified__{};

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Module|Trigger Module")
	float TriggerValue{ 0 };

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Module|Trigger Module")
	bool bInputState{ false };

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Module|Trigger Module")
	bool bIsTrigger{ false };

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Module|Trigger Module")
	bool bCanTrigger{ true };
};
