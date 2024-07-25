#include "ShieldSkeleton.h"
#include "HalfSkeleton_Anim.h"
#include "AIController_Common.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

AShieldSkeleton::AShieldSkeleton()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AAIController_Common::StaticClass();

	GetMesh()->SetRelativeLocation(FVector(0, 0, -100));
	GetMesh()->SetRelativeScale3D(FVector(1.1));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RightSkeletonWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightWeapon"));
	RightSkeletonWeapon->SetupAttachment(GetMesh());
	RightSkeletonWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHand"));

	LeftSkeletonWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield"));
	LeftSkeletonWeapon->SetupAttachment(GetMesh());
	LeftSkeletonWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("LeftHand"));

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimInstance(TEXT("/Game/01_Core/AJH/Enemy/Skeleton/Melee/AJH_ABP_HalfSkeleton.AJH_ABP_HalfSkeleton_C"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	RHCollision->SetBoxExtent(FVector(20, 20, 65));
	RHCollision->SetRelativeLocation(FVector(0, 0, 50));
	GetCapsuleComponent()->InitCapsuleSize(20.0f, 90.0f);
}

void AShieldSkeleton::Attack()
{
	if (!bIsEnemyDie) {
		Super::Attack();

		damage = 20.0f;
		randomPattern = FMath::RandRange(1, 9);

		UHalfSkeleton_Anim* ShieldSkeletonAnim = Cast<UHalfSkeleton_Anim>(GetMesh()->GetAnimInstance());
		if (ShieldSkeletonAnim == nullptr) return;

		if (randomPattern <= 3) {
			ShieldSkeletonAnim->Attack("Attack_A");
		}
		else if (randomPattern <= 6) {
			ShieldSkeletonAnim->Attack("Attack_B");
		}
		else {
			ShieldSkeletonAnim->Attack("Attack_C");
		}

		ShieldSkeletonAnim->OnMontageEnded.RemoveDynamic(this, &AShieldSkeleton::OnAttackMontageEnded);
		ShieldSkeletonAnim->OnMontageEnded.AddDynamic(this, &AShieldSkeleton::OnAttackMontageEnded);
	}
}

void AShieldSkeleton::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Super::OnAttackMontageEnded(Montage, bInterrupted);
}

void AShieldSkeleton::AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::AttackCheckOverlap(OverlapComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

float AShieldSkeleton::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float actualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (actualDamage > 0.f && !bIsEnemyDie) {
		shieldSkeletonHP -= actualDamage;
		if (shieldSkeletonHP <= 0.f) EnemyDie();
	}
	return actualDamage;
}

void AShieldSkeleton::EnemyDie()
{
	bIsEnemyDie = true;

	UHalfSkeleton_Anim* ShieldSkeletonAnim = Cast<UHalfSkeleton_Anim>(GetMesh()->GetAnimInstance());
	if (ShieldSkeletonAnim == nullptr) return;

	ShieldSkeletonAnim->Die();

	FTimerHandle DieTimerHandle;
	FTimerDelegate CallEnemyDie = FTimerDelegate::CreateLambda([this]() { Super::EnemyDie(); });
	GetWorld()->GetTimerManager().SetTimer(DieTimerHandle, CallEnemyDie, dieDelay, false);
}

void AShieldSkeleton::OnSpawnFromPool_Implementation()
{
	Super::OnSpawnFromPool_Implementation();
}

void AShieldSkeleton::OnReturnToPool_Implementation()
{
	Super::OnReturnToPool_Implementation();
}

void AShieldSkeleton::OnCollisionStart_Implementation()
{
}

void AShieldSkeleton::OnCollisionEnd_Implementation()
{
}