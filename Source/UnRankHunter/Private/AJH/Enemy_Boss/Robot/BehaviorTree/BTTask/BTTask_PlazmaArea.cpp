#include "BTTask_PlazmaArea.h"
#include "MT26.h"
#include "AIController_Boss.h"

UBTTask_PlazmaArea::UBTTask_PlazmaArea()
{
	NodeName = TEXT("PlazmaArea");
	bNotifyTick = true;
	bIsAttacking = false;
}

EBTNodeResult::Type UBTTask_PlazmaArea::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMT26* MT26 = Cast<AMT26>(OwnerComp.GetAIOwner()->GetPawn());
	if (!MT26) {
		return EBTNodeResult::Failed;
	}

	MT26->PlazmaArea();
	bIsAttacking = true;

	MT26->OnAttackEnd.RemoveDynamic(this, &UBTTask_PlazmaArea::OnAttackEnd);
	MT26->OnAttackEnd.AddDynamic(this, &UBTTask_PlazmaArea::OnAttackEnd);

	return EBTNodeResult::InProgress;
}

void UBTTask_PlazmaArea::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsAttacking) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_PlazmaArea::OnAttackEnd()
{
	bIsAttacking = false;
}