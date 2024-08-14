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

	UFUNCTION()
	virtual void Attack();

	virtual void DashAttack();
	virtual void JumpAttack();

	UFUNCTION(BlueprintCallable)
	void Slow(float Value);

protected:
	UFUNCTION()
	virtual void OnAttackMontageEnded(UAnimMontage* Montage, bool Interrupted);

	UFUNCTION()
	virtual void AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void EnemyDie();

	float randomPattern = 0.0f;
	float damage = 0.0f;
	float dieDelay = 3.0f;
	float enemyHP = 100.0f;
	float increaseXP = 10.0f;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnCollisionStart_Implementation() override;
	virtual void OnCollisionEnd_Implementation() override;

	virtual void OnSpawnFromPool_Implementation() override;
	virtual void OnReturnToPool_Implementation() override;

	FOnAttackEnd OnAttackEnd;

	bool bIsEnemyDie = false;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* LHCollision;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* RHCollision;

	bool bIsActive = false;
	bool bIsNear = false;
private:
	
};
