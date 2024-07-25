#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy_Common.h"
#include "BombSpider.generated.h"

UCLASS()
class UNRANKHUNTER_API ABombSpider : public ABaseEnemy_Common
{
	GENERATED_BODY()
	
public:
	ABombSpider();

	virtual void Attack() override;
	virtual void OnSpawnFromPool_Implementation() override;
	virtual void OnReturnToPool_Implementation() override;
	virtual void EnemyDie() override;

private:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
