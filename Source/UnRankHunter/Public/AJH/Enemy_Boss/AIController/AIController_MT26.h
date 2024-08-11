#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_MT26.generated.h"

UCLASS()
class UNRANKHUNTER_API AAIController_MT26 : public AAIController
{
	GENERATED_BODY()
	
public:
	AAIController_MT26();

	virtual void OnPossess(APawn* InPawn) override;
	void StopAI();
	void StartAI();

	static const FName TargetKey;
	static const FName FormKey;
	static const FName bIsPlazmaAreaKey;
	static const FName bIsChangeFormKey;
	static const FName MaxPatternCountKey;
	static const FName RandomPatternKey;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float enemyRotator_Y = 1500.0f;

	UPROPERTY(BlueprintReadWrite)
	bool bIsLaserAttack = false;

	UPROPERTY(BlueprintReadOnly)
	FVector AdjustedPlayerLocation;

private:
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, Category = "BehaviorTree")
	class UBehaviorTree* BTEnemy;

	UPROPERTY(VisibleAnywhere, Category = "BehaviorTree")
	class UBlackboardData* BBEnemy;

	class AActor* Player;
	class AMT26* MT26;
};
