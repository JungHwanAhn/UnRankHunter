#include "AIController_MT26.h"
#include "MT26.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AAIController_MT26::TargetKey(TEXT("Target"));
const FName AAIController_MT26::FormKey(TEXT("Form"));
const FName AAIController_MT26::bIsPlazmaAreaKey(TEXT("bIsPlazmaArea"));
const FName AAIController_MT26::bIsChangeFormKey(TEXT("bIsChangeForm"));
const FName AAIController_MT26::MaxPatternCountKey(TEXT("MaxPatternCount"));
const FName AAIController_MT26::RandomPatternKey(TEXT("RandomPattern"));

AAIController_MT26::AAIController_MT26()
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

void AAIController_MT26::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	MT26 = Cast<AMT26>(InPawn);

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

void AAIController_MT26::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BehaviorTreeComponent) {
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}

void AAIController_MT26::StartAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BehaviorTreeComponent) {
		BehaviorTreeComponent->StartTree(*this->BTEnemy, EBTExecutionMode::Looped);
	}
}

void AAIController_MT26::Tick(float DeltaSeconds)
{
	if (!MT26->bIsEnemyDie && MT26) {
		if (Player) {
			AdjustedPlayerLocation = Player->GetActorLocation() + FVector(0.0f, enemyRotator_Y, -11500.0f);
			if (bIsLaserAttack) {
				AdjustedPlayerLocation.Y = enemyRotator_Y;
			}
			MT26->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(MT26->GetActorLocation(), AdjustedPlayerLocation));
		}
	}
}
