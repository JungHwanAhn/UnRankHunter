#include "BTTask_SetForm.h"
#include "MT26.h"
#include "AIController_Boss.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetForm::UBTTask_SetForm()
{
	NodeName = TEXT("SetForm");
}

EBTNodeResult::Type UBTTask_SetForm::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMT26* MT26 = Cast<AMT26>(OwnerComp.GetAIOwner()->GetPawn());
	if (!MT26) {
		return EBTNodeResult::Failed;
	}

	FName CurrentForm = OwnerComp.GetBlackboardComponent()->GetValueAsName(AAIController_Boss::FormKey);

	if (CurrentForm == FName(TEXT("Laser"))) {
		MT26->ChangeForm();
		MT26->ChangeColor(FName(TEXT("Laser")));
	}
	else if (CurrentForm == FName(TEXT("Plazma"))) {
		MT26->ChangeForm();
		MT26->ChangeColor(FName(TEXT("Plazma")));
	}
	else if (CurrentForm == FName(TEXT("Rocket"))) {
		MT26->ChangeForm();
		MT26->ChangeColor(FName(TEXT("Rocket")));
	}
	else {
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AAIController_Boss::bIsChangeFormKey, false);
	return EBTNodeResult::Succeeded;
}