#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_Rambo.generated.h"

UCLASS()
class UNRANKHUNTER_API AAIController_Rambo : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnPossess(APawn* InPawn) override;
private:
	class APawn* PlayerPawn;
	class ARambo* Rambo;

	bool bIsAttack = false;
	float attackDelay = 2.5;
	float moveRange = 1700.0f;

	float acceptanceRadius = 1800.0f;
	float avoidanceRadius = 300.0f;
	float avoidanceStrength = 2.0f;
	float lastEnemyScan = 0.0f;
	float enemyScanInterval = 0.2f;

	FVector AvoidanceVector;

	void EnemyScan();
};
