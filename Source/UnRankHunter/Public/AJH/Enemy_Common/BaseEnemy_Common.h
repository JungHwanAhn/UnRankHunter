#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CollisionController.h"
#include "Poolable.h"
#include "BlueprintInterface/EnemyStatProvider.h"
#include "BaseEnemy_Common.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEnd);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDeath, class ABaseEnemy_Common*, Invoker);

UCLASS()
class UNRANKHUNTER_API ABaseEnemy_Common : public ACharacter, public ICollisionController, public IPoolable, public IEnemyStatProvider
{
	GENERATED_BODY()

public:
	ABaseEnemy_Common();

	UFUNCTION()
	virtual void Attack();

	virtual void DashAttack();
	virtual void JumpAttack();

	UFUNCTION(BlueprintCallable)
	void Slow(float Value, bool bIsSlow);

	UPROPERTY(BlueprintReadWrite)
	bool bIsDamage = false;

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
	float increaseXP = 10.0f;	// Deprecated. cause: unusing variable. kyg 08-26 modified.

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnCollisionStart_Implementation() override;
	virtual void OnCollisionEnd_Implementation() override;

	virtual void OnSpawnFromPool_Implementation() override;
	virtual void OnReturnToPool_Implementation() override;

	virtual float GetMoveSpeed_Implementation() override;

	FOnAttackEnd OnAttackEnd;

	bool bIsEnemyDie = false;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* LHCollision;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* RHCollision;

	bool bIsActive = false;
	bool bIsNear = false;
private:

	// KYG Extention
public:
	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void InitializeEnemyStat(float MaxHealth, float Damage, float MoveSpeed, float DropExp, int32 DropMoney, int32 DropToken);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy")
	FName EnemyID{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Stat")
	float BaseMaxHealth{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Stat")
	float BaseDamange{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Stat")
	float BaseMoveSpeed{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Stat")
	float BaseDropExp{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Stat")
	int32 BaseDropMoney{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Stat")
	int32 BaseDropToken{};


	// Event Dispatcher
public:
	UPROPERTY(BlueprintAssignable, Category = "Enemy")
	FOnEnemyDeath OnDeath;

};
