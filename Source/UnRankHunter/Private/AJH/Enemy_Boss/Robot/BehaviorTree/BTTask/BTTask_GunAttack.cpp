#include "BTTask_GunAttack.h"
#include "MiniMT26.h"
#include "AIController_MiniMT26.h"

UBTTask_GunAttack::UBTTask_GunAttack()
{
	NodeName = TEXT("GunAttack");
	bNotifyTick = true;
	bIsAttacking = false;
}

EBTNodeResult::Type UBTTask_GunAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMiniMT26* MiniMT26 = Cast<AMiniMT26>(OwnerComp.GetAIOwner()->GetPawn());
	if (!MiniMT26) {
		return EBTNodeResult::Failed;
	}

	MiniMT26->Attack();
	bIsAttacking = true;

	MiniMT26->OnAttackEnd.RemoveDynamic(this, &UBTTask_GunAttack::OnAttackEnd);
	MiniMT26->OnAttackEnd.AddDynamic(this, &UBTTask_GunAttack::OnAttackEnd);

	return EBTNodeResult::InProgress;
}

void UBTTask_GunAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsAttacking) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_GunAttack::OnAttackEnd()
{
	bIsAttacking = false;
}