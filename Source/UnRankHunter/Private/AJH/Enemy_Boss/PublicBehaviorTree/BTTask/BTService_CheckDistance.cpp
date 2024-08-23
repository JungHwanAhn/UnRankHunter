#include "BTService_CheckDistance.h"
#include "MiniMT26.h"
#include "AIController_MiniMT26.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_CheckDistance::UBTService_CheckDistance()
{
	NodeName = TEXT("Check Distance");
	bNotifyBecomeRelevant = true;
}

void UBTService_CheckDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (MiniMT26 && Player) {
		if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(AAIController_MiniMT26::bIsCheckingKey)) {
			float distance = FVector::Distance(MiniMT26->GetActorLocation(), Player->GetActorLocation());
			if (distance > 2500) {
				OwnerComp.GetBlackboardComponent()->SetValueAsInt(AAIController_MiniMT26::MaxPatternCountKey, 3);
			}
			else if (distance > 800) {
				OwnerComp.GetBlackboardComponent()->SetValueAsInt(AAIController_MiniMT26::MaxPatternCountKey, 4);
			}
			else {
				OwnerComp.GetBlackboardComponent()->SetValueAsInt(AAIController_MiniMT26::MaxPatternCountKey, 5);
			}
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AAIController_MiniMT26::bIsCheckingKey, false);
		}
	}
}

void UBTService_CheckDistance::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	MiniMT26 = Cast<AMiniMT26>(OwnerComp.GetAIOwner()->GetPawn());
	if (!MiniMT26) {
		UE_LOG(LogTemp, Warning, TEXT("Check Distance Node Can't Casting MiniMT26 Enemy"));
		return;
	}

	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Player) {
		UE_LOG(LogTemp, Warning, TEXT("Check Distance Node Can't Casting Player"));
		return;
	}
}