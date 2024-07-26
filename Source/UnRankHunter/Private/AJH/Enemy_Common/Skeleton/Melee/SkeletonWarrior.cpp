#include "SkeletonWarrior.h"
#include "SkeletonWarrior_Anim.h"
#include "AIController_Skeleton.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASkeletonWarrior::ASkeletonWarrior()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AAIController_Skeleton::StaticClass();

	GetMesh()->SetRelativeLocation(FVector(0, 0, -100));
	GetMesh()->SetRelativeScale3D(FVector(1.5));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RightSkeletonWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightWeapon"));
	RightSkeletonWeapon->SetupAttachment(GetMesh());
	RightSkeletonWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightSkeletonWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHand"));

	LeftSkeletonWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftWeapon"));
	LeftSkeletonWeapon->SetupAttachment(GetMesh());
	LeftSkeletonWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftSkeletonWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("LeftHand"));

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimInstance(TEXT("/Game/01_Core/AJH/Enemy/Skeleton/Melee/AJH_ABP_SkeletonWarrior.AJH_ABP_SkeletonWarrior_C"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	RHCollision->SetBoxExtent(FVector(20, 20, 45));
	RHCollision->SetRelativeLocation(FVector(0, 0, 35));
	LHCollision->SetBoxExtent(FVector(20, 20, 45));
	LHCollision->SetRelativeLocation(FVector(0, 0, 40));

	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	GetCapsuleComponent()->InitCapsuleSize(20.0f, 90.0f);
}

void ASkeletonWarrior::Attack()
{
	if (!bIsEnemyDie) {
		Super::Attack();

		damage = 20.0f;
		randomPattern = FMath::RandRange(1, 9);

		USkeletonWarrior_Anim* SkeletonWarriorAnim = Cast<USkeletonWarrior_Anim>(GetMesh()->GetAnimInstance());
		if (SkeletonWarriorAnim == nullptr) return;

		if (randomPattern <= 3) {
			SkeletonWarriorAnim->Attack("Attack_A");
		}
		else if (randomPattern <= 6) {
			SkeletonWarriorAnim->Attack("Attack_B");
		}
		else {
			SkeletonWarriorAnim->Attack("Attack_C");
		}

		SkeletonWarriorAnim->OnMontageEnded.RemoveDynamic(this, &ASkeletonWarrior::OnAttackMontageEnded);
		SkeletonWarriorAnim->OnMontageEnded.AddDynamic(this, &ASkeletonWarrior::OnAttackMontageEnded);
	}
}

void ASkeletonWarrior::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Super::OnAttackMontageEnded(Montage, bInterrupted);
}

void ASkeletonWarrior::AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::AttackCheckOverlap(OverlapComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

float ASkeletonWarrior::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float actualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (actualDamage > 0.f && !bIsEnemyDie) {
		enemyHP -= actualDamage;
		if (enemyHP <= 0.f) EnemyDie();
	}
	return actualDamage;
}

void ASkeletonWarrior::EnemyDie()
{
	bIsEnemyDie = true;

	USkeletonWarrior_Anim* SkeletonWarriorAnim = Cast<USkeletonWarrior_Anim>(GetMesh()->GetAnimInstance());
	if (SkeletonWarriorAnim == nullptr) return;

	SkeletonWarriorAnim->Die();

	FTimerHandle DieTimerHandle;
	FTimerDelegate CallEnemyDie = FTimerDelegate::CreateLambda([this]() { Super::EnemyDie(); });
	GetWorld()->GetTimerManager().SetTimer(DieTimerHandle, CallEnemyDie, dieDelay, false);
}

void ASkeletonWarrior::OnSpawnFromPool_Implementation()
{
	Super::OnSpawnFromPool_Implementation();
}

void ASkeletonWarrior::OnReturnToPool_Implementation()
{
	Super::OnReturnToPool_Implementation();
}

void ASkeletonWarrior::OnCollisionStart_Implementation()
{
}

void ASkeletonWarrior::OnCollisionEnd_Implementation()
{
}