#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PoolSubsystem.generated.h"

// Structure to hold an array of pooled actors
USTRUCT()
struct FPoolArray {
	GENERATED_BODY()

	UPROPERTY()
	TArray<AActor*> ObjectPool;

	// Check if the pool is empty
	bool IsEmpty() {
		return ObjectPool.IsEmpty();
	}

	// Pop an actor from the pool (removes and returns the last actor)
	AActor* Pop() {
		return ObjectPool.Pop();
	}

	// Add an actor to the pool
	void Add(AActor* ActorToAdd) {
		ObjectPool.Add(ActorToAdd);
	} 
};

UCLASS()
class UNRANKHUNTER_API UPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	// Function to spawn an actor from the pool
	UFUNCTION(BlueprintCallable, Category = "Pool SubSystem")
	void SpawnFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation, AActor*& SpawnedActor);

	// Function to return an actor to the pool
	UFUNCTION(BlueprintCallable, Category = "Pool SubSystem")
	void ReturnToPool(AActor* Poolable);

	// Function to initialize the pool for a specific class with a maximum size
	UFUNCTION(BlueprintCallable, Category = "Pool SubSystem")
	void InitializePool(TSubclassOf<AActor> PoolClass, int32 MaxSize);

private:
	// Map of object pools, keyed by class
	TMap<UClass*, FPoolArray> ObjectPools;

	// Helper function to get an actor from the pool or create a new one if necessary
	AActor* GetActorFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation);
};
