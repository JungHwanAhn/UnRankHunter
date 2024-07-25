#include "Saw.h"
#include "Saw_Anim.h"
#include "AIController_Common.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

ASaw::ASaw()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AAIController_Common::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		GrootMesh(TEXT("SkeletalMesh'/Game/02_Asset/SteamPunkCollection/SteamPunkMech2837/Mesh/SK_SteamPunkMech_2837_Saw.SK_SteamPunkMech_2837_Saw'"));
	if (GrootMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(GrootMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -160), FRotator(0, -180, 0));
		GetMesh()->SetRelativeScale3D(FVector(1.2));
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimInstance(TEXT("/Game/01_Core/AJH/Enemy/Robot/Melee/AJH_ABP_Saw.AJH_ABP_Saw_C"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	RHCollision->SetBoxExtent(FVector(50, 30, 50));
	RHCollision->SetRelativeLocation(FVector(20, 0, 0));

	GetCapsuleComponent()->InitCapsuleSize(60.0f, 120.0f);
}

void ASaw::Attack()
{
	if (!bIsEnemyDie) {
		Super::Attack();

		damage = 20.0f;

		USaw_Anim* SawAnim = Cast<USaw_Anim>(GetMesh()->GetAnimInstance());
		if (SawAnim == nullptr) return;

		SawAnim->Attack();

		SawAnim->OnMontageEnded.RemoveDynamic(this, &ASaw::OnAttackMontageEnded);
		SawAnim->OnMontageEnded.AddDynamic(this, &ASaw::OnAttackMontageEnded);
	}
}

void ASaw::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Super::OnAttackMontageEnded(Montage, bInterrupted);
}

void ASaw::AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::AttackCheckOverlap(OverlapComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

float ASaw::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float actualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (actualDamage > 0.f && !bIsEnemyDie) {
		enemyHP -= actualDamage;
		if (enemyHP <= 0.f) EnemyDie();
	}
	return actualDamage;
}

void ASaw::EnemyDie()
{
	bIsEnemyDie = true;

	USaw_Anim* SawAnim = Cast<USaw_Anim>(GetMesh()->GetAnimInstance());
	if (SawAnim == nullptr) return;

	SawAnim->Die();

	FTimerHandle DieTimerHandle;
	FTimerDelegate CallEnemyDie = FTimerDelegate::CreateLambda([this]() { Super::EnemyDie(); });
	GetWorld()->GetTimerManager().SetTimer(DieTimerHandle, CallEnemyDie, dieDelay, false);
}

void ASaw::OnSpawnFromPool_Implementation()
{
	Super::OnSpawnFromPool_Implementation();
}

void ASaw::OnReturnToPool_Implementation()
{
	Super::OnReturnToPool_Implementation();
}

void ASaw::OnCollisionStart_Implementation()
{
}

void ASaw::OnCollisionEnd_Implementation()
{
}