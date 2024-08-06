#include "BTTask_LaserBeam.h"
#include "MT26.h"
#include "AIController_Boss.h"

UBTTask_LaserBeam::UBTTask_LaserBeam()
{
	NodeName = TEXT("LaserBeam");
	bNotifyTick = true;
	bIsAttacking = false;
}

EBTNodeResult::Type UBTTask_LaserBeam::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMT26* MT26 = Cast<AMT26>(OwnerComp.GetAIOwner()->GetPawn());
	if (!MT26) {
		return EBTNodeResult::Failed;
	}

	MT26->LaserBeam();
	bIsAttacking = true;

	MT26->OnAttackEnd.RemoveDynamic(this, &UBTTask_LaserBeam::OnAttackEnd);
	MT26->OnAttackEnd.AddDynamic(this, &UBTTask_LaserBeam::OnAttackEnd);

	return EBTNodeResult::InProgress;
}

void UBTTask_LaserBeam::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsAttacking) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_LaserBeam::OnAttackEnd()
{
	bIsAttacking = false;
}
