#include "SteelGroot.h"
#include "SteelGroot_Anim.h"
#include "AIController_Common.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

ASteelGroot::ASteelGroot()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AAIController_Common::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		GrootMesh(TEXT("SkeletalMesh'/Game/02_Asset/SteamPunkCollection/SteamPunkBoss/Mesh/Character/SK_SteamPunkBoss.SK_SteamPunkBoss'"));
	if (GrootMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(GrootMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -150));
		GetMesh()->SetRelativeScale3D(FVector(1.5));
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimInstance(TEXT("/Game/01_Core/AJH/Enemy/Robot/Melee/AJH_ABP_SteelGroot.AJH_ABP_SteelGroot_C"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	RHCollision->SetBoxExtent(FVector(50, 40, 40));
	RHCollision->SetRelativeLocation(FVector(-20, 0, 0));

	LHCollision->SetBoxExtent(FVector(50, 40, 40));
	LHCollision->SetRelativeLocation(FVector(20, 0, 0));

	GetCapsuleComponent()->InitCapsuleSize(80.0f, 150.0f);
}

void ASteelGroot::Attack()
{
	if (!bIsEnemyDie) {
		Super::Attack();

		damage = 20.0f;

		USteelGroot_Anim* SteelGrootAnim = Cast<USteelGroot_Anim>(GetMesh()->GetAnimInstance());
		if (SteelGrootAnim == nullptr) return;

		SteelGrootAnim->Attack();

		SteelGrootAnim->OnMontageEnded.RemoveDynamic(this, &ASteelGroot::OnAttackMontageEnded);
		SteelGrootAnim->OnMontageEnded.AddDynamic(this, &ASteelGroot::OnAttackMontageEnded);
	}
}

void ASteelGroot::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Super::OnAttackMontageEnded(Montage, bInterrupted);
}

void ASteelGroot::AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::AttackCheckOverlap(OverlapComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

float ASteelGroot::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float actualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (actualDamage > 0.f && !bIsEnemyDie) {
		grootHP -= actualDamage;
		if (grootHP <= 0.f) EnemyDie();
	}
	return actualDamage;
}

void ASteelGroot::EnemyDie()
{
	bIsEnemyDie = true;

	USteelGroot_Anim* SteelGrootAnim = Cast<USteelGroot_Anim>(GetMesh()->GetAnimInstance());
	if (SteelGrootAnim == nullptr) return;

	SteelGrootAnim->Die();

	FTimerHandle DieTimerHandle;
	FTimerDelegate CallEnemyDie = FTimerDelegate::CreateLambda([this]() { Super::EnemyDie(); });
	GetWorld()->GetTimerManager().SetTimer(DieTimerHandle, CallEnemyDie, dieDelay, false);
}

void ASteelGroot::OnSpawnFromPool_Implementation()
{
	Super::OnSpawnFromPool_Implementation();
}

void ASteelGroot::OnReturnToPool_Implementation()
{
	Super::OnReturnToPool_Implementation();
}

void ASteelGroot::OnCollisionStart_Implementation()
{
}

void ASteelGroot::OnCollisionEnd_Implementation()
{
}