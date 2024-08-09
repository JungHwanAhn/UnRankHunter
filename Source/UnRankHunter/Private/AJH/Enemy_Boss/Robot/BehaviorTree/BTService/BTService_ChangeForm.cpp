#include "BTService_ChangeForm.h"
#include "MT26.h"
#include "AIController_Boss.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_ChangeForm::UBTService_ChangeForm()
{
	NodeName = TEXT("Change Form");
	Interval = 0.1f;
	timeElapsed = 0.0f;
}

void UBTService_ChangeForm::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsInitForm) {
		bIsInitForm = true;
		AMT26* MT26 = Cast<AMT26>(OwnerComp.GetAIOwner()->GetPawn());
		if (!MT26) {
			UE_LOG(LogTemp, Warning, TEXT("ChangeForm Node Can't Casting MT26 Enemy"));
			return;
		}
		UE_LOG(LogTemp, Warning, TEXT("Init"));
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AAIController_Boss::bIsChangeFormKey, true);
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(AAIController_Boss::MaxPatternCountKey, 2);
		OwnerComp.GetBlackboardComponent()->SetValueAsName(AAIController_Boss::FormKey, FName(TEXT("Laser")));
	}

	timeElapsed += DeltaSeconds;

	if (timeElapsed >= changeFormTime) {
		timeElapsed = 0.0f;
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AAIController_Boss::bIsChangeFormKey, true);

		FName CurrentForm = OwnerComp.GetBlackboardComponent()->GetValueAsName(AAIController_Boss::FormKey);

		if (CurrentForm == FName(TEXT("Laser"))) {
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AAIController_Boss::bIsPlazmaAreaKey, true);
			OwnerComp.GetBlackboardComponent()->SetValueAsName(AAIController_Boss::FormKey, FName(TEXT("Plazma")));
		}
		else if (CurrentForm == FName(TEXT("Plazma"))) {
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(AAIController_Boss::MaxPatternCountKey, 1);
			OwnerComp.GetBlackboardComponent()->SetValueAsName(AAIController_Boss::FormKey, FName(TEXT("Rocket")));
		}
		else if (CurrentForm == FName(TEXT("Rocket"))) {
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(AAIController_Boss::MaxPatternCountKey, 2);
			OwnerComp.GetBlackboardComponent()->SetValueAsName(AAIController_Boss::FormKey, FName(TEXT("Laser")));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Form Key is not valid"));
		}
	}
}