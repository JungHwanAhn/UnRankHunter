#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_Common.generated.h"

UCLASS()
class UNRANKHUNTER_API AAIController_Common : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnPossess(APawn* InPawn) override;
private:
	class APawn* PlayerPawn;
	class ABaseEnemy_Common* ControlledPawn;
};
