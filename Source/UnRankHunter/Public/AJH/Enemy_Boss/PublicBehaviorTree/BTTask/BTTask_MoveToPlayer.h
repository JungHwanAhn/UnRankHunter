#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MoveToPlayer.generated.h"

UCLASS()
class UNRANKHUNTER_API UBTTask_MoveToPlayer : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_MoveToPlayer();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	class AAIController* AIController;
	class AActor* Player;
	class AMiniMT26* MiniMT26;

	bool bIsMoving = false;
};