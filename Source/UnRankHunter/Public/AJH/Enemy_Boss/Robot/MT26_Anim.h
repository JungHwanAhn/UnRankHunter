#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MT26_Anim.generated.h"

UCLASS()
class UNRANKHUNTER_API UMT26_Anim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMT26_Anim();
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
	void Die();

private:
	virtual void NativeInitializeAnimation() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* EnergyBallMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* PlazmaAreaMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* PlazmaToPlayerMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* ShellingMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* ShellingToPlayerMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* HomingRocketMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* LaserBeamMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* LaserShotMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* MultiLaserShotMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* ChangeFormMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* DieMontage;

	class APawn* Owner;
	class AMT26* MT26;
};
