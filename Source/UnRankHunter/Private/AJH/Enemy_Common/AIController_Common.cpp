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

	if (PlayerPawn && ControlledPawn->isActive) {
		SetFocus(PlayerPawn);
		MoveToActor(PlayerPawn, 130);
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
