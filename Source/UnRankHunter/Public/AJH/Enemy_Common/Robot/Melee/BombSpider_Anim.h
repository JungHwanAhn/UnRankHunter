#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BombSpider_Anim.generated.h"

UCLASS()
class UNRANKHUNTER_API UBombSpider_Anim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UBombSpider_Anim();
	void Attack(FString pattern);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BombSpider State")
	float speed = 0.0f;
private:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* AttackMontage;

	class APawn* Owner;
	class ABombSpider* BombSpider;

	FVector velocity;
};
