// Fill out your copyright notice in the Description page of Project Settings.


#include "ArtifactSystem/ArtifactObject/ArtifactObject.h"
#include "KYG/ArtifactSystem/ArtifactManager/ACArtifactManager.h"

// Sets default values for this component's properties
UACArtifactManager::UACArtifactManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UACArtifactManager::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UACArtifactManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	for (auto item : ArtifactArray)
	{
		if (item->bUseTick)
		{
			item->Tick(DeltaTime);
		}
	}
}

bool UACArtifactManager::AddArtifact(UArtifactObject* ArtifactInstance)
{
	ArtifactArray.Add(ArtifactInstance);
	ArtifactInstance->InitializeArtifact(GetOwner());

	return false;
}

bool UACArtifactManager::AddArtifactByID(FName ArtifactID)
{
	TSubclassOf<class UArtifactObject> ArtifactClass = GetArtifactClass(ArtifactID);
	if (ArtifactClass == nullptr)
	{
		UH_LogTempParam(Warning, TEXT("Add Artifact is FAILURE! id %s can't find."), *ArtifactID.ToString());
		return false;
	}


	UArtifactObject* ArtifactInstance = NewObject<UArtifactObject>(nullptr, ArtifactClass, "UArtifactInstance");
	AddArtifact(ArtifactInstance);
	return true;
}

TSubclassOf<class UArtifactObject> UACArtifactManager::GetArtifactClass(FName ArtifactID)
{
	return nullptr;
}

