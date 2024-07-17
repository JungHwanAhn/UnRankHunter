// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon/WeaponModule/Base/ACBaseTriggerModule.h"
#include "Weapon/WeaponModule/Base/ACBaseShooterModule.h"
#include "Weapon/WeaponModule/Base/ACBaseReloadModule.h"
#include "Weapon/WeaponModule/Base/ACBaseScopeModule.h"
#include "BaseWeapon.generated.h"

UCLASS()
class UNRANKHUNTER_API ABaseWeapon : public AActor, public IWeaponInterface
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();

protected:
	virtual void BeginPlay() override;

private:
	void GenerateBasicModule();

protected:
	UACBaseTriggerModule* TriggerModule{};
	UACBaseShooterModule* ShooterModule{};
	UACBaseReloadModule* ReloadModule{};
	UACBaseScopeModule* ScopeModule{};

private:
	void ReceiveFireNotify(float TriggerValue);

#pragma region [Weapon Interface Implementation]
	// Set start or stop weapon firing.
	virtual void SetFireInput_Implementation(bool bInput) override;

	// Set start or stop weapon reloading.
	virtual void SetReloadInput_Implementation(bool bInput) override;

	// Set start or stop weapon zooming.
	virtual void SetZoomInput_Implementation(bool bInput) override;


	// Return this weapon can fire now.
	// If CanFire() is false, this weapon must not be fired.
	virtual bool CanFire_Implementation() override;

	// Return this weapon can reload now.
	// If CanReload() is false, this weapon must not be reloaded.
	virtual bool CanReload_Implementation() override;

	// Return this weapon can zoom now.
	// If CanZoom() is false, this weapon must not be zoomed.
	virtual bool CanZoom_Implementation() override;


	// Return this weapon is firing now.
	virtual bool IsFiring_Implementation() override;

	// Return this weapon is reloading now.
	virtual bool IsReloading_Implementation() override;

	// Return this weapon is zooming now.
	virtual bool IsZooming_Implementation() override;


	// Set weapon enable state.
	// If you set this property false, this weapon become invisible, no collision, tick disabled.
	virtual void SetWeaponEnabled_Implementation(bool bNewEnabled) override;

	// Return weapon enable state.
	virtual bool GetWeaponEnabled_Implementation() override;

	// Setup and initialize weapon attachment.
	// When this weapon is created, must use this function to initialize.
	virtual void SetupWeaponAttachment_Implementation(AActor* Owner, USceneComponent* AttachParent, FName SocketName = "") override;


	virtual FName GetWeaponID_Implementation() override;

	virtual int32 GetRemainAmmoCount_Implementation() override;

	virtual void RefillAmmoCount_Implementation(int32 AmmoCount) override;
#pragma endregion

protected:
	int32 GetMaxAmmoCapacity();

	float GetDamageAmount(int DamageType, float Falloff, FName HitTag, EElementType Type)
	{
		FWeaponParameter Param;
		FWeaponStat FinStat;

		Execute_GetWeaonParameter(this, Param);
		Execute_GetWeaponFinalStat(this, FinStat);
		
	}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data|Ammo")
	int32 RemainAmmoCount{ 0 };
};
