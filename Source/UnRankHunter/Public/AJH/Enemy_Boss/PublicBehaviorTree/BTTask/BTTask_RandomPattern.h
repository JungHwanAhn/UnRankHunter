#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RandomPattern.generated.h"

UCLASS()
class UNRANKHUNTER_API UBTTask_RandomPattern : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_RandomPattern();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};