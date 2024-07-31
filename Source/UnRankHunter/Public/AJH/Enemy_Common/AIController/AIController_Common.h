#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_Common.generated.h"

UCLASS()
class UNRANKHUNTER_API AAIController_Common : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnPossess(APawn* InPawn) override;
private:
	class APawn* PlayerPawn;
	class ABaseEnemy_Common* ControlledPawn;

	bool bIsAttack = false;
	float attackDelay = 3.0f;
	float acceptanceRadius = 130.0f;
	float avoidanceRadius = 300.0f;
	float avoidanceStrength = 1.5f;
	float lastEnemyScan = 0.0f;
	float enemyScanInterval = 0.2f;

	FVector AvoidanceVector;
	void EnemyScan();
};
