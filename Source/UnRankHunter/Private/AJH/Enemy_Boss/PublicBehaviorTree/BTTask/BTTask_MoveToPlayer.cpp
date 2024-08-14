#include "BTTask_MoveToPlayer.h"
#include "MiniMT26.h"
#include "AIController_MiniMT26.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_MoveToPlayer::UBTTask_MoveToPlayer()
{
    NodeName = TEXT("MoveToPlayer");
    bNotifyTick = true;
    bIsMoving = false;
}

EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    MiniMT26 = Cast<AMiniMT26>(OwnerComp.GetAIOwner()->GetPawn());
    if (!MiniMT26) {
        UE_LOG(LogTemp, Warning, TEXT("MoveToPlayer BTTaskNode Can't Cast MiniMT26"));
        return EBTNodeResult::Failed;
    }

    Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AAIController_MiniMT26::TargetKey));
    if (!Player) {
        UE_LOG(LogTemp, Warning, TEXT("MoveToPlayer BTTaskNode Can't Cast Player"));
        return EBTNodeResult::Failed;
    }

    AIController = OwnerComp.GetAIOwner();
    if (!AIController) {
        UE_LOG(LogTemp, Warning, TEXT("MoveToPlayer BTTaskNode Can't Get AIController"));
        return EBTNodeResult::Failed;
    }

    float distance = FVector::Distance(Player->GetActorLocation(), MiniMT26->GetActorLocation());
    if (distance > 3500.0f) {
        bIsMoving = true;
        AIController->MoveToActor(Player);
        return EBTNodeResult::InProgress;
    }

    bIsMoving = false;
    return EBTNodeResult::Succeeded;
}

void UBTTask_MoveToPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    if (!MiniMT26 || !Player || !AIController) {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    if (!bIsMoving) {
        return;
    }

    float distance = FVector::Distance(Player->GetActorLocation(), MiniMT26->GetActorLocation());
    if (distance <= 3500.0f) {
        bIsMoving = false;
        AIController->StopMovement();
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
    else {
        AIController->MoveToActor(Player);
    }
}