#include "Spider_Anim.h"
#include "Spider.h"

USpider_Anim::USpider_Anim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Attack_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Range/Montage/AJH_AM_Spider_Attack.AJH_AM_Spider_Attack'"));
	if (Attack_Montage.Succeeded()) {
		AttackMontage = Attack_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Die_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Range/Montage/AJH_AM_Spider_Die.AJH_AM_Spider_Die'"));
	if (Die_Montage.Succeeded()) {
		DieMontage = Die_Montage.Object;
	}
}

void USpider_Anim::Attack()
{
	Montage_Play(AttackMontage);
}

void USpider_Anim::Die()
{
	Montage_Play(DieMontage);
}

void USpider_Anim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = TryGetPawnOwner();
	Spider = Cast<ASpider>(Owner);
}

void USpider_Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Spider) {
		velocity = Spider->GetVelocity();
		speed = velocity.Size2D();
	}
}
