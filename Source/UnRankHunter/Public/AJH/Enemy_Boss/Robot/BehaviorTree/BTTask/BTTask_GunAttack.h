#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GunAttack.generated.h"

UCLASS()
class UNRANKHUNTER_API UBTTask_GunAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_GunAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	bool bIsAttacking = false;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UFUNCTION()
	void OnAttackEnd();
};