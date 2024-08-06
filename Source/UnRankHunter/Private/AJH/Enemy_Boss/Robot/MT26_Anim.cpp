#include "MT26_Anim.h"
#include "MT26.h"

UMT26_Anim::UMT26_Anim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		ChargingShot_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Boss/Montage/AJH_AM_MT26_ChargingShot.AJH_AM_MT26_ChargingShot'"));
	if (ChargingShot_Montage.Succeeded()) {
		ChargingShotMontage = ChargingShot_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Shelling_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Boss/Montage/AJH_AM_MT26_Shelling.AJH_AM_MT26_Shelling'"));
	if (Shelling_Montage.Succeeded()) {
		ShellingMontage = Shelling_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		ShellingToPlayer_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Boss/Montage/AJH_AM_MT26_ShellingToPlayer.AJH_AM_MT26_ShellingToPlayer'"));
	if (ShellingToPlayer_Montage.Succeeded()) {
		ShellingToPlayerMontage = ShellingToPlayer_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Die_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Boss/Montage/AJH_AM_MT26_Die.AJH_AM_MT26_Die'"));
	if (Die_Montage.Succeeded()) {
		DieMontage = Die_Montage.Object;
	}
}

void UMT26_Anim::Attack()
{
}

void UMT26_Anim::ChargingShot()
{
	Montage_Play(ChargingShotMontage);
}

void UMT26_Anim::Shelling()
{
	Montage_Play(ShellingMontage);
}

void UMT26_Anim::ShellingToPlayer()
{
	Montage_Play(ShellingToPlayerMontage);
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
