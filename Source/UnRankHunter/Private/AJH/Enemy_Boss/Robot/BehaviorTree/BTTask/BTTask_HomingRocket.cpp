#include "BTTask_HomingRocket.h"
#include "MT26.h"
#include "AIController_Boss.h"

UBTTask_HomingRocket::UBTTask_HomingRocket()
{
	NodeName = TEXT("HomingRocket");
	bNotifyTick = true;
	bIsAttacking = false;
}

EBTNodeResult::Type UBTTask_HomingRocket::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMT26* MT26 = Cast<AMT26>(OwnerComp.GetAIOwner()->GetPawn());
	if (!MT26) {
		return EBTNodeResult::Failed;
	}

	MT26->HomingRocket();
	bIsAttacking = true;

	MT26->OnAttackEnd.RemoveDynamic(this, &UBTTask_HomingRocket::OnAttackEnd);
	MT26->OnAttackEnd.AddDynamic(this, &UBTTask_HomingRocket::OnAttackEnd);

	return EBTNodeResult::InProgress;
}

void UBTTask_HomingRocket::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsAttacking) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_HomingRocket::OnAttackEnd()
{
	bIsAttacking = false;
}