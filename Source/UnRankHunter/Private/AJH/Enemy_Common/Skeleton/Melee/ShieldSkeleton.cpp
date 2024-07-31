#include "ShieldSkeleton.h"
#include "ShieldSkeleton_Anim.h"
#include "AIController_Skeleton.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

AShieldSkeleton::AShieldSkeleton()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AAIController_Skeleton::StaticClass();

	GetMesh()->SetRelativeLocation(FVector(0, 0, -130));
	GetMesh()->SetRelativeScale3D(FVector(1.5));

	RightSkeletonWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightWeapon"));
	RightSkeletonWeapon->SetupAttachment(GetMesh());
	RightSkeletonWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightSkeletonWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHand"));

	LeftSkeletonWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield"));
	LeftSkeletonWeapon->SetupAttachment(GetMesh());
	LeftSkeletonWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftSkeletonWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("LeftHand"));

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimInstance(TEXT("/Game/01_Core/AJH/Enemy/Skeleton/Melee/AJH_ABP_ShieldSkeleton.AJH_ABP_ShieldSkeleton_C"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	RHCollision->SetBoxExtent(FVector(20, 20, 65));
	RHCollision->SetRelativeLocation(FVector(0, 0, 50));

	GetCapsuleComponent()->InitCapsuleSize(30.0f, 125.0f);
}

void AShieldSkeleton::Attack()
{
	if (!bIsEnemyDie) {
		Super::Attack();

		damage = 20.0f;
		randomPattern = FMath::RandRange(1, 9);

		UShieldSkeleton_Anim* ShieldSkeletonAnim = Cast<UShieldSkeleton_Anim>(GetMesh()->GetAnimInstance());
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
		UE_LOG(LogTemp, Warning, TEXT("%f"), actualDamage);
		UE_LOG(LogTemp, Warning, TEXT("%f"), enemyHP);
		enemyHP -= actualDamage;
		if (enemyHP <= 0.f) EnemyDie();
	}
	return actualDamage;
}

void AShieldSkeleton::EnemyDie()
{
	bIsEnemyDie = true;

	UShieldSkeleton_Anim* ShieldSkeletonAnim = Cast<UShieldSkeleton_Anim>(GetMesh()->GetAnimInstance());
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