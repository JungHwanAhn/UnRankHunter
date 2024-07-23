#include "AIController_Elite.h"
#include "BaseEnemy_Common.h"
#include "Kismet/GameplayStatics.h"

void AAIController_Elite::BeginPlay()
{
	Super::BeginPlay();
}

void AAIController_Elite::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (PlayerPawn) {
		if (ControlledPawn->bIsActive && !ControlledPawn->bIsEnemyDie) {
			SetFocus(PlayerPawn);

			if (!bIsAttack) {
				if (!bIsDash) {
					MoveToActor(PlayerPawn, 1500);
					float distance = FVector::Distance(this->GetPawn()->GetActorLocation(), PlayerPawn->GetActorLocation());
					if (distance < 1700.0f) {
						bIsAttack = true;
						bIsDash = true;
						FTimerHandle AttackTimerHandle;
						FTimerDelegate AttackCD = FTimerDelegate::CreateLambda([this]() {bIsAttack = false; });
						GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, AttackCD, attackDelay, false);
						ControlledPawn->DashAttack();
					}
				}
				else {
					MoveToActor(PlayerPawn, 210);
					float distance = FVector::Distance(this->GetPawn()->GetActorLocation(), PlayerPawn->GetActorLocation());
					if (distance < 410.0f) {
						bIsAttack = true;
						int randomPattern = FMath::RandRange(1, 4);
						FTimerHandle AttackTimerHandle;
						FTimerDelegate AttackCD = FTimerDelegate::CreateLambda([this]() {bIsAttack = false; attackDelay = 3.0f; });
						if (randomPattern <= 3) {
							GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, AttackCD, attackDelay, false);
							ControlledPawn->Attack();
						}
						else {
							attackDelay = 4.0f;
							GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, AttackCD, attackDelay, false);
							ControlledPawn->JumpAttack();
						}
					}
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

void AAIController_Elite::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn) {
		PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		ControlledPawn = Cast<ABaseEnemy_Common>(InPawn);
	}
}
