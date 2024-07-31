#include "AIController_Elite.h"
#include "BaseEnemy_Common.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

void AAIController_Elite::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (PlayerPawn) {
		if (ControlledPawn->bIsActive && !ControlledPawn->bIsEnemyDie) {
			SetFocus(PlayerPawn);
			ControlledPawn->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(ControlledPawn->GetActorLocation(), PlayerPawn->GetActorLocation()));
			float distance = FVector::Distance(this->GetPawn()->GetActorLocation(), PlayerPawn->GetActorLocation());
			if (!ControlledPawn->bIsNear && distance < 3500.0f) {
				ControlledPawn->GetCharacterMovement()->MaxWalkSpeed = 850.0f;
				ControlledPawn->bIsNear = true;
			}

			if (!bIsAttack) {
				if (!bIsDash) {
					MoveToActor(PlayerPawn, 1500);
					if (distance < 1700.0f) {
						bIsAttack = true;
						bIsDash = true;
						attackDelay = 3.0f;
						GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, AttackCD, attackDelay, false);
						ControlledPawn->Attack();
					}
				}
				else {
					MoveToActor(PlayerPawn, 210);
					if (distance < 410.0f) {
						bIsAttack = true;
						int randomPattern = FMath::RandRange(1, 4);

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
		AttackCD = FTimerDelegate::CreateLambda([this]() {bIsAttack = false; attackDelay = 2.0f; });
	}
}
