// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KYG/ArtifactSystem/ArtifactObject/ArtifactObject.h"
#include "BlueprintInterface/PlayerStatInterface.h"
#include "Weapon/Structure/WeaponStructure.h"
#include "ArtifactObject_BleedingHeart.generated.h"

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class UNRANKHUNTER_API UArtifactObject_BleedingHeart : public UArtifactObject
{
	GENERATED_BODY()

public:
	UArtifactObject_BleedingHeart();

public:
	virtual void EnableArtifact() override;

	virtual void DisableArtifect() override;

	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Artifact|BleedingHeart")
	double GetDuration();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Artifact|BleedingHeart")
	float GetCooldownDuration();

protected:
	UFUNCTION()
	void OnActorDamaged(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

private:
	UFUNCTION()
	void StatUpModifier(FWeaponBonusStat& Stat);

	UFUNCTION()
	void StatDownModifier(FWeaponBonusStat& Stat);

	UFUNCTION()
	void AffectBuff();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Artifact|BleedingHeart")
	double BuffDuration{ 15.0 };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Artifact|BleedingHeart")
	float FireSpeedUp{ 0.5f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Artifact|BleedingHeart")
	float ReloadSpeedUp{ 0.5f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Artifact|BleedingHeart")
	float ActiveHealthRatio{ 0.5f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Artifact|BleedingHeart")
	float CooldownTime{ 30.0f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Artifact|BleedingHeart")
	bool bIsBuffActive{ false };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Artifact|BleedingHeart")
	bool bIsCooldown{ false };
private:
	UPROPERTY()
	UActorComponent* PlayerStat{};

	UPROPERTY()
	class UACWeaponManager* WeaponManager{};

	UPROPERTY()
	FTimerHandle BuffTimer{};

	UPROPERTY()
	FTimerHandle CooldownTimer{};

	UPROPERTY()
	double BuffStartTime{};
};
