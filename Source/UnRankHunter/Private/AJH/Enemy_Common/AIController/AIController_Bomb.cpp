#include "AIController_Bomb.h"
#include "BaseEnemy_Common.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

void AAIController_Bomb::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (PlayerPawn) {
        if (ControlledPawn->bIsActive && !ControlledPawn->bIsEnemyDie) {
            SetFocus(PlayerPawn);
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

            if (!bIsAttack) {
                MoveToActor(PlayerPawn, 100);
                if (distance < 200.0f)
                {
                    bIsAttack = true;
                    FTimerHandle AttackTimerHandle;
                    FTimerDelegate AttackCD = FTimerDelegate::CreateLambda([this]() { bIsAttack = false; });
                    GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, AttackCD, attackDelay, false);
                    ControlledPawn->Attack();
                }
            }
        }
    }
}

void AAIController_Bomb::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (InPawn) {
        PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        ControlledPawn = Cast<ABaseEnemy_Common>(InPawn);
    }
}
