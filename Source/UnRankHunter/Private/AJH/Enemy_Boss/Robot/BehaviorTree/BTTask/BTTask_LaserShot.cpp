#include "BTTask_LaserShot.h"
#include "MT26.h"
#include "AIController_MT26.h"
#include "MiniMT26.h"
#include "AIController_MiniMT26.h"

UBTTask_LaserShot::UBTTask_LaserShot()
{
	NodeName = TEXT("LaserShot");
	bNotifyTick = true;
	bIsAttacking = false;
}

EBTNodeResult::Type UBTTask_LaserShot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMT26* MT26 = Cast<AMT26>(OwnerComp.GetAIOwner()->GetPawn());
	if (MT26) {
		MT26->LaserShot();
		bIsAttacking = true;

		MT26->OnAttackEnd.RemoveDynamic(this, &UBTTask_LaserShot::OnAttackEnd);
		MT26->OnAttackEnd.AddDynamic(this, &UBTTask_LaserShot::OnAttackEnd);

		return EBTNodeResult::InProgress;
	}
	else {
		AMiniMT26* MiniMT26 = Cast<AMiniMT26>(OwnerComp.GetAIOwner()->GetPawn());
		if (!MiniMT26) {
			return EBTNodeResult::Failed;
		}
		MiniMT26->LaserShot();
		bIsAttacking = true;

		MiniMT26->OnAttackEnd.RemoveDynamic(this, &UBTTask_LaserShot::OnAttackEnd);
		MiniMT26->OnAttackEnd.AddDynamic(this, &UBTTask_LaserShot::OnAttackEnd);

		return EBTNodeResult::InProgress;
	}
}

void UBTTask_LaserShot::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsAttacking) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_LaserShot::OnAttackEnd()
{
	bIsAttacking = false;
}