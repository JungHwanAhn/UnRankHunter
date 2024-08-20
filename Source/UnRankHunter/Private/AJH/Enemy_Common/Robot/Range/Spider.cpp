#include "Spider.h"
#include "Spider_Anim.h"
#include "AIController_Spider.h"
#include "Components/CapsuleComponent.h"

ASpider::ASpider()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AAIController_Spider::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SpiderMesh(TEXT("SkeletalMesh'/Game/02_Asset/SteamPunkCollection/SpiderMech/Mesh/SpiderMech/SK_SpriderMech.SK_SpriderMech'"));
	if (SpiderMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SpiderMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -200));
		GetMesh()->SetRelativeScale3D(FVector(1.9));
		GetMesh()->GetOwner()->Tags.Add("Spider");
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimInstance(TEXT("/Game/01_Core/AJH/Enemy/Robot/Range/AJH_ABP_Spider.AJH_ABP_Spider_C"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	GetCapsuleComponent()->InitCapsuleSize(100.0f, 115.0f);
}

void ASpider::Attack()
{
	if (!bIsEnemyDie) {
		Super::Attack();

		damage = 20.0f;

		USpider_Anim* SpiderAnim = Cast<USpider_Anim>(GetMesh()->GetAnimInstance());
		if (SpiderAnim == nullptr) return;

		SpiderAnim->Attack();

		SpiderAnim->OnMontageEnded.RemoveDynamic(this, &ASpider::OnAttackMontageEnded);
		SpiderAnim->OnMontageEnded.AddDynamic(this, &ASpider::OnAttackMontageEnded);
	}
}

void ASpider::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Super::OnAttackMontageEnded(Montage, bInterrupted);
}

void ASpider::AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::AttackCheckOverlap(OverlapComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

float ASpider::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float actualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (actualDamage > 0.f && !bIsEnemyDie) {
		enemyHP -= actualDamage;
		if (enemyHP <= 0.f) EnemyDie();
	}
	return actualDamage;
}

void ASpider::EnemyDie()
{
	bIsEnemyDie = true;

	USpider_Anim* SpiderAnim = Cast<USpider_Anim>(GetMesh()->GetAnimInstance());
	if (SpiderAnim == nullptr) return;

	SpiderAnim->Die();

	FTimerHandle DieTimerHandle;
	FTimerDelegate CallEnemyDie = FTimerDelegate::CreateLambda([this]() { Super::EnemyDie(); });
	GetWorld()->GetTimerManager().SetTimer(DieTimerHandle, CallEnemyDie, dieDelay, false);
}

void ASpider::OnSpawnFromPool_Implementation()
{
	Super::OnSpawnFromPool_Implementation();
}

void ASpider::OnReturnToPool_Implementation()
{
	Super::OnReturnToPool_Implementation();
}

void ASpider::OnCollisionStart_Implementation()
{
}

void ASpider::OnCollisionEnd_Implementation()
{
}