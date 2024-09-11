#include "Rambo.h"
#include "Rambo_Anim.h"
#include "AIController_Rambo.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"

ARambo::ARambo()
{
	AIControllerClass = AAIController_Rambo::StaticClass();

	// Debug build test
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		RamboMesh(TEXT("SkeletalMesh'/Game/02_Asset/SteamPunkCollection/SteamPunkMech2837/Mesh/SK_SteamPunkMech_2837_Gun.SK_SteamPunkMech_2837_Gun'"));
	if (RamboMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(RamboMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -260), FRotator(0, -180, 0));
		GetMesh()->SetRelativeScale3D(FVector(1.8));
		GetMesh()->GetOwner()->Tags.Add("Rambo");
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimInstance(TEXT("/Game/01_Core/AJH/Enemy/Robot/Range/AJH_ABP_Rambo.AJH_ABP_Rambo_C"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	ShotDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("ShotDirection"));
	ShotDirection->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHand"));

	GetCapsuleComponent()->InitCapsuleSize(100.0f, 170.0f);
}

void ARambo::Attack()
{
	if (!bIsEnemyDie) {
		URambo_Anim* RamboAnim = Cast<URambo_Anim>(GetMesh()->GetAnimInstance());
		if (RamboAnim == nullptr) return;

		RamboAnim->Attack();

		RamboAnim->OnMontageEnded.RemoveDynamic(this, &ARambo::OnAttackMontageEnded);
		RamboAnim->OnMontageEnded.AddDynamic(this, &ARambo::OnAttackMontageEnded);
	}
}

void ARambo::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Super::OnAttackMontageEnded(Montage, bInterrupted);
}

void ARambo::AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::AttackCheckOverlap(OverlapComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

float ARambo::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float actualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (actualDamage > 0.f && !bIsEnemyDie) {
		enemyHP -= actualDamage;
		if (enemyHP <= 0.f) EnemyDie();
	}
	return actualDamage;
}

void ARambo::EnemyDie()
{
	bIsEnemyDie = true;

	URambo_Anim* RamboAnim = Cast<URambo_Anim>(GetMesh()->GetAnimInstance());
	if (RamboAnim == nullptr) return;

	RamboAnim->Die();

	FTimerHandle DieTimerHandle;
	FTimerDelegate CallEnemyDie = FTimerDelegate::CreateLambda([this]() { Super::EnemyDie(); });
	GetWorld()->GetTimerManager().SetTimer(DieTimerHandle, CallEnemyDie, dieDelay, false);
}

void ARambo::OnSpawnFromPool_Implementation()
{
	Super::OnSpawnFromPool_Implementation();
}

void ARambo::OnReturnToPool_Implementation()
{
	Super::OnReturnToPool_Implementation();
}

void ARambo::OnCollisionStart_Implementation()
{
}

void ARambo::OnCollisionEnd_Implementation()
{
}