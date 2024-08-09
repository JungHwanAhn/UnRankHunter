#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_HomingRocket.generated.h"

UCLASS()
class UNRANKHUNTER_API UBTTask_HomingRocket : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_HomingRocket();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	bool bIsAttacking = false;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UFUNCTION()
	void OnAttackEnd();
};
