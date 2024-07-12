#include "PoolSubsystem.h"
#include "Poolable.h"

// Spawns an actor from the pool or creates a new one if none are available
void UPoolSubsystem::SpawnFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation, AActor*& SpawnedActor)
{
	SpawnedActor = GetActorFromPool(PoolClass, Location, Rotation);
}

// Returns an actor to the pool for reuse
void UPoolSubsystem::ReturnToPool(AActor* Poolable)
{
    if (!Poolable) return;

    UClass* ActorClass = Poolable->GetClass();

    if (ActorClass->ImplementsInterface(UPoolable::StaticClass()))
    {
        IPoolable::Execute_OnReturnToPool(Poolable);
        Poolable->SetActorHiddenInGame(true);
        Poolable->SetActorEnableCollision(false);
        FPoolArray& ObjectPool = ObjectPools.FindOrAdd(ActorClass);
        ObjectPool.Add(Poolable);
    }
    else
    {
        Poolable->Destroy();
    }
}

// Initializes a pool with a specified number of actors
void UPoolSubsystem::InitializePool(TSubclassOf<AActor> PoolClass, int32 MaxSize)
{
    FPoolArray& ObjectPool = ObjectPools.FindOrAdd(PoolClass);
    for (int32 i = 0; i < MaxSize; ++i) {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        AActor* NewActor = GetWorld()->SpawnActor<AActor>(PoolClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
        if (NewActor && PoolClass.Get()->ImplementsInterface(UPoolable::StaticClass())) {
            IPoolable::Execute_OnReturnToPool(NewActor);
            NewActor->SetActorHiddenInGame(true);
            NewActor->SetActorEnableCollision(false);
            ObjectPool.Add(NewActor);
        }
    }
}

// Retrieves an actor from the pool or creates a new one if the pool is empty
AActor* UPoolSubsystem::GetActorFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation)
{
    FPoolArray& ObjectPool = ObjectPools.FindOrAdd(PoolClass);
    // Retrieves an actor from the pool
    if (!ObjectPool.IsEmpty())
    {
        AActor* Actor = ObjectPool.Pop();
        if (Actor) {
            Actor->SetActorLocationAndRotation(Location, Rotation);
            Actor->SetActorEnableCollision(true);
            Actor->SetActorHiddenInGame(false);
            IPoolable::Execute_OnSpawnFromPool(Actor);
            return Actor;
        }
    }
    //creates a new one if the pool is empty
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    AActor* NewActor = GetWorld()->SpawnActor<AActor>(PoolClass, Location, Rotation, SpawnParams);
    if (NewActor && PoolClass.Get()->ImplementsInterface(UPoolable::StaticClass())) {
        IPoolable::Execute_OnSpawnFromPool(NewActor);
    }
    return NewActor;
}
