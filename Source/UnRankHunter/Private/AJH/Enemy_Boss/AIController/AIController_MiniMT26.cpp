#include "AIController_MiniMT26.h"
#include "MiniMT26.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AAIController_MiniMT26::TargetKey(TEXT("Target"));
const FName AAIController_MiniMT26::MaxPatternCountKey(TEXT("MaxPatternCount"));
const FName AAIController_MiniMT26::RandomPatternKey(TEXT("RandomPattern"));

AAIController_MiniMT26::AAIController_MiniMT26()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		BTObject(TEXT("BehaviorTree'/Game/01_Core/AJH/Enemy/Robot/Boss/BehaviorTree/AJH_BT_MiniMT26.AJH_BT_MiniMT26'"));
	if (BTObject.Succeeded()) {
		BTEnemy = BTObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData>
		BBObject(TEXT("BlackboardData'/Game/01_Core/AJH/Enemy/Robot/Boss/BehaviorTree/AJH_BB_MiniMT26.AJH_BB_MiniMT26'"));
	if (BBObject.Succeeded()) {
		BBEnemy = BBObject.Object;
	}
}

void AAIController_MiniMT26::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	MiniMT26 = Cast<AMiniMT26>(InPawn);

	UBlackboardComponent* BlackboardComp = Blackboard;
	if (UseBlackboard(BBEnemy, BlackboardComp)) {
		Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
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

void AAIController_MiniMT26::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BehaviorTreeComponent) {
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}

void AAIController_MiniMT26::StartAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BehaviorTreeComponent) {
		BehaviorTreeComponent->StartTree(*this->BTEnemy, EBTExecutionMode::Looped);
	}
}

void AAIController_MiniMT26::Tick(float DeltaSeconds)
{
	if (!MiniMT26->bIsEnemyDie && MiniMT26) {
		if (Player) {
			MiniMT26->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(MiniMT26->GetActorLocation(), Player->GetActorLocation()));
		}
	}
}
