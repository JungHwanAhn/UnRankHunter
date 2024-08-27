#include "AIController_Spider.h"
#include "Spider.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

void AAIController_Spider::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

    if (PlayerPawn) {
        if (Spider->bIsActive && !Spider->bIsEnemyDie) {
            SetFocus(PlayerPawn);
            lastEnemyScan += DeltaSeconds;
            Spider->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(Spider->GetActorLocation(), PlayerPawn->GetActorLocation()));
            float distance = FVector::Distance(this->GetPawn()->GetActorLocation(), PlayerPawn->GetActorLocation());
            if (!Spider->bIsNear && distance < 4000.0f) {
                Spider->GetCharacterMovement()->MaxWalkSpeed = Spider->GetBaseMoveSpeed();
                Spider->bIsNear = true;
            }

            if (!bIsAttack) {
                FVector Destination = PlayerPawn->GetActorLocation();
                FVector CurrentLocation = Spider->GetActorLocation();
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
                    Spider->Attack();
                }
            }
        }
        else {
            Spider->GetCharacterMovement()->StopActiveMovement();
            ClearFocus(EAIFocusPriority::Gameplay);
        }
    }
}

void AAIController_Spider::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn) {
		PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		Spider = Cast<ASpider>(InPawn);
	}
}

void AAIController_Spider::EnemyScan()
{
    if (Spider)
    {
        FVector CurrentLocation = Spider->GetActorLocation();

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