#include "BTTask_ShellingToPlayer.h"
#include "MT26.h"
#include "AIController_MT26.h"

UBTTask_ShellingToPlayer::UBTTask_ShellingToPlayer()
{
	NodeName = TEXT("ShellingToPlayer");
	bNotifyTick = true;
	bIsAttacking = false;
}

EBTNodeResult::Type UBTTask_ShellingToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMT26* MT26 = Cast<AMT26>(OwnerComp.GetAIOwner()->GetPawn());
	if (!MT26) {
		return EBTNodeResult::Failed;
	}

	MT26->ShellingToPlayer();
	bIsAttacking = true;

	MT26->OnAttackEnd.RemoveDynamic(this, &UBTTask_ShellingToPlayer::OnAttackEnd);
	MT26->OnAttackEnd.AddDynamic(this, &UBTTask_ShellingToPlayer::OnAttackEnd);

	return EBTNodeResult::InProgress;
}

void UBTTask_ShellingToPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsAttacking) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_ShellingToPlayer::OnAttackEnd()
{
	bIsAttacking = false;
}
