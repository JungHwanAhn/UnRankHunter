#include "Titan_Anim.h"
#include "Titan.h"

UTitan_Anim::UTitan_Anim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Attack_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Elite/Montage/AJH_AM_Titan_Attack.AJH_AM_Titan_Attack'"));
	if (Attack_Montage.Succeeded()) {
		AttackMontage = Attack_Montage.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Dash_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Elite/Montage/AJH_AM_Titan_DashAttack.AJH_AM_Titan_DashAttack'"));
	if (Dash_Montage.Succeeded()) {
		DashMontage = Dash_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Jump_Montage(TEXT("/Script/Engine.AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Elite/Montage/AJH_AM_Titan_JumpAttack.AJH_AM_Titan_JumpAttack'"));
	if (Jump_Montage.Succeeded()) {
		JumpMontage = Jump_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Die_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Elite/Montage/AJH_AM_Titan_Die.AJH_AM_Titan_Die'"));
	if (Die_Montage.Succeeded()) {
		DieMontage = Die_Montage.Object;
	}
}

void UTitan_Anim::Attack(FString pattern)
{
	Montage_Play(AttackMontage);
	Montage_JumpToSection(*pattern);
}

void UTitan_Anim::DashAttack()
{
	Montage_Play(DashMontage);
}

void UTitan_Anim::JumpAttack()
{
	Montage_Play(JumpMontage);
}

void UTitan_Anim::Die()
{
	Montage_Play(DieMontage);
}

void UTitan_Anim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = TryGetPawnOwner();
	Titan = Cast<ATitan>(Owner);
}

void UTitan_Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Titan) {
		velocity = Titan->GetVelocity();
		speed = velocity.Size2D();
	}
}