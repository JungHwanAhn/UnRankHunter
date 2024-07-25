#include "SkeletonWarrior_Anim.h"
#include "SkeletonWarrior.h"
#include "KismetAnimationLibrary.h"

USkeletonWarrior_Anim::USkeletonWarrior_Anim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Attack_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Skeleton/Melee/Montage/AJH_AM_SkeletonWarrior_Attack.AJH_AM_SkeletonWarrior_Attack'"));
	if (Attack_Montage.Succeeded()) {
		AttackMontage = Attack_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Die_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Skeleton/Melee/Montage/AJH_AM_Skeleton_Die.AJH_AM_Skeleton_Die'"));
	if (Die_Montage.Succeeded()) {
		DieMontage = Die_Montage.Object;
	}
}

void USkeletonWarrior_Anim::Attack(FString pattern)
{
	Montage_Play(AttackMontage);
	Montage_JumpToSection(*pattern);
}

void USkeletonWarrior_Anim::Die()
{
	Montage_Play(DieMontage);
}

void USkeletonWarrior_Anim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = TryGetPawnOwner();
	SkeletonWarrior = Cast<ASkeletonWarrior>(Owner);
}

void USkeletonWarrior_Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (SkeletonWarrior) {
		velocity = SkeletonWarrior->GetVelocity();
		speed = velocity.Size2D();
	}
}
