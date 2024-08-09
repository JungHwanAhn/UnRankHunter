#include "BTTask_MultiLaserShot.h"
#include "MT26.h"
#include "AIController_Boss.h"

UBTTask_MultiLaserShot::UBTTask_MultiLaserShot()
{
	NodeName = TEXT("MultiLaserShot");
	bNotifyTick = true;
	bIsAttacking = false;
}

EBTNodeResult::Type UBTTask_MultiLaserShot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMT26* MT26 = Cast<AMT26>(OwnerComp.GetAIOwner()->GetPawn());
	if (!MT26) {
		return EBTNodeResult::Failed;
	}

	MT26->MultiLaserShot();
	bIsAttacking = true;

	MT26->OnAttackEnd.RemoveDynamic(this, &UBTTask_MultiLaserShot::OnAttackEnd);
	MT26->OnAttackEnd.AddDynamic(this, &UBTTask_MultiLaserShot::OnAttackEnd);

	return EBTNodeResult::InProgress;
}

void UBTTask_MultiLaserShot::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds); 

	if (!bIsAttacking) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_MultiLaserShot::OnAttackEnd()
{
	bIsAttacking = false;
}