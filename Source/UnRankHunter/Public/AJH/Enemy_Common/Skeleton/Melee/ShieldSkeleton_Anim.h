#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ShieldSkeleton_Anim.generated.h"

UCLASS()
class UNRANKHUNTER_API UShieldSkeleton_Anim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UShieldSkeleton_Anim();
	void Attack(FString pattern);
	void Die();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ShieldSkeleton State")
	float speed = 0.0f;

private:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* DieMontage;

	class APawn* Owner;
	class AShieldSkeleton* ShieldSkeleton;

	FVector velocity;
};
