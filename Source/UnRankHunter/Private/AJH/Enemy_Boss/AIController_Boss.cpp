#include "AIController_Boss.h"
#include "BaseEnemy_Common.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AAIController_Boss::TargetKey(TEXT("Target"));

AAIController_Boss::AAIController_Boss()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		BTObject(TEXT("BehaviorTree'/Game/01_Core/AJH/Enemy/Robot/Boss/BehaviorTree/AJH_BT_MT26.AJH_BT_MT26'"));
	if (BTObject.Succeeded()) {
		BTEnemy = BTObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData>
		BBObject(TEXT("BlackboardData'/Game/01_Core/AJH/Enemy/Robot/Boss/BehaviorTree/AJH_BB_MT26.AJH_BB_MT26'"));
	if (BBObject.Succeeded()) {
		BBEnemy = BBObject.Object;
	}
}

void AAIController_Boss::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ControlledPawn = Cast<ABaseEnemy_Common>(InPawn);

	UBlackboardComponent* BlackboardComp = Blackboard;
	if (UseBlackboard(BBEnemy, BlackboardComp)) {
		Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (Player) {
			BlackboardComp->SetValueAsObject(TargetKey, Player);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("AIController couldn't get player"));
		}
		if (!RunBehaviorTree(BTEnemy)) {
			UE_LOG(LogTemp, Warning, TEXT("AIController couldn't run behavior tree"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController couldn't use blackboard"));
	}
}

void AAIController_Boss::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (!BehaviorTreeComponent) {
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}

void AAIController_Boss::StartAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (!BehaviorTreeComponent) {
		BehaviorTreeComponent->StartTree(*this->BTEnemy, EBTExecutionMode::Looped);
	}
}

void AAIController_Boss::Tick(float DeltaSeconds)
{
	if (!ControlledPawn->bIsEnemyDie) {
		FVector AdjustedPlayerLocation = Player->GetActorLocation() + FVector(0.0f, 0.0f, -13000.0f);
		ControlledPawn->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(ControlledPawn->GetActorLocation(), AdjustedPlayerLocation));
	}
}
