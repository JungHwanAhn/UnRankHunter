#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_ChangeForm.generated.h"

UCLASS()
class UNRANKHUNTER_API UBTService_ChangeForm : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_ChangeForm();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	float timeElapsed = 0.0f;
	float changeFormTime = 25.0f;
	bool bIsInitForm = false;
};