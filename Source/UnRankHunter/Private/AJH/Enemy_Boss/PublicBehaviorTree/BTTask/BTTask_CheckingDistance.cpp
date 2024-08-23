#include "BTTask_CheckingDistance.h"
#include "AIController_MiniMT26.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_CheckingDistance::UBTTask_CheckingDistance()
{
	NodeName = TEXT("CheckingDistance");
}

EBTNodeResult::Type UBTTask_CheckingDistance::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AAIController_MiniMT26::bIsCheckingKey, true);
	return EBTNodeResult::Succeeded;
}