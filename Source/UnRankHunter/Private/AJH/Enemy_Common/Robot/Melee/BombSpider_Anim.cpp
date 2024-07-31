#include "BombSpider_Anim.h"
#include "BombSpider.h"

UBombSpider_Anim::UBombSpider_Anim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Attack_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Melee/Montage/AJH_AM_BombSpider_Attack.AJH_AM_BombSpider_Attack'"));
	if (Attack_Montage.Succeeded()) {
		AttackMontage = Attack_Montage.Object;
	}
}

void UBombSpider_Anim::Attack()
{
	Montage_Play(AttackMontage);
	BombSpider->EnemyDie();
}

void UBombSpider_Anim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = TryGetPawnOwner();
	BombSpider = Cast<ABombSpider>(Owner);
}

void UBombSpider_Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (BombSpider) {
		velocity = BombSpider->GetVelocity();
		speed = velocity.Size2D();
	}
}
