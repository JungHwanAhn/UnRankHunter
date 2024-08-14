#include "MiniMT26_Anim.h"
#include "MiniMT26.h"

UMiniMT26_Anim::UMiniMT26_Anim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		EnergyBall_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Boss/Montage/Plazma/AJH_AM_MT26_EnergyBall.AJH_AM_MT26_EnergyBall'"));
	if (EnergyBall_Montage.Succeeded()) {
		EnergyBallMontage = EnergyBall_Montage.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Shelling_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Boss/Montage/Shelling/AJH_AM_MT26_Shelling.AJH_AM_MT26_Shelling'"));
	if (Shelling_Montage.Succeeded()) {
		ShellingMontage = Shelling_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		ShellingToPlayer_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Boss/Montage/Shelling/AJH_AM_MT26_ShellingToPlayer.AJH_AM_MT26_ShellingToPlayer'"));
	if (ShellingToPlayer_Montage.Succeeded()) {
		ShellingToPlayerMontage = ShellingToPlayer_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		HomingRocket_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Boss/Montage/Shelling/AJH_AM_MT26_HomingRocket.AJH_AM_MT26_HomingRocket'"));
	if (HomingRocket_Montage.Succeeded()) {
		HomingRocketMontage = HomingRocket_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		LaserShot_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Boss/Montage/Laser/AJH_AM_MT26_LaserShot.AJH_AM_MT26_LaserShot'"));
	if (LaserShot_Montage.Succeeded()) {
		LaserShotMontage = LaserShot_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Die_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Boss/Montage/AJH_AM_MT26_Die.AJH_AM_MT26_Die'"));
	if (Die_Montage.Succeeded()) {
		DieMontage = Die_Montage.Object;
	}
}

void UMiniMT26_Anim::EnergyBall()
{
	Montage_Play(EnergyBallMontage);
}

void UMiniMT26_Anim::Shelling()
{
	Montage_Play(ShellingMontage);
}

void UMiniMT26_Anim::ShellingToPlayer()
{
	Montage_Play(ShellingToPlayerMontage);
}

void UMiniMT26_Anim::LaserShot()
{
	Montage_Play(LaserShotMontage);
}

void UMiniMT26_Anim::HomingRocket()
{
	Montage_Play(HomingRocketMontage);
}

void UMiniMT26_Anim::Die()
{
	Montage_Play(DieMontage);
}

void UMiniMT26_Anim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = TryGetPawnOwner();
	MiniMT26 = Cast<AMiniMT26>(Owner);
}

void UMiniMT26_Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (MiniMT26) {
		velocity = MiniMT26->GetVelocity();
		speed = velocity.Size2D();
	}
}
