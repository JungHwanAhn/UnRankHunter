#include "Rambo.h"
#include "Rambo_Anim.h"
#include "AIController_Range.h"
#include "Components/CapsuleComponent.h"

ARambo::ARambo()
{
	AIControllerClass = AAIController_Range::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		RamboMesh(TEXT("SkeletalMesh'/Game/02_Asset/SteamPunkCollection/SteamPunkMech2837/Mesh/SK_SteamPunkMech_2837_Gun.SK_SteamPunkMech_2837_Gun'"));
	if (RamboMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(RamboMesh.Object);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -140), FRotator(0, -180, 0));
		GetMesh()->GetOwner()->Tags.Add("Rambo");
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimInstance(TEXT("/Game/01_Core/AJH/Enemy/Robot/Range/AJH_ABP_Rambo.AJH_ABP_Rambo_C"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	GetCapsuleComponent()->InitCapsuleSize(60.0f, 100.0f);
}

void ARambo::Attack()
{
	if (!bIsEnemyDie) {
		Super::Attack();

		damage = 20.0f;

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
		ramboHP -= actualDamage;
		UE_LOG(LogTemp, Warning, TEXT("takeDamage: %f"), actualDamage);
		if (ramboHP <= 0.f) EnemyDie();
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