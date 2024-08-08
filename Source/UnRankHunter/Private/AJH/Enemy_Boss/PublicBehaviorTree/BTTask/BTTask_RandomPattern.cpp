#include "BTTask_RandomPattern.h"
#include "AIController_Boss.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_RandomPattern::UBTTask_RandomPattern()
{
	NodeName = TEXT("RandomPattern");
}

EBTNodeResult::Type UBTTask_RandomPattern::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	int32 randomPattern = FMath::RandRange(0, OwnerComp.GetBlackboardComponent()->GetValueAsInt(AAIController_Boss::MaxPatternCountKey));
	OwnerComp.GetBlackboardComponent()->SetValueAsInt(AAIController_Boss::RandomPatternKey, randomPattern);
	return EBTNodeResult::Succeeded;
}