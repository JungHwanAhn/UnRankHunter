#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Android_Anim.generated.h"

UCLASS()
class UNRANKHUNTER_API UAndroid_Anim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UAndroid_Anim();
	void Attack(FString pattern);
	void Die();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Android State")
	float speed = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Android State")
	float direction = 0.0f;

private:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* DieMontage;

	class APawn* Owner;
	class AAndroid* Android;

	FVector velocity;
	FRotator androidRotation;
};
