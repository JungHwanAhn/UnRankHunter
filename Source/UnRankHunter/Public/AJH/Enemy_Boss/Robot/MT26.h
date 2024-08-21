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
	void PlazmaArea();
	void PlazmaToPlayer();
	void Shelling();
	void ShellingToPlayer();
	void LaserBeam();
	void LaserShot(); 
	void MultiLaserShot();
	void HomingRocket();
	void ChangeForm();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CPP Function")
	void SpawnShelling();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CPP Function")
	void SpawnPlazmaArea();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable , Category = "CPP Function")
	void AimToValue(float location_Y, FName Pattern);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CPP Function")
	void ReturnAim(float location_Y);

	UFUNCTION(BlueprintImplementableEvent, Category = "CPP Function")
	void ChangeColor(FName Form);

	virtual void OnSpawnFromPool_Implementation() override;
	virtual void OnReturnToPool_Implementation() override;
	virtual void OnCollisionStart_Implementation() override;
	virtual void OnCollisionEnd_Implementation() override;

	UPROPERTY(BlueprintReadWrite)
	class AAIController_MT26* AIController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Arrow")
	class UArrowComponent* ShotDirection;

	bool bIsInitForm = false;

private:
	virtual void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted) override;
	virtual void AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void EnemyDie() override;

	class UMT26_Anim* MT26Anim;

	float mt26HP = 5000;
};