#include "BTTask_Shelling.h"
#include "MT26.h"
#include "AIController_MT26.h"
#include "MiniMT26.h"
#include "AIController_MiniMT26.h"

UBTTask_Shelling::UBTTask_Shelling()
{
	NodeName = TEXT("Shelling");
	bNotifyTick = true;
	bIsAttacking = false;
}

EBTNodeResult::Type UBTTask_Shelling::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMT26* MT26 = Cast<AMT26>(OwnerComp.GetAIOwner()->GetPawn());
	if (MT26) {
		MT26->Shelling();
		bIsAttacking = true;

		MT26->OnAttackEnd.RemoveDynamic(this, &UBTTask_Shelling::OnAttackEnd);
		MT26->OnAttackEnd.AddDynamic(this, &UBTTask_Shelling::OnAttackEnd);

		return EBTNodeResult::InProgress;
	}
	else {
		AMiniMT26* MiniMT26 = Cast<AMiniMT26>(OwnerComp.GetAIOwner()->GetPawn());
		if (!MiniMT26) {
			return EBTNodeResult::Failed;
		}
		MiniMT26->Shelling();
		bIsAttacking = true;

		MiniMT26->OnAttackEnd.RemoveDynamic(this, &UBTTask_Shelling::OnAttackEnd);
		MiniMT26->OnAttackEnd.AddDynamic(this, &UBTTask_Shelling::OnAttackEnd);

		return EBTNodeResult::InProgress;
	}
}

void UBTTask_Shelling::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsAttacking) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_Shelling::OnAttackEnd()
{
	bIsAttacking = false;
}