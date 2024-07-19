#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CollisionSubsystem.generated.h"

UCLASS()
class UNRANKHUNTER_API UCollisionSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Collision SubSystem")
	void CollisionStart(AActor* Actor, FString type);

	UFUNCTION(BlueprintCallable, Category = "Collision SubSystem")
	void CollisionEnd(AActor* Actor);
};
