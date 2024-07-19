#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SteelGroot_Anim.generated.h"

UCLASS()
class UNRANKHUNTER_API USteelGroot_Anim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	USteelGroot_Anim();
	void Attack();
	void Die();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SteelGroot State")
	float speed = 0.0f;

private:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* DieMontage;

	class APawn* Owner;
	class ASteelGroot* SteelGroot;

	FVector velocity;
};
