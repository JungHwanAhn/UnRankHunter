#include "GunSkeleton.h"
#include "GunSkeleton_Anim.h"
#include "AIController_Range.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AGunSkeleton::AGunSkeleton()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AAIController_Range::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		GunSkeletonMesh(TEXT("SkeletalMesh'/Game/02_Asset/SkeletonCharacter/SkeletalMeshes/SkeletonCharacter/SKM_SkeletonCharacter_A.SKM_SkeletonCharacter_A'"));
	if (GunSkeletonMesh.Succeeded()) {
		GetMesh()->SetRelativeLocation(FVector(0, 0, -130));
		GetMesh()->SetRelativeScale3D(FVector(1.5));
		GetMesh()->SetSkeletalMesh(GunSkeletonMesh.Object);
		GetMesh()->GetOwner()->Tags.Add("GunSkeleton");
	}

	GunSkeletonWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunSkeletonWeapon"));
	GunSkeletonWeapon->SetupAttachment(GetMesh());
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		WeaponMesh(TEXT("StaticMesh'/Game/02_Asset/FPS_Weapon_Bundle/Weapons/Meshes/AR4/SM_AR4.SM_AR4'"));
	if (WeaponMesh.Succeeded()) {
		GunSkeletonWeapon->SetStaticMesh(WeaponMesh.Object);
		GunSkeletonWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GunSkeletonWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Gun"));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimInstance(TEXT("/Game/01_Core/AJH/Enemy/Skeleton/Range/AJH_ABP_GunSkeleton.AJH_ABP_GunSkeleton_C"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	GetCapsuleComponent()->InitCapsuleSize(30.0f, 125.0f);
}

void AGunSkeleton::Attack()
{
	if (!bIsEnemyDie) {
		
		Super::Attack();

		damage = 20.0f;

		UGunSkeleton_Anim* GunSkeletonAnim = Cast<UGunSkeleton_Anim>(GetMesh()->GetAnimInstance());
		if (GunSkeletonAnim == nullptr) return;

		GunSkeletonAnim->Attack();

		GunSkeletonAnim->OnMontageEnded.RemoveDynamic(this, &AGunSkeleton::OnAttackMontageEnded);
		GunSkeletonAnim->OnMontageEnded.AddDynamic(this, &AGunSkeleton::OnAttackMontageEnded);
	}
}

void AGunSkeleton::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Super::OnAttackMontageEnded(Montage, bInterrupted);
}

void AGunSkeleton::AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::AttackCheckOverlap(OverlapComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

float AGunSkeleton::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float actualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (actualDamage > 0.f && !bIsEnemyDie) {
		enemyHP -= actualDamage;
		if (enemyHP <= 0.f) EnemyDie();
	}
	return actualDamage;
}

void AGunSkeleton::EnemyDie()
{
	bIsEnemyDie = true;

	UGunSkeleton_Anim* GunSkeletonAnim = Cast<UGunSkeleton_Anim>(GetMesh()->GetAnimInstance());
	if (GunSkeletonAnim == nullptr) return;

	GunSkeletonAnim->Die();

	FTimerHandle DieTimerHandle;
	FTimerDelegate CallEnemyDie = FTimerDelegate::CreateLambda([this]() { Super::EnemyDie(); });
	GetWorld()->GetTimerManager().SetTimer(DieTimerHandle, CallEnemyDie, dieDelay, false);
}

void AGunSkeleton::OnSpawnFromPool_Implementation()
{
	Super::OnSpawnFromPool_Implementation();
}

void AGunSkeleton::OnReturnToPool_Implementation()
{
	Super::OnReturnToPool_Implementation();
}

void AGunSkeleton::OnCollisionStart_Implementation()
{
}

void AGunSkeleton::OnCollisionEnd_Implementation()
{
}