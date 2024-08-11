#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MiniMT26_Anim.generated.h"

UCLASS()
class UNRANKHUNTER_API UMiniMT26_Anim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMiniMT26_Anim();
	void EnergyBall();
	void Shelling();
	void ShellingToPlayer();
	void LaserShot();
	void HomingRocket();
	void Die();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MT26 State")
	float speed = 0.0f;

private:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* EnergyBallMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* ShellingMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* ShellingToPlayerMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* HomingRocketMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* LaserShotMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* DieMontage;

	class APawn* Owner;
	class AMiniMT26* MiniMT26;

	FVector velocity;
};
