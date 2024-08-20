#include "BTTask_PlazmaToPlayer.h"
#include "MT26.h"
#include "AIController_MT26.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_PlazmaToPlayer::UBTTask_PlazmaToPlayer()
{
	NodeName = TEXT("PlazmaToPlayer");
	bNotifyTick = true;
	bIsAttacking = false;
}

EBTNodeResult::Type UBTTask_PlazmaToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMT26* MT26 = Cast<AMT26>(OwnerComp.GetAIOwner()->GetPawn());
	if (!MT26) {
		return EBTNodeResult::Failed;
	}

	MT26->PlazmaToPlayer();
	bIsAttacking = true;

	MT26->OnAttackEnd.RemoveDynamic(this, &UBTTask_PlazmaToPlayer::OnAttackEnd);
	MT26->OnAttackEnd.AddDynamic(this, &UBTTask_PlazmaToPlayer::OnAttackEnd);

	return EBTNodeResult::InProgress;
}

void UBTTask_PlazmaToPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsAttacking) {
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AAIController_MT26::bIsPlazmaAreaKey, false);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_PlazmaToPlayer::OnAttackEnd()
{
	bIsAttacking = false;
}