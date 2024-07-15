#include "Android.h"
#include "Android_Anim.h"
#include "Components/BoxComponent.h"

AAndroid::AAndroid()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		AndroidMesh(TEXT("SkeletalMesh'/Game/02_Asset/Enemy/SteamPunkCollection/SteamPunkAndroid/Mesh/Character/SK_SteamPunkAndroid.SK_SteamPunkAndroid'"));
	if (AndroidMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(AndroidMesh.Object);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	AndroidWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AndroidWeapon"));
	AndroidWeapon->SetupAttachment(GetMesh());
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		WeaponMesh(TEXT("StaticMesh'/Game/02_Asset/Enemy/SteamPunkCollection/SteamPunkAndroid/Mesh/Weapon/AndroidWeapon.AndroidWeapon'"));
	if (WeaponMesh.Succeeded()) {
		AndroidWeapon->SetStaticMesh(WeaponMesh.Object);
		AndroidWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHand"));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimInstance(TEXT("/Game/01_Core/AJH/Enemy/Robot/Melee/AJH_ABP_Android.AJH_ABP_Android_C"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	RHCollision->SetBoxExtent(FVector(28, 16, 45));
	RHCollision->SetRelativeLocation(FVector(0, 0, 70));
}

void AAndroid::OnSpawnFromPool_Implementation()
{
	Super::OnSpawnFromPool_Implementation();
}

void AAndroid::OnReturnToPool_Implementation()
{
	Super::OnReturnToPool_Implementation();
}

void AAndroid::OnCollisionStart_Implementation()
{
}

void AAndroid::OnCollisionEnd_Implementation()
{
}

void AAndroid::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Super::OnAttackMontageEnded(Montage, bInterrupted);
}

void AAndroid::AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::AttackCheckOverlap(OverlapComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AAndroid::EnemyDie()
{
	Super::EnemyDie();
}
