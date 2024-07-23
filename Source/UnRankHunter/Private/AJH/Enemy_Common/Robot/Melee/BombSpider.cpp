#include "BombSpider.h"
#include "BombSpider_Anim.h"
#include "AIController_Bomb.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ABombSpider::ABombSpider()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AAIController_Bomb::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		BombSpiderMesh(TEXT("SkeletalMesh'/Game/02_Asset/SteamPunkCollection/SpiderMech/Mesh/SpiderMech/SK_SpriderMech_Bomb.SK_SpriderMech_Bomb'"));
	if (BombSpiderMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(BombSpiderMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -50));
		GetMesh()->SetRelativeScale3D(FVector(0.5));
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimInstance(TEXT("/Game/01_Core/AJH/Enemy/Robot/Melee/AJH_ABP_BombSpider.AJH_ABP_BombSpider_C"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	GetCapsuleComponent()->InitCapsuleSize(34.0f, 40.0f);
	GetCharacterMovement()->MaxWalkSpeed = 950.0f;
}

void ABombSpider::Attack()
{
	if (!bIsEnemyDie) {
		Super::Attack();

		UBombSpider_Anim* BombSpiderAnim = Cast<UBombSpider_Anim>(GetMesh()->GetAnimInstance());
		if (BombSpiderAnim == nullptr) return;


		BombSpiderAnim->Attack();

		BombSpiderAnim->OnMontageEnded.RemoveDynamic(this, &ABombSpider::OnAttackMontageEnded);
		BombSpiderAnim->OnMontageEnded.AddDynamic(this, &ABombSpider::OnAttackMontageEnded);
	}
}

void ABombSpider::OnSpawnFromPool_Implementation()
{
	Super::OnSpawnFromPool_Implementation();
}

void ABombSpider::OnReturnToPool_Implementation()
{
	Super::OnReturnToPool_Implementation();
}

float ABombSpider::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float actualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (actualDamage > 0.f && !bIsEnemyDie) {
		bombSpiderHP -= actualDamage;
		if (bombSpiderHP <= 0.f) EnemyDie();
	}
	return actualDamage;
}

void ABombSpider::EnemyDie()
{
	bIsEnemyDie = true;

	FTimerHandle DieTimerHandle;
	FTimerDelegate CallEnemyDie = FTimerDelegate::CreateLambda([this]() { Super::EnemyDie(); });
	GetWorld()->GetTimerManager().SetTimer(DieTimerHandle, CallEnemyDie, dieDelay, false);
}
