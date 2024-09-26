// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KYG/ArtifactSystem/ArtifactObject/ArtifactObject.h"
#include "BlueprintArtifactObject.generated.h"

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class UNRANKHUNTER_API UBlueprintArtifactObject : public UArtifactObject
{
	GENERATED_BODY()

public:
	virtual void EnableArtifact() override;

	virtual void DisableArtifect() override;

	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintImplementableEvent, Category = "Artifact", meta = (DisplayName = "Enable Artifact"))
	void EnableArtifact_Blueprint();

	UFUNCTION(BlueprintImplementableEvent, Category = "Artifact", meta = (DisplayName = "Disable Artifact"))
	void DisableArtifect_Blueprint();

	UFUNCTION(BlueprintImplementableEvent, Category = "Artifact", meta = (DisplayName = "Tick"))
	void Tick_Blueprint(float DeltaTime);

protected:
	UFUNCTION(BlueprintCallable, Category = "Artifact", meta = (DisplayName = "Modify Weapon Stat"))
	void ModifyWeaponStat_Blueprint(UPARAM(ref) const FWeaponBonusStat& RefStat);

private:
	UFUNCTION()
	void ModifyStatCallback(FWeaponBonusStat& WeaponStat);

private:
	class UACWeaponManager* WeaponManager{};

	FWeaponBonusStat TempStat{};
};
