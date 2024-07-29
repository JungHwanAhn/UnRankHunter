#include "HalfSkeleton.h"
#include "HalfSkeleton_Anim.h"
#include "AIController_Skeleton.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AHalfSkeleton::AHalfSkeleton()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AAIController_Skeleton::StaticClass();

	GetMesh()->SetRelativeLocation(FVector(0, 0, -130));
	GetMesh()->SetRelativeScale3D(FVector(1.5));

	SkeletonWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkeletonWeapon"));
	SkeletonWeapon->SetupAttachment(GetMesh());
	SkeletonWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SkeletonWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHand"));

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimInstance(TEXT("/Game/01_Core/AJH/Enemy/Skeleton/Melee/AJH_ABP_HalfSkeleton.AJH_ABP_HalfSkeleton_C"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	RHCollision->SetBoxExtent(FVector(20, 20, 80));
	RHCollision->SetRelativeLocation(FVector(0, 0, 75));

	GetCapsuleComponent()->InitCapsuleSize(30.0f, 125.0f);
}

void AHalfSkeleton::Attack()
{
	if (!bIsEnemyDie) {
		Super::Attack();

		damage = 20.0f;
		randomPattern = FMath::RandRange(1, 9);

		UHalfSkeleton_Anim* HalfSkeletonAnim = Cast<UHalfSkeleton_Anim>(GetMesh()->GetAnimInstance());
		if (HalfSkeletonAnim == nullptr) return;

		if (randomPattern <= 3) {
			HalfSkeletonAnim->Attack("Attack_A");
		}
		else if (randomPattern <= 6) {
			HalfSkeletonAnim->Attack("Attack_B");
		}
		else {
			HalfSkeletonAnim->Attack("Attack_C");
		}

		HalfSkeletonAnim->OnMontageEnded.RemoveDynamic(this, &AHalfSkeleton::OnAttackMontageEnded);
		HalfSkeletonAnim->OnMontageEnded.AddDynamic(this, &AHalfSkeleton::OnAttackMontageEnded);
	}
}

void AHalfSkeleton::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Super::OnAttackMontageEnded(Montage, bInterrupted);
}

void AHalfSkeleton::AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::AttackCheckOverlap(OverlapComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

float AHalfSkeleton::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float actualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (actualDamage > 0.f && !bIsEnemyDie) {
		enemyHP -= actualDamage;
		if (enemyHP <= 0.f) EnemyDie();
	}
	return actualDamage;
}

void AHalfSkeleton::EnemyDie()
{
	bIsEnemyDie = true;

	UHalfSkeleton_Anim* HalfSkeletonAnim = Cast<UHalfSkeleton_Anim>(GetMesh()->GetAnimInstance());
	if (HalfSkeletonAnim == nullptr) return;

	HalfSkeletonAnim->Die();

	FTimerHandle DieTimerHandle;
	FTimerDelegate CallEnemyDie = FTimerDelegate::CreateLambda([this]() { Super::EnemyDie(); });
	GetWorld()->GetTimerManager().SetTimer(DieTimerHandle, CallEnemyDie, dieDelay, false);
}

void AHalfSkeleton::OnSpawnFromPool_Implementation()
{
	Super::OnSpawnFromPool_Implementation();
}

void AHalfSkeleton::OnReturnToPool_Implementation()
{
	Super::OnReturnToPool_Implementation();
}

void AHalfSkeleton::OnCollisionStart_Implementation()
{
}

void AHalfSkeleton::OnCollisionEnd_Implementation()
{
}