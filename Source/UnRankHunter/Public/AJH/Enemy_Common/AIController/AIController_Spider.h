#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_Spider.generated.h"

UCLASS()
class UNRANKHUNTER_API AAIController_Spider : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnPossess(APawn* InPawn) override;
private:
	class APawn* PlayerPawn;
	class ASpider* Spider;

	bool bIsAttack = false;
	float attackDelay = 1.5f;
	float moveRange = 1700.0f;

	float acceptanceRadius = 1800.0f;
	float avoidanceRadius = 300.0f;
	float avoidanceStrength = 2.0f;
	float lastEnemyScan = 0.0f;
	float enemyScanInterval = 0.2f;

	FVector AvoidanceVector;

	void EnemyScan();
};
