#include "BTTask_Firebat.h"
#include "MiniMT26.h"
#include "AIController_MiniMT26.h"

UBTTask_Firebat::UBTTask_Firebat()
{
	NodeName = TEXT("Firebat");
	bNotifyTick = true;
	bIsAttacking = false;
}

EBTNodeResult::Type UBTTask_Firebat::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMiniMT26* MiniMT26 = Cast<AMiniMT26>(OwnerComp.GetAIOwner()->GetPawn());
	if (!MiniMT26) {
		return EBTNodeResult::Failed;
	}
	MiniMT26->Firebat();
	bIsAttacking = true;

	MiniMT26->OnAttackEnd.RemoveDynamic(this, &UBTTask_Firebat::OnAttackEnd);
	MiniMT26->OnAttackEnd.AddDynamic(this, &UBTTask_Firebat::OnAttackEnd);

	return EBTNodeResult::InProgress;
}

void UBTTask_Firebat::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsAttacking) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_Firebat::OnAttackEnd()
{
	bIsAttacking = false;
}
