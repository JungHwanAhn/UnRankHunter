#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_Boss.generated.h"

UCLASS()
class UNRANKHUNTER_API AAIController_Boss : public AAIController
{
	GENERATED_BODY()
	
public:
	AAIController_Boss();

	virtual void OnPossess(APawn* InPawn) override;
	void StopAI();
	void StartAI();

	static const FName TargetKey;

private:
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, Category = "BehaviorTree")
	class UBehaviorTree* BTEnemy;

	UPROPERTY(VisibleAnywhere, Category = "BehaviorTree")
	class UBlackboardData* BBEnemy;

	class AActor* Player;
	class ABaseEnemy_Common* ControlledPawn;
};
