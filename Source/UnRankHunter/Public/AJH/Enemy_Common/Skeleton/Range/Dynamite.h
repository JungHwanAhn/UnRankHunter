#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dynamite.generated.h"

UCLASS()
class UNRANKHUNTER_API ADynamite : public AActor
{
	GENERATED_BODY()
	
public:	
	ADynamite();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	class UStaticMeshComponent* Dynamite;

private:
	void LaunchTowardsPlayer();
	float CalculateLaunchSpeed(float distance);
	float CalculateLaunchZVelocity(float distance, float launchSpeed);

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* DynamiteCollision;
};
