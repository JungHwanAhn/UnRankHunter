#include "BTTask_ClearFocus.h"
#include "AIController_Boss.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearFocus::UBTTask_ClearFocus()
{
	NodeName = TEXT("ClearFocus");
}

EBTNodeResult::Type UBTTask_ClearFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController) {
		auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
		if (!ControlledPawn) {
			return EBTNodeResult::Failed;
		}

		AIController->ClearFocus(EAIFocusPriority::Gameplay);
		return EBTNodeResult::Succeeded;
	}
	else {
		return EBTNodeResult::Failed;
	}
}
