#include "AIController_Range.h"
#include "BaseEnemy_Common.h"
#include "Rambo.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

void AAIController_Range::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (PlayerPawn) {
		if (ControlledPawn->bIsActive && !ControlledPawn->bIsEnemyDie) {
			SetFocus(PlayerPawn);
			ControlledPawn->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(ControlledPawn->GetActorLocation(), PlayerPawn->GetActorLocation()));
			float distance = FVector::Distance(this->GetPawn()->GetActorLocation(), PlayerPawn->GetActorLocation());

			if (!ControlledPawn->bIsNear) {
				if (distance > 3500.0f) {
					ControlledPawn->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
				}
				else {
					ControlledPawn->GetCharacterMovement()->MaxWalkSpeed = 850.0f;
					ControlledPawn->bIsNear = true;
				}
			}
			MoveToActor(PlayerPawn, moveRange);

			if (distance < 1700.0f) {
				FVector StartLocation = ControlledPawn->GetActorLocation();
				FVector EndLocation = PlayerPawn->GetActorLocation();
				FHitResult HitResult;
				FCollisionQueryParams CollisionParams;
				CollisionParams.AddIgnoredActor(ControlledPawn);

				bool bPlayerInSight = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams);

				if (bPlayerInSight && HitResult.GetActor() == PlayerPawn) {
					moveRange = 1500.0f;
					if (!bIsAttack) {
						bIsAttack = true;
						FTimerHandle AttackTimerHandle;
						FTimerDelegate AttackCD = FTimerDelegate::CreateLambda([this]() {bIsAttack = false; });
						GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, AttackCD, attackDelay, false);
						ControlledPawn->Attack();
					}
				}
				else {
					moveRange = 150.0f;
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
		if (ControlledPawn->IsA(ARambo::StaticClass())) {
			attackDelay = 2.5f;
		}
		else {
			attackDelay = 1.0f;
		}
	}
}
