#include "GunSkeleton_Anim.h"
#include "GunSkeleton.h"

UGunSkeleton_Anim::UGunSkeleton_Anim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Attack_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Skeleton/Range/Montage/AJH_AM_GunSkeleton_Attack.AJH_AM_GunSkeleton_Attack'"));
	if (Attack_Montage.Succeeded()) {
		AttackMontage = Attack_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Die_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Skeleton/Range/Montage/AJH_AM_GunSkeleton_Die.AJH_AM_GunSkeleton_Die'"));
	if (Die_Montage.Succeeded()) {
		DieMontage = Die_Montage.Object;
	}
}

void UGunSkeleton_Anim::Attack()
{
	Montage_Play(AttackMontage);
}

void UGunSkeleton_Anim::Die()
{
	Montage_Play(DieMontage);
}

void UGunSkeleton_Anim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = TryGetPawnOwner();
	GunSkeleton = Cast<AGunSkeleton>(Owner);
}

void UGunSkeleton_Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (GunSkeleton) {
		velocity = GunSkeleton->GetVelocity();
		speed = velocity.Size2D();
	}
}
