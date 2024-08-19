// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnRankHunter/UnRankHunter.h"
#include "UObject/NoExportTypes.h"
#include "Weapon/Structure/WeaponStructure.h"
#include "ArtifactObject.generated.h"

USTRUCT(BlueprintType)
struct FArtifactTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ArtifactID{ NAME_None };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ArtifactName{ "" };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ArtifactDesc{ "" };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* ArtifactIcon{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemRarity Rarity{ EItemRarity::Common };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UArtifactObject> ArtifactClass;
};

UCLASS(Abstract, BlueprintType)
class UNRANKHUNTER_API UArtifactObject : public UObject
{
	GENERATED_BODY()

public:
	bool bUseTick{ false };


public:
	void InitializeArtifact(AActor* Owner);

	virtual void EnableArtifact();

	virtual void DisableArtifect();

	virtual void Tick(float DeltaTime) {};

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Artifact")
	bool IsActive();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Artifact")
	bool IsEnabled();

protected:
	AActor* ArtifactOwner{};

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Artifact")
	FName ArtifactID{ NAME_None };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Artifact")
	FString ArtifactName{ "" };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Artifact")
	TEnumAsByte<EItemRarity> Rarity{ EItemRarity::Legend };

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Artifact")
	FName GetArtifactID() { return ArtifactID; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Artifact")
	FString GetArtifactName() { return ArtifactName; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Artifact")
	TEnumAsByte<EItemRarity> GetRarity() { return Rarity; }


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Artifact")
	bool bIsTickEnabled{ false };

	// The state that artifact effect is activated.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Artifact")
	bool bIsActive{ true };

private:
	// The state that artifact is enabled.
	UPROPERTY(VisibleAnywhere, Category = "Artifact")
	bool bIsEnabled{ true };
};
