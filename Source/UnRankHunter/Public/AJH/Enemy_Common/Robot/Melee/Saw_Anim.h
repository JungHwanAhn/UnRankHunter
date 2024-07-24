#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Saw_Anim.generated.h"

UCLASS()
class UNRANKHUNTER_API USaw_Anim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	USaw_Anim();
	void Attack();
	void Die();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Saw State")
	float speed = 0.0f;

private:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* DieMontage;

	class APawn* Owner;
	class ASaw* Saw;

	FVector velocity;
};
