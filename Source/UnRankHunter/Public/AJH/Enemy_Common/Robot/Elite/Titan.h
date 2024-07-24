#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy_Common.h"
#include "Titan.generated.h"

UCLASS()
class UNRANKHUNTER_API ATitan : public ABaseEnemy_Common
{
	GENERATED_BODY()
	
public:
	ATitan();

	virtual void BeginPlay() override;
	virtual void Attack() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "CPP Function")
	void Dashing(FVector Destination);

	virtual void OnSpawnFromPool_Implementation() override;
	virtual void OnReturnToPool_Implementation() override;
	virtual void OnCollisionStart_Implementation() override;
	virtual void OnCollisionEnd_Implementation() override;

private:
	virtual void DashAttack() override;
	virtual void JumpAttack() override;
	virtual void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted) override;
	virtual void AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void EnemyDie() override;

	FTimerHandle DashTimerHandle;

	class UTitan_Anim* TitanAnim;

	bool bIsDash = false;
	float titanHP = 200;
};
