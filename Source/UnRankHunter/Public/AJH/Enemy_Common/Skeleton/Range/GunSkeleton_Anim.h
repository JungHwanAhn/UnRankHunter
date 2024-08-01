#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GunSkeleton_Anim.generated.h"

UCLASS()
class UNRANKHUNTER_API UGunSkeleton_Anim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UGunSkeleton_Anim();
	void Attack();
	void Die();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GunSkeleton State")
	float speed = 0.0f;

private:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* DieMontage;

	class APawn* Owner;
	class AGunSkeleton* GunSkeleton;

	FVector velocity;
};
