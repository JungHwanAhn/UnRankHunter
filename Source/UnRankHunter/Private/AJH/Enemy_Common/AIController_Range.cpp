#include "AIController_Range.h"
#include "BaseEnemy_Common.h"
#include "Kismet/GameplayStatics.h"

void AAIController_Range::BeginPlay()
{
	Super::BeginPlay();
}

void AAIController_Range::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (PlayerPawn) {
		if (ControlledPawn->bIsActive && !ControlledPawn->bIsEnemyDie) {
			SetFocus(PlayerPawn);

			if (!bIsAttack) {
				MoveToActor(PlayerPawn, 1500);

				float distance = FVector::Distance(this->GetPawn()->GetActorLocation(), PlayerPawn->GetActorLocation());
				if (distance < 1650.0f) {
					bIsAttack = true;
					FTimerHandle AttackTimerHandle;
					FTimerDelegate AttackCD = FTimerDelegate::CreateLambda([this]() {bIsAttack = false; });
					GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, AttackCD, attackDelay, false);
					ControlledPawn->Attack();
				}
			}
		}
		else {
			ClearFocus(EAIFocusPriority::Gameplay);
		}
	}
	else {
		ClearFocus(EAIFocusPriority::Gameplay);
	}
}

void AAIController_Range::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn) {
		PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		ControlledPawn = Cast<ABaseEnemy_Common>(InPawn);
	}
}
