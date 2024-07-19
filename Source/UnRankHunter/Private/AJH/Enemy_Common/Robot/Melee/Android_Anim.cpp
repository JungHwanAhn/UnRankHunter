#include "Android_Anim.h"
#include "Android.h"
#include "KismetAnimationLibrary.h"

UAndroid_Anim::UAndroid_Anim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Attack_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Melee/Montage/AJH_AM_Android_Attack.AJH_AM_Android_Attack'"));
	if (Attack_Montage.Succeeded()) {
		AttackMontage = Attack_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Die_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Melee/Montage/AJH_AM_Android_Die.AJH_AM_Android_Die'"));
	if (Die_Montage.Succeeded()) {
		DieMontage = Die_Montage.Object;
	}
}

void UAndroid_Anim::Attack(FString pattern)
{
	Montage_Play(AttackMontage);
	Montage_JumpToSection(*pattern);
}

void UAndroid_Anim::Die()
{
	Montage_Play(DieMontage);
}

void UAndroid_Anim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = TryGetPawnOwner();
	Android = Cast<AAndroid>(Owner);
}

void UAndroid_Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Android) {
		velocity = Android->GetVelocity();
		speed = velocity.Size2D();

		androidRotation = Android->GetActorRotation();
		direction = UKismetAnimationLibrary::CalculateDirection(velocity, androidRotation);
	}
}
