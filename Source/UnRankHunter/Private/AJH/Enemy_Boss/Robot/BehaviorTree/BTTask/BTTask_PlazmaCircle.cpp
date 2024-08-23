#include "BTTask_PlazmaCircle.h"
#include "MiniMT26.h"
#include "AIController_MiniMT26.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_PlazmaCircle::UBTTask_PlazmaCircle()
{
	NodeName = TEXT("PlazmaCircle");
	bNotifyTick = true;
	bIsAttacking = false;
}

EBTNodeResult::Type UBTTask_PlazmaCircle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMiniMT26* MiniMT26 = Cast<AMiniMT26>(OwnerComp.GetAIOwner()->GetPawn());
	if (!MiniMT26) {
		return EBTNodeResult::Failed;
	}
	MiniMT26->PlazmaCircle();
	bIsAttacking = true;

	MiniMT26->OnAttackEnd.RemoveDynamic(this, &UBTTask_PlazmaCircle::OnAttackEnd);
	MiniMT26->OnAttackEnd.AddDynamic(this, &UBTTask_PlazmaCircle::OnAttackEnd);

	return EBTNodeResult::InProgress;
}

void UBTTask_PlazmaCircle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsAttacking) {
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AAIController_MiniMT26::bIsPlazmaCircleKey, true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_PlazmaCircle::OnAttackEnd()
{
	bIsAttacking = false;
}