#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetForm.generated.h"

UCLASS()
class UNRANKHUNTER_API UBTTask_SetForm : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_SetForm();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};