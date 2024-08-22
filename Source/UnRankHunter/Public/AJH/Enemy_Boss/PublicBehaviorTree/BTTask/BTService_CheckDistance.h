#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckDistance.generated.h"

UCLASS()
class UNRANKHUNTER_API UBTService_CheckDistance : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_CheckDistance();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	bool bIsAttack = false;

	class AMiniMT26* MiniMT26;
	class AActor* Player;
};