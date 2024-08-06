#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy_Common.h"
#include "MT26.generated.h"

UCLASS()
class UNRANKHUNTER_API AMT26 : public ABaseEnemy_Common
{
	GENERATED_BODY()
	
public:
	AMT26();

	virtual void BeginPlay() override;
	void EnergyBall();
	void Shelling();
	void ShellingToPlayer();
	void LaserBeam();
	void LaserShot(); 
	void MultiLaserShot();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CPP Function")
	void SpawnShelling();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable , Category = "CPP Function")
	void AimToValue(float location_Y, FName Pattern);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CPP Function")
	void ReturnAim(float location_Y);

	virtual void OnSpawnFromPool_Implementation() override;
	virtual void OnReturnToPool_Implementation() override;
	virtual void OnCollisionStart_Implementation() override;
	virtual void OnCollisionEnd_Implementation() override;

	UPROPERTY(BlueprintReadWrite)
	class AAIController_Boss* AIController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Arrow")
	class UArrowComponent* ShotDirection;

	float chargingLocation = 0.0f;

private:
	virtual void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted) override;
	virtual void AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void EnemyDie() override;

	class UMT26_Anim* MT26Anim;

	float mt26HP = 200;
};