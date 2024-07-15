// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon/Interface/KYG_WeaponInterface.h"
#include "Weapon/Interface/KYG_WeaponPropertyInterface.h"
#include "Weapon/Interface/KYG_Weapon_TriggerModule.h"
#include "Weapon/Interface/KYG_Weapon_ShooterModule.h"
#include "Weapon/Interface/KYG_Weapon_ReloadModule.h"
#include "KYG_Base_Weapon.generated.h"

UCLASS()
class UNRANKHUNTER_API AKYG_Base_Weapon : public AActor, public IKYG_WeaponInterface, public IKYG_WeaponPropertyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AKYG_Base_Weapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Implement "IKYG_WeaponInterface"

#pragma region [Interface]
#pragma region [KYG_WeaponInterface]
public:
	virtual void SetFireInput_Implementation(bool bInput) override;

	// Set start or stop weapon reloading.
	virtual void SetReloadInput_Implementation(bool bInput) override;

	// Set start or stop weapon zooming.
	virtual void SetZoomInput_Implementation(bool bInput) override;


	virtual bool CanFire_Implementation() override;

	virtual bool CanReload_Implementation() override;

	virtual bool CanZoom_Implementation() override;


	virtual bool IsFiring_Implementation() override;

	virtual bool IsReloading_Implementation() override;

	virtual bool IsZooming_Implementation() override;


	virtual void SetWeaponEnabled_Implementation(bool bNewEnabled) override;

	virtual bool GetWeaponEnabled_Implementation() override;

	virtual void AttachWeaponToSocket_Implementation(AActor* Player, USkeletalMeshComponent* Mesh, FName SocketName = "") override;

	virtual void SetupWeaponAttachment_Implementation(AActor* Owner, USceneComponent* AttachParent, FName SocketName = "") override;


	virtual void GetFinalStat_Implementation(FKYG_WeaponStat& Output) override;

	virtual int GetRemainAmmoCount_Implementation() override;
#pragma endregion
#pragma region [KYG_WeaponPropertyInterface]
	virtual FName GetWeaponID_Implementation() override;

	virtual void GetWeaponParameter_Implementation(FKYG_WeaponParameter& Output) override;

	virtual void GetFinalStat_Implementation(FKYG_WeaponStat& Output) override;

	virtual void GetBasicStat_Implementation(FKYG_WeaponStat& Output) override;
#pragma endregion
#pragma endregion


private:
	IKYG_Weapon_TriggerModule* TriggerModule{};

	IKYG_Weapon_ShooterModule* ShooterModule{};

	IKYG_Weapon_ReloadModule* ReloadModule{};


	bool bFireInputState{ false };

	bool bReloadInputState{ false };

	bool bZoomInputState{ false };


	int32 RemainAmmo{ 0 };
};
