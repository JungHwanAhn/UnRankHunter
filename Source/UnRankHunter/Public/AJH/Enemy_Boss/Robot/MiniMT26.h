#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy_Common.h"
#include "MiniMT26.generated.h"

UCLASS()
class UNRANKHUNTER_API AMiniMT26 : public ABaseEnemy_Common
{
	GENERATED_BODY()
	
public:
	AMiniMT26();

	virtual void BeginPlay() override;
	void EnergyBall();
	void Shelling();
	void ShellingToPlayer();
	void LaserShot();
	void HomingRocket();

	virtual void OnSpawnFromPool_Implementation() override;
	virtual void OnReturnToPool_Implementation() override;
	virtual void OnCollisionStart_Implementation() override;
	virtual void OnCollisionEnd_Implementation() override;

	UPROPERTY(BlueprintReadWrite)
	class AAIController_MiniMT26* AIController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Arrow")
	class UArrowComponent* ShotDirection;

private:
	virtual void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted) override;
	virtual void AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void EnemyDie() override;

	class UMiniMT26_Anim* MiniMT26Anim;

	float miniMT26HP = 200;
};
