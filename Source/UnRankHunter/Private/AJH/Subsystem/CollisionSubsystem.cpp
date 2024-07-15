#include "CollisionSubsystem.h"
#include "CollisionController.h"
#include "Components/BoxComponent.h"
#include "BaseEnemy_Common.h"

void UCollisionSubsystem::CollisionStart(AActor* Actor, FString type)
{
	ICollisionController::Execute_OnCollisionStart(Actor);

	if (Actor->IsA(ABaseEnemy_Common::StaticClass())) {
		ABaseEnemy_Common* CommonEnemy = Cast<ABaseEnemy_Common>(Actor);
		if (type.Equals("Right")) {
			CommonEnemy->RHCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
		else if (type.Equals("Left")) {
			CommonEnemy->LHCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
	}
	
}

void UCollisionSubsystem::CollisionEnd(AActor* Actor)
{
	ICollisionController::Execute_OnCollisionEnd(Actor);

	if (Actor->IsA(ABaseEnemy_Common::StaticClass())) {
		ABaseEnemy_Common* CommonEnemy = Cast<ABaseEnemy_Common>(Actor);
		CommonEnemy->RHCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CommonEnemy->LHCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
