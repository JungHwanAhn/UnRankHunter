#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CollisionController.h"
#include "Poolable.h"
#include "BaseEnemy_Common.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEnd);

UCLASS()
class UNRANKHUNTER_API ABaseEnemy_Common : public ACharacter, public ICollisionController, public IPoolable
{
	GENERATED_BODY()

public:
	ABaseEnemy_Common();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnAttackMontageEnded(UAnimMontage* Montage, bool Interrupted);

	UFUNCTION()
	virtual void AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void EnemyDie();

	FTimerHandle DieTimerHandle;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnCollisionStart_Implementation() override;
	virtual void OnCollisionEnd_Implementation() override;

	virtual void OnSpawnFromPool_Implementation() override;
	virtual void OnReturnToPool_Implementation() override;

	FOnAttackEnd OnAttackEnd;

	bool isEnemyDie = false;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* LHCollision;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* RHCollision;

	bool isActive = false;
private:
	
};
