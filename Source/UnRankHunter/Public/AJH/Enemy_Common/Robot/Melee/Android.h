#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy_Common.h"
#include "Android.generated.h"

UCLASS()
class UNRANKHUNTER_API AAndroid : public ABaseEnemy_Common
{
	GENERATED_BODY()
	
public:
	AAndroid();

	virtual void Attack() override;
	
	virtual void OnSpawnFromPool_Implementation() override;
	virtual void OnReturnToPool_Implementation() override;
	virtual void OnCollisionStart_Implementation() override;
	virtual void OnCollisionEnd_Implementation() override;

private:
	virtual void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted) override;
	virtual void AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void EnemyDie() override;

	UPROPERTY(VisibleAnywhere, Category = "Weapon");
	class UStaticMeshComponent* AndroidWeapon;

	float androidHP = 100;
};
