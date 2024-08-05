#include "BTTask_SetFocus.h"
#include "AIController_Boss.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetFocus::UBTTask_SetFocus()
{
	NodeName = TEXT("SetFocus");
}

EBTNodeResult::Type UBTTask_SetFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController) {
		auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
		if (!ControlledPawn) {
			return EBTNodeResult::Failed;
		}
		AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AAIController_Boss::TargetKey));
		if (!Player) {
			return EBTNodeResult::Failed;
		}
		AIController->SetFocus(Player);
		return EBTNodeResult::Succeeded;
	}
	else {
		return EBTNodeResult::Failed;
	}
}