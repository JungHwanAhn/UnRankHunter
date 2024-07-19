#include "Rambo_Anim.h"
#include "Rambo.h"

URambo_Anim::URambo_Anim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Attack_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Range/Montage/AJH_AM_Rambo_Attack.AJH_AM_Rambo_Attack'"));
	if (Attack_Montage.Succeeded()) {
		AttackMontage = Attack_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Die_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Range/Montage/AJH_AM_Rambo_Die.AJH_AM_Rambo_Die'"));
	if (Die_Montage.Succeeded()) {
		DieMontage = Die_Montage.Object;
	}
}

void URambo_Anim::Attack()
{
	Montage_Play(AttackMontage);

}

void URambo_Anim::Die()
{
	Montage_Play(DieMontage);
}

void URambo_Anim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = TryGetPawnOwner();
	Rambo = Cast<ARambo>(Owner);
}

void URambo_Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Rambo) {
		velocity = Rambo->GetVelocity();
		speed = velocity.Size2D();
	}
}
