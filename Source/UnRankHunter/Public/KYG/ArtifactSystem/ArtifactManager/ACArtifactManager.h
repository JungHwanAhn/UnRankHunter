// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnRankHunter/UnRankHunter.h"
#include "Components/ActorComponent.h"
#include "ACArtifactManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNRANKHUNTER_API UACArtifactManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UACArtifactManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Container of all artifact instances.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Artifact Manager")
	TArray<class UArtifactObject*> ArtifactArray;

#pragma region [ Public Interface ]
public:
	UFUNCTION(BlueprintCallable, Category = "Artifact Manager")
	int32 AddArtifact(class UArtifactObject* ArtifactInstance);
	
	UFUNCTION(BlueprintCallable, Category = "Artifact Manager")
	int32 AddArtifactByID(FName ArtifactID);
#pragma endregion

public:
private:
	TSubclassOf<class UArtifactObject> GetArtifactClass(FName ArtifactID);
};
