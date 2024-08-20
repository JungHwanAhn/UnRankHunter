// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/ArtifactSystem/ArtifactManager/ACArtifactManager.h"
#include "ArtifactSystem/ArtifactObject/ArtifactObject.h"

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

int32 UACArtifactManager::AddArtifact(UArtifactObject* ArtifactInstance)
{
	if (ArtifactInstance == nullptr)
	{
		UH_LogTemp(Warning, TEXT("Giving artifact is FAILURE! Cause: Artifact instance is empty."));
		return -1;
	}

	int32 SlotIndex = ArtifactArray.Add(ArtifactInstance);
	ArtifactInstance->InitializeArtifact(GetOwner());

	UH_LogTempParam(Log, TEXT("Giving artifact is SUCCESSED! %s artifact set in %d slot"), *ArtifactInstance->GetArtifactName(), SlotIndex);

	return SlotIndex;
}

int32 UACArtifactManager::AddArtifactByID(FName ArtifactID)
{
	TSubclassOf<class UArtifactObject> ArtifactClass = GetArtifactClass(ArtifactID);
	if (ArtifactClass == nullptr)
	{
		UH_LogTempParam(Warning, TEXT("Add Artifact is FAILURE! id %s can't find."), *ArtifactID.ToString());
		return -1;
	}

	// Instantiate and initialize the artifact class.
	UArtifactObject* ArtifactInstance = NewObject<UArtifactObject>(this, ArtifactClass, "UArtifactInstance");

	return AddArtifact(ArtifactInstance);
}

TSubclassOf<class UArtifactObject> UACArtifactManager::GetArtifactClass(FName ArtifactID)
{
	FString DTPath = "/Script/Engine.DataTable'/Game/01_Core/KYG/ArtifactSystem/DataTable/KYG_DT_ArtifactTable.KYG_DT_ArtifactTable'";
	UDataTable* ArtifactDataTable = LoadObject<UDataTable>(nullptr, *DTPath, nullptr);

	// Exception: DTPath is null or missing path.
	if (ArtifactDataTable == nullptr)
	{
		UH_LogTempParam(Warning, TEXT("Loading the Artifact Data Table is FAILURE! Cause: the path \"%s\" is not available."), *DTPath);
		return nullptr;
	}

	FArtifactTableRow* Row = ArtifactDataTable->FindRow<FArtifactTableRow>(ArtifactID, nullptr);

	// Exception: Parameter; ArtifactID is not contain in data table.
	if (Row == nullptr)
	{
		UH_LogTempParam(Warning, TEXT("Loading the Artifact Data Table is FAILURE! Cause: the row id \"%s\" is not found."), *ArtifactID.ToString());
		return nullptr;
	}

	return Row->ArtifactClass;
}

