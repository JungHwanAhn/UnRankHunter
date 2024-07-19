#include "SteelGroot_Anim.h"
#include "SteelGroot.h"

USteelGroot_Anim::USteelGroot_Anim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Attack_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Melee/Montage/AJH_AM_SteelGroot_Attack.AJH_AM_SteelGroot_Attack'"));
	if (Attack_Montage.Succeeded()) {
		AttackMontage = Attack_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Die_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Melee/Montage/AJH_AM_SteelGroot_Die.AJH_AM_SteelGroot_Die'"));
	if (Die_Montage.Succeeded()) {
		DieMontage = Die_Montage.Object;
	}
}

void USteelGroot_Anim::Attack()
{
	Montage_Play(AttackMontage);
}

void USteelGroot_Anim::Die()
{
	Montage_Play(DieMontage);
}

void USteelGroot_Anim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = TryGetPawnOwner();
	SteelGroot = Cast<ASteelGroot>(Owner);
}

void USteelGroot_Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (SteelGroot) {
		velocity = SteelGroot->GetVelocity();
		speed = velocity.Size2D();
	}
}
