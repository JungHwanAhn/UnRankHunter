#include "MT26.h"
#include "MT26_Anim.h"
#include "AIController_Boss.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

AMT26::AMT26()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AAIController_Boss::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MT26Mesh(TEXT("SkeletalMesh'/Game/02_Asset/ParagonGRIMexe/Characters/Heroes/GRIM/Meshes/GRIM_GDC.GRIM_GDC'"));
	if (MT26Mesh.Succeeded()) {
		//GetMesh()->SetRelativeLocation(FVector(0, 0, -120));
		//GetMesh()->SetRelativeScale3D(FVector(1.5));
		GetMesh()->SetSkeletalMesh(MT26Mesh.Object);
		GetMesh()->GetOwner()->Tags.Remove("Common");
		GetMesh()->GetOwner()->Tags.Add("Boss");
		GetMesh()->GetOwner()->Tags.Add("MT26");
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimInstance(TEXT("/Game/01_Core/AJH/Enemy/Robot/Boss/AJH_ABP_MT26.AJH_ABP_MT26_C"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	//GetCapsuleComponent()->InitCapsuleSize(100.0f, 170.0f);
}

void AMT26::BeginPlay()
{
	Super::BeginPlay();

	MT26Anim = Cast<UMT26_Anim>(GetMesh()->GetAnimInstance());
	if (!MT26Anim) return;
}

void AMT26::Attack()
{
	if (!bIsEnemyDie) {
		Super::Attack();

		damage = 30.0f;

		MT26Anim->Attack();

		MT26Anim->OnMontageEnded.RemoveDynamic(this, &AMT26::OnAttackMontageEnded);
		MT26Anim->OnMontageEnded.AddDynamic(this, &AMT26::OnAttackMontageEnded);
	}
}

void AMT26::ChargingShot()
{
	if (!bIsEnemyDie) {
		MT26Anim->ChargingShot();

		MT26Anim->OnMontageEnded.RemoveDynamic(this, &AMT26::OnAttackMontageEnded);
		MT26Anim->OnMontageEnded.AddDynamic(this, &AMT26::OnAttackMontageEnded);
	}
}

void AMT26::Shelling()
{
	if (!bIsEnemyDie) {
		MT26Anim->Shelling();

		MT26Anim->OnMontageEnded.RemoveDynamic(this, &AMT26::OnAttackMontageEnded);
		MT26Anim->OnMontageEnded.AddDynamic(this, &AMT26::OnAttackMontageEnded);
	}
}

void AMT26::ShellingToPlayer()
{
	if (!bIsEnemyDie) {
		MT26Anim->ShellingToPlayer();

		MT26Anim->OnMontageEnded.RemoveDynamic(this, &AMT26::OnAttackMontageEnded);
		MT26Anim->OnMontageEnded.AddDynamic(this, &AMT26::OnAttackMontageEnded);
	}
}

void AMT26::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Super::OnAttackMontageEnded(Montage, bInterrupted);
}

void AMT26::AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::AttackCheckOverlap(OverlapComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

float AMT26::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float actualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (actualDamage > 0.f && !bIsEnemyDie) {
		mt26HP -= actualDamage;
		if (mt26HP <= 0.f) EnemyDie();
	}
	return actualDamage;
}

void AMT26::EnemyDie()
{
	bIsEnemyDie = true;
	MT26Anim->Die();
}

void AMT26::OnSpawnFromPool_Implementation()
{
}

void AMT26::OnReturnToPool_Implementation()
{
}

void AMT26::OnCollisionStart_Implementation()
{
}

void AMT26::OnCollisionEnd_Implementation()
{
}