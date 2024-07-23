#include "Titan.h"
#include "Titan_Anim.h"
#include "AIController_Elite.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

ATitan::ATitan()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AAIController_Elite::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		AndroidMesh(TEXT("SkeletalMesh'/Game/02_Asset/ParagonCrunch/Characters/Heroes/Crunch/Skins/Teir_1/Military/Meshes/Crunch_Military.Crunch_Military'"));
	if (AndroidMesh.Succeeded()) {
		GetMesh()->SetRelativeLocation(FVector(0, 0, -120));
		GetMesh()->SetRelativeScale3D(FVector(1.5));
		GetMesh()->SetSkeletalMesh(AndroidMesh.Object);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimInstance(TEXT("/Game/01_Core/AJH/Enemy/Robot/Elite/AJH_ABP_Titan.AJH_ABP_Titan_C"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	RHCollision->SetBoxExtent(FVector(45, 40, 40));
	RHCollision->SetRelativeLocation(FVector(-20, -20, 0));
	LHCollision->SetBoxExtent(FVector(45, 40, 40));
	LHCollision->SetRelativeLocation(FVector(20, 20, 0));

	GetCapsuleComponent()->InitCapsuleSize(100.0f, 170.0f);
}

void ATitan::BeginPlay()
{
	Super::BeginPlay();

	TitanAnim = Cast<UTitan_Anim>(GetMesh()->GetAnimInstance());
	if (TitanAnim == nullptr) return;
}

void ATitan::Attack()
{
	if (!bIsEnemyDie) {
		Super::Attack();

		damage = 30.0f;
		randomPattern = FMath::RandRange(1, 9);

		if (randomPattern <= 3) {
			TitanAnim->Attack("Attack_A");
		}
		else if (randomPattern <= 6) {
			TitanAnim->Attack("Attack_B");
		}
		else {
			TitanAnim->Attack("Attack_C");
		}

		TitanAnim->OnMontageEnded.RemoveDynamic(this, &ATitan::OnAttackMontageEnded);
		TitanAnim->OnMontageEnded.AddDynamic(this, &ATitan::OnAttackMontageEnded);
	}
}

void ATitan::DashAttack()
{
	TitanAnim->DashAttack();

	float DeltaTime = GetWorld()->GetDeltaSeconds();
	float TimeElapsed = 0.0f;



	GetWorldTimerManager().SetTimer(DashTimerHandle, [this, DeltaTime, TimeElapsed]() mutable {
		TimeElapsed += DeltaTime;
		float Alpha = TimeElapsed / 1.13f;

		if (Alpha >= 0.4f) {
			Dashing();
		}
		if (Alpha >= 1.13f) {
			GetWorldTimerManager().ClearTimer(DashTimerHandle);
		}
		}, DeltaTime, true);
}

void ATitan::JumpAttack()
{
	TitanAnim->JumpAttack();
}

void ATitan::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Super::OnAttackMontageEnded(Montage, bInterrupted);
}

void ATitan::AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::AttackCheckOverlap(OverlapComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

float ATitan::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float actualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (actualDamage > 0.f && !bIsEnemyDie) {
		titanHP -= actualDamage;
		if (titanHP <= 0.f) EnemyDie();
	}
	return actualDamage;
}

void ATitan::EnemyDie()
{
	bIsEnemyDie = true;
	TitanAnim->Die();

	FTimerHandle DieTimerHandle;
	FTimerDelegate CallEnemyDie = FTimerDelegate::CreateLambda([this]() { Super::EnemyDie(); });
	GetWorld()->GetTimerManager().SetTimer(DieTimerHandle, CallEnemyDie, dieDelay, false);
}

void ATitan::OnSpawnFromPool_Implementation()
{
	Super::OnSpawnFromPool_Implementation();
}

void ATitan::OnReturnToPool_Implementation()
{
	Super::OnReturnToPool_Implementation();
}

void ATitan::OnCollisionStart_Implementation()
{
}

void ATitan::OnCollisionEnd_Implementation()
{
}