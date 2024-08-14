#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_MiniMT26.generated.h"

UCLASS()
class UNRANKHUNTER_API AAIController_MiniMT26 : public AAIController
{
	GENERATED_BODY()
	
public:
	AAIController_MiniMT26();

	virtual void OnPossess(APawn* InPawn) override;
	void StopAI();
	void StartAI();

	static const FName TargetKey;
	static const FName MaxPatternCountKey;
	static const FName RandomPatternKey;

private:
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, Category = "BehaviorTree")
	class UBehaviorTree* BTEnemy;

	UPROPERTY(VisibleAnywhere, Category = "BehaviorTree")
	class UBlackboardData* BBEnemy;

	class AActor* Player;
	class AMiniMT26* MiniMT26;
};