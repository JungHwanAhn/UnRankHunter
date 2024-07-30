#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SkeletonWarrior_Anim.generated.h"

UCLASS()
class UNRANKHUNTER_API USkeletonWarrior_Anim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	USkeletonWarrior_Anim();
	void Attack(FString pattern);
	void Die();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SkeletonWarrior State")
	float speed = 0.0f;

private:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* DieMontage;

	class APawn* Owner;
	class ASkeletonWarrior* SkeletonWarrior;

	FVector velocity;
};
