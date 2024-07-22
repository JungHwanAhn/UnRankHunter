#include "AIController_Common.h"
#include "BaseEnemy_Common.h"
#include "Kismet/GameplayStatics.h"

void AAIController_Common::BeginPlay()
{
	Super::BeginPlay();

}

void AAIController_Common::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (PlayerPawn) {
		if (ControlledPawn->bIsActive && !ControlledPawn->bIsEnemyDie) {
            SetFocus(PlayerPawn);
            lastEnemyScan += DeltaSeconds;

			if (!bIsAttack) {
                FVector Destination = PlayerPawn->GetActorLocation();
                FVector CurrentLocation = ControlledPawn->GetActorLocation();

                if (lastEnemyScan >= enemyScanInterval)
                {
                    EnemyScan();
                    lastEnemyScan = 0.0f;
                }

                FVector AdjustedDestination = Destination + AvoidanceVector;

                MoveToLocation(AdjustedDestination, acceptanceRadius);

                float distance = FVector::Distance(this->GetPawn()->GetActorLocation(), PlayerPawn->GetActorLocation());
                if (distance < 250.0f)
                {
                    bIsAttack = true;
                    FTimerHandle AttackTimerHandle;
                    FTimerDelegate AttackCD = FTimerDelegate::CreateLambda([this]() { bIsAttack = false; });
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

void AAIController_Common::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn) {
		PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		ControlledPawn = Cast<ABaseEnemy_Common>(InPawn);
	}
}

void AAIController_Common::EnemyScan()
{
    if (ControlledPawn)
    {
        FVector CurrentLocation = ControlledPawn->GetActorLocation();

        TArray<AActor*> OverlappingEnemies;
        UKismetSystemLibrary::SphereOverlapActors(GetWorld(), CurrentLocation, avoidanceRadius, TArray<TEnumAsByte<EObjectTypeQuery>>(), ABaseEnemy_Common::StaticClass(), TArray<AActor*>(), OverlappingEnemies);

        AvoidanceVector = FVector::ZeroVector;
        for (AActor* Actor : OverlappingEnemies)
        {
            if (Actor != ControlledPawn)
            {
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
