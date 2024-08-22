#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CheckingDistance.generated.h"

UCLASS()
class UNRANKHUNTER_API UBTTask_CheckingDistance : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_CheckingDistance();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};