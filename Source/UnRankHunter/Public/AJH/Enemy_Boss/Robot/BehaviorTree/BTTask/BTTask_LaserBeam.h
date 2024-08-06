#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_LaserBeam.generated.h"

UCLASS()
class UNRANKHUNTER_API UBTTask_LaserBeam : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_LaserBeam();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	bool bIsAttacking = false;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UFUNCTION()
	void OnAttackEnd();
};
