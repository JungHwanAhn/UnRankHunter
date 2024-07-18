// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon/Interface/WeaponInterface.h"
#include "Weapon/WeaponModule/Base/ACBaseTriggerModule.h"
#include "Weapon/WeaponModule/Base/ACBaseShooterModule.h"
#include "Weapon/WeaponModule/Base/ACBaseReloadModule.h"
#include "Weapon/WeaponModule/Base/ACBaseScopeModule.h"
#include "Elemental/Enum/ElementalEnums.h"
#include "BaseWeapon.generated.h"

UCLASS(BlueprintType, Blueprintable)
class UNRANKHUNTER_API ABaseWeapon : public AActor, public IWeaponInterface
{
	GENERATED_BODY()

public:
	ABaseWeapon();

protected:
	virtual void BeginPlay() override;

private:
	void GenerateBasicModule();


private:
	void ReceiveFireNotify(float Value);

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
	virtual void SetupWeaponAttachment_Implementation(AActor* WeaponOwner) override;


	virtual FName GetWeaponID_Implementation() override;

	virtual int32 GetRemainAmmoCount_Implementation() override;

	virtual void RefillAmmoCount_Implementation(int32 AmmoCount) override;
#pragma endregion

public:
	USceneComponent* GetCameraPosition();

	USceneComponent* GetMuzzlePosition();

protected:
	int32 GetMaxAmmoCapacity();

	float GetDamageAmount(EDamageEffectType DamageType, float Distance, FName HitTag, EDamageElementalType Type, bool bIsCritical);

protected:
	// Assign On Begin Play
	UACBaseTriggerModule* TriggerModule{};
	UACBaseShooterModule* ShooterModule{};
	UACBaseReloadModule* ReloadModule{};
	UACBaseScopeModule* ScopeModule{};

protected:
	UPROPERTY();
	USceneComponent* CameraPositionComponent{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	class UArrowComponent* MuzzlePositionComponent{};

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data|Ammo")
	int32 RemainAmmoCount{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Ammo")
	bool bIsInfiniteAmmo{ false };

private:
	bool bWeaponEnabled{ false };


public:
	// On Bullet Fired
	// On Occur Damage
	// On Change Trigger/Reload/Zoom State
	// On Recover
};
