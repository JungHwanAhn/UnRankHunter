#include "HalfSkeleton_Anim.h"
#include "HalfSkeleton.h"

UHalfSkeleton_Anim::UHalfSkeleton_Anim()
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

void UHalfSkeleton_Anim::Attack(FString pattern)
{
	Montage_Play(AttackMontage);
	Montage_JumpToSection(*pattern);
}

void UHalfSkeleton_Anim::Die()
{
	Montage_Play(DieMontage);
}

void UHalfSkeleton_Anim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = TryGetPawnOwner();
	HalfSkeleton = Cast<AHalfSkeleton>(Owner);
}

void UHalfSkeleton_Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (HalfSkeleton) {
		velocity = HalfSkeleton->GetVelocity();
		speed = velocity.Size2D();
	}
}
