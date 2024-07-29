#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HalfSkeleton_Anim.generated.h"

UCLASS()
class UNRANKHUNTER_API UHalfSkeleton_Anim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UHalfSkeleton_Anim();
	void Attack(FString pattern);
	void Die();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HalfSkeleton State")
	float speed = 0.0f;

private:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* DieMontage;

	class APawn* Owner;
	class AHalfSkeleton* HalfSkeleton;

	FVector velocity;
};
