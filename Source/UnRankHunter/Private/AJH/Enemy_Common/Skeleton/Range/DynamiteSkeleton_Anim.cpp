#include "DynamiteSkeleton_Anim.h"
#include "DynamiteSkeleton.h"

UDynamiteSkeleton_Anim::UDynamiteSkeleton_Anim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Attack_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Skeleton/Range/Montage/AJH_AM_DynamiteSkeleton_Attack.AJH_AM_DynamiteSkeleton_Attack'"));
	if (Attack_Montage.Succeeded()) {
		AttackMontage = Attack_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Die_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Skeleton/Range/Montage/AJH_AM_GunSkeleton_Die.AJH_AM_GunSkeleton_Die'"));
	if (Die_Montage.Succeeded()) {
		DieMontage = Die_Montage.Object;
	}
}

void UDynamiteSkeleton_Anim::Attack()
{
	Montage_Play(AttackMontage);
}

void UDynamiteSkeleton_Anim::Die()
{
	Montage_Play(DieMontage);
}

void UDynamiteSkeleton_Anim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = TryGetPawnOwner();
	DynamiteSkeleton = Cast<ADynamiteSkeleton>(Owner);
}

void UDynamiteSkeleton_Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (DynamiteSkeleton) {
		velocity = DynamiteSkeleton->GetVelocity();
		speed = velocity.Size2D();
	}
}
