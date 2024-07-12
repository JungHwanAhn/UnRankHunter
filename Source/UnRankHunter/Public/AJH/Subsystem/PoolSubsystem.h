#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PoolSubsystem.generated.h"

USTRUCT()
struct FPoolArray {
	GENERATED_BODY()

	UPROPERTY()
	TArray<AActor*> ObjectPool;

	bool IsEmpty() {
		return ObjectPool.IsEmpty();
	}

	AActor* Pop() {
		return ObjectPool.Pop();
	}

	void Add(AActor* ActorToAdd) {
		ObjectPool.Add(ActorToAdd);
	} 
};

UCLASS()
class UNRANKHUNTER_API UPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Pool SubSystem")
	void SpawnFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation, AActor*& SpawnedActor);

	UFUNCTION(BlueprintCallable, Category = "Pool SubSystem")
	void ReturnToPool(AActor* Poolable);

	UFUNCTION(BlueprintCallable, Category = "Pool SubSystem")
	void InitializePool(TSubclassOf<AActor> PoolClass, int32 MaxSize);

private:
	TMap<UClass*, FPoolArray> ObjectPools;

	AActor* GetActorFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation);
};
