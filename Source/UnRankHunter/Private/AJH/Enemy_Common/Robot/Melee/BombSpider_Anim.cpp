#include "BombSpider_Anim.h"
#include "BombSpider.h"
#include "KismetAnimationLibrary.h"

UBombSpider_Anim::UBombSpider_Anim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Attack_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Melee/Montage/AJH_AM_BombSpider_Attack.AJH_AM_BombSpider_Attack'"));
	if (Attack_Montage.Succeeded()) {
		AttackMontage = Attack_Montage.Object;
	}
}

void UBombSpider_Anim::Attack(FString pattern)
{
	Montage_Play(AttackMontage);
	BombSpider->EnemyDie();
	FTimerHandle AttackTimerHandle;
	FTimerDelegate AttackCD = FTimerDelegate::CreateLambda([this]() { BombSpider->RadialDamage(); });
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, AttackCD, Montage_Play(AttackMontage), false);
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
