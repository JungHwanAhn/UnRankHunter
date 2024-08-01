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
	void Attack();
	void Die();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MT26 State")
	float speed = 0.0f;

private:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* DieMontage;

	class APawn* Owner;
	class AMT26* MT26;

	FVector velocity;
};
