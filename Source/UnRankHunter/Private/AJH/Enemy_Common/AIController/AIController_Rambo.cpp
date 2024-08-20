#include "AIController_Rambo.h"
#include "Rambo.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

void AAIController_Rambo::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

    if (PlayerPawn) {
        if (Rambo->bIsActive && !Rambo->bIsEnemyDie) {
            SetFocus(PlayerPawn);
            lastEnemyScan += DeltaSeconds;
            Rambo->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(Rambo->GetActorLocation(), PlayerPawn->GetActorLocation()));
            float distance = FVector::Distance(this->GetPawn()->GetActorLocation(), PlayerPawn->GetActorLocation());
            if (!Rambo->bIsNear && distance < 4000.0f) {
                Rambo->GetCharacterMovement()->MaxWalkSpeed = 800.0f;
                Rambo->bIsNear = true;
            }

            if (!bIsAttack) {
                FVector Destination = PlayerPawn->GetActorLocation();
                FVector CurrentLocation = Rambo->GetActorLocation();
                if (lastEnemyScan >= enemyScanInterval)
                {
                    EnemyScan();
                    lastEnemyScan = 0.0f;
                }

                FVector AdjustedDestination = Destination + AvoidanceVector;
                EPathFollowingRequestResult::Type MoveResult = MoveToLocation(AdjustedDestination, acceptanceRadius);
                if (MoveResult == EPathFollowingRequestResult::Failed || MoveResult == EPathFollowingResult::Invalid)
                {
                    MoveResult = MoveToLocation(PlayerPawn->GetActorLocation(), acceptanceRadius);
                }

                if (distance < 2000.0f)
                {
                    bIsAttack = true;
                    FTimerHandle AttackTimerHandle;
                    FTimerDelegate AttackCD = FTimerDelegate::CreateLambda([this]() { bIsAttack = false; });
                    GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, AttackCD, attackDelay, false);
                    Rambo->Attack();
                }
            }
        }
        else {
            ClearFocus(EAIFocusPriority::Gameplay);
        }
    }
}

void AAIController_Rambo::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn) {
		PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		Rambo = Cast<ARambo>(InPawn);
	}
}

void AAIController_Rambo::EnemyScan()
{
	if (Rambo)
	{
		FVector CurrentLocation = Rambo->GetActorLocation();

		TArray<AActor*> OverlappingEnemies;
        TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
        ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));
        UKismetSystemLibrary::SphereOverlapActors(GetWorld(), CurrentLocation, avoidanceRadius, ObjectTypes, ABaseEnemy_Common::StaticClass(), TArray<AActor*>(), OverlappingEnemies);

		AvoidanceVector = FVector::ZeroVector;
		for (AActor* Actor : OverlappingEnemies)
		{
            if (Actor && Actor->GetOwner() != this) {
                FVector ToOther = CurrentLocation - Actor->GetActorLocation();
                float DistanceToOther = ToOther.Size();
                if (DistanceToOther < avoidanceRadius)
                {
                    AvoidanceVector += ToOther.GetSafeNormal() * (avoidanceRadius - DistanceToOther) * avoidanceStrength;
                }
            }
		}
	}
}