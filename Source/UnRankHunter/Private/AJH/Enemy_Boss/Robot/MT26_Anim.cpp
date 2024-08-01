#include "MT26_Anim.h"
#include "MT26.h"

UMT26_Anim::UMT26_Anim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Die_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Boss/Montage/AJH_AM_MT26_Die.AJH_AM_MT26_Die'"));
	if (Die_Montage.Succeeded()) {
		DieMontage = Die_Montage.Object;
	}
}

void UMT26_Anim::Attack()
{
}

void UMT26_Anim::Die()
{
	Montage_Play(DieMontage);
}

void UMT26_Anim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = TryGetPawnOwner();
	MT26 = Cast<AMT26>(Owner);
}

void UMT26_Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (MT26) {
		velocity = MT26->GetVelocity();
		speed = velocity.Size2D();
	}
}
