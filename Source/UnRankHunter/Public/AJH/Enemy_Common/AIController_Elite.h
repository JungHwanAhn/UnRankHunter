#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_Elite.generated.h"

UCLASS()
class UNRANKHUNTER_API AAIController_Elite : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnPossess(APawn* InPawn) override;
private:
	class APawn* PlayerPawn;
	class ABaseEnemy_Common* ControlledPawn;

	bool bIsAttack = false;
	float attackDelay = 2.5;

	bool bIsDash = false;
};
