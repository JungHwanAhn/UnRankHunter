#include "Saw_Anim.h"
#include "Saw.h"

USaw_Anim::USaw_Anim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Attack_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Melee/Montage/AJH_AM_Saw_Attack.AJH_AM_Saw_Attack'"));
	if (Attack_Montage.Succeeded()) {
		AttackMontage = Attack_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Die_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Range/Montage/AJH_AM_Rambo_Die.AJH_AM_Rambo_Die'"));
	if (Die_Montage.Succeeded()) {
		DieMontage = Die_Montage.Object;
	}
}

void USaw_Anim::Attack()
{
	Montage_Play(AttackMontage);
}

void USaw_Anim::Die()
{
	Montage_Play(DieMontage);
}

void USaw_Anim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = TryGetPawnOwner();
	Saw = Cast<ASaw>(Owner);
}

void USaw_Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Saw) {
		velocity = Saw->GetVelocity();
		speed = velocity.Size2D();
	}
}
