#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_Bomb.generated.h"

UCLASS()
class UNRANKHUNTER_API AAIController_Bomb : public AAIController
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
	int32 attackDelay = 5;
};
