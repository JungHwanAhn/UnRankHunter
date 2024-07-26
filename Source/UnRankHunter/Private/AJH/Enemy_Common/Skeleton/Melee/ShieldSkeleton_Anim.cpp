#include "ShieldSkeleton_Anim.h"
#include "ShieldSkeleton.h"

UShieldSkeleton_Anim::UShieldSkeleton_Anim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Attack_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Skeleton/Melee/Montage/AJH_AM_HalfSkeleton_Attack.AJH_AM_HalfSkeleton_Attack'"));
	if (Attack_Montage.Succeeded()) {
		AttackMontage = Attack_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Die_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Skeleton/Melee/Montage/AJH_AM_Skeleton_Die.AJH_AM_Skeleton_Die'"));
	if (Die_Montage.Succeeded()) {
		DieMontage = Die_Montage.Object;
	}
}

void UShieldSkeleton_Anim::Attack(FString pattern)
{
	Montage_Play(AttackMontage);
	Montage_JumpToSection(*pattern);
}

void UShieldSkeleton_Anim::Die()
{
	Montage_Play(DieMontage);
}

void UShieldSkeleton_Anim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = TryGetPawnOwner();
	ShieldSkeleton = Cast<AShieldSkeleton>(Owner);
}

void UShieldSkeleton_Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (ShieldSkeleton) {
		velocity = ShieldSkeleton->GetVelocity();
		speed = velocity.Size2D();
	}
}
