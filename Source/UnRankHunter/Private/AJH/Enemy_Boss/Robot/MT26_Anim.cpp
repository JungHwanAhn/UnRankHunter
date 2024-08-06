#include "MT26_Anim.h"
#include "MT26.h"

UMT26_Anim::UMT26_Anim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		EnergyBall_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Boss/Montage/AJH_AM_MT26_EnergyBall.AJH_AM_MT26_EnergyBall'"));
	if (EnergyBall_Montage.Succeeded()) {
		EnergyBallMontage = EnergyBall_Montage.Object;
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
		LaserBeam_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Boss/Montage/Laser/AJH_AM_MT26_LaserBeam.AJH_AM_MT26_LaserBeam'"));
	if (LaserBeam_Montage.Succeeded()) {
		LaserBeamMontage = LaserBeam_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		LaserShot_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Boss/Montage/Laser/AJH_AM_MT26_LaserShot.AJH_AM_MT26_LaserShot'"));
	if (LaserShot_Montage.Succeeded()) {
		LaserShotMontage = LaserShot_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		MultiLaserShot_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Boss/Montage/Laser/AJH_AM_MT26_MultiLaserShot.AJH_AM_MT26_MultiLaserShot'"));
	if (MultiLaserShot_Montage.Succeeded()) {
		MultiLaserShotMontage = MultiLaserShot_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		Die_Montage(TEXT("AnimMontage'/Game/01_Core/AJH/Enemy/Robot/Boss/Montage/AJH_AM_MT26_Die.AJH_AM_MT26_Die'"));
	if (Die_Montage.Succeeded()) {
		DieMontage = Die_Montage.Object;
	}
}

void UMT26_Anim::EnergyBall()
{
	Montage_Play(EnergyBallMontage);
}

void UMT26_Anim::Shelling()
{
	Montage_Play(ShellingMontage);
}

void UMT26_Anim::ShellingToPlayer()
{
	Montage_Play(ShellingToPlayerMontage);
}

void UMT26_Anim::LaserBeam()
{
	Montage_Play(LaserBeamMontage);
}

void UMT26_Anim::LaserShot()
{
	Montage_Play(LaserShotMontage);
}

void UMT26_Anim::MultiLaserShot()
{
	Montage_Play(MultiLaserShotMontage);
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
