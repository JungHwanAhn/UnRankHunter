#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Titan_Anim.generated.h"

UCLASS()
class UNRANKHUNTER_API UTitan_Anim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UTitan_Anim();
	void Attack(FString pattern);
	void DashAttack();
	void JumpAttack();
	void Die();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Titan State")
	float speed = 0.0f;

private:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* DashMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* JumpMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* DieMontage;

	class APawn* Owner;
	class ATitan* Titan;

	FVector velocity;
};
