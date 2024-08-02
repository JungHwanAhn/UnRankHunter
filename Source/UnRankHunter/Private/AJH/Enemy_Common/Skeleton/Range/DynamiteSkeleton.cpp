#include "DynamiteSkeleton.h"
#include "DynamiteSkeleton_Anim.h"
#include "AIController_Range.h"
#include "Components/CapsuleComponent.h"

ADynamiteSkeleton::ADynamiteSkeleton()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AAIController_Range::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		GunSkeletonMesh(TEXT("SkeletalMesh'/Game/02_Asset/SkeletonCharacter/SkeletalMeshes/SkeletonCharacter/SKM_SkeletonCharacter_E.SKM_SkeletonCharacter_E'"));
	if (GunSkeletonMesh.Succeeded()) {
		GetMesh()->SetRelativeLocation(FVector(0, 0, -130));
		GetMesh()->SetRelativeScale3D(FVector(1.5));
		GetMesh()->SetSkeletalMesh(GunSkeletonMesh.Object);
	}

	Dynamite = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Dynamite"));
	Dynamite->SetupAttachment(GetMesh());
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		DynamiteMesh(TEXT("StaticMesh'/Game/02_Asset/dynamite/source/Dynamite/Dynamite.Dynamite'"));
	if (DynamiteMesh.Succeeded()) {
		Dynamite->SetStaticMesh(DynamiteMesh.Object);
		Dynamite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Dynamite->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Dynamite"));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimInstance(TEXT("/Game/01_Core/AJH/Enemy/Skeleton/Range/AJH_ABP_DynamiteSkeleton.AJH_ABP_DynamiteSkeleton_C"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	GetCapsuleComponent()->InitCapsuleSize(30.0f, 125.0f);
}

void ADynamiteSkeleton::Attack()
{
	if (!bIsEnemyDie) {

		Super::Attack();

		damage = 20.0f;

		UDynamiteSkeleton_Anim* DynamiteSkeletonAnim = Cast<UDynamiteSkeleton_Anim>(GetMesh()->GetAnimInstance());
		if (DynamiteSkeletonAnim == nullptr) return;

		DynamiteSkeletonAnim->Attack();

		DynamiteSkeletonAnim->OnMontageEnded.RemoveDynamic(this, &ADynamiteSkeleton::OnAttackMontageEnded);
		DynamiteSkeletonAnim->OnMontageEnded.AddDynamic(this, &ADynamiteSkeleton::OnAttackMontageEnded);
	}
}

void ADynamiteSkeleton::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Super::OnAttackMontageEnded(Montage, bInterrupted);
}

void ADynamiteSkeleton::AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::AttackCheckOverlap(OverlapComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

float ADynamiteSkeleton::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float actualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (actualDamage > 0.f && !bIsEnemyDie) {
		enemyHP -= actualDamage;
		if (enemyHP <= 0.f) EnemyDie();
	}
	return actualDamage;
}

void ADynamiteSkeleton::EnemyDie()
{
	bIsEnemyDie = true;

	UDynamiteSkeleton_Anim* DynamiteSkeletonAnim = Cast<UDynamiteSkeleton_Anim>(GetMesh()->GetAnimInstance());
	if (DynamiteSkeletonAnim == nullptr) return;

	DynamiteSkeletonAnim->Die();

	FTimerHandle DieTimerHandle;
	FTimerDelegate CallEnemyDie = FTimerDelegate::CreateLambda([this]() { Super::EnemyDie(); });
	GetWorld()->GetTimerManager().SetTimer(DieTimerHandle, CallEnemyDie, dieDelay, false);
}

void ADynamiteSkeleton::OnSpawnFromPool_Implementation()
{
	Super::OnSpawnFromPool_Implementation();
}

void ADynamiteSkeleton::OnReturnToPool_Implementation()
{
	Super::OnReturnToPool_Implementation();
}

void ADynamiteSkeleton::OnCollisionStart_Implementation()
{
}

void ADynamiteSkeleton::OnCollisionEnd_Implementation()
{
}