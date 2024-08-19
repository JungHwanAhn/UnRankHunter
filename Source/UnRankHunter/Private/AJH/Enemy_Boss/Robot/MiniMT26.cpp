#include "MiniMT26.h"
#include "MiniMT26_Anim.h"
#include "AIController_MiniMT26.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

AMiniMT26::AMiniMT26()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AAIController_MiniMT26::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MiniMT26Mesh(TEXT("SkeletalMesh'/Game/02_Asset/ParagonGRIMexe/Characters/Heroes/GRIM/Meshes/GRIM_GDC.GRIM_GDC'"));
	if (MiniMT26Mesh.Succeeded()) {
		GetMesh()->SetRelativeLocation(FVector(0, 0, -370));
		GetMesh()->SetRelativeScale3D(FVector(3.0f));
		GetMesh()->SetSkeletalMesh(MiniMT26Mesh.Object);
		GetMesh()->GetOwner()->Tags.Remove("Common");
		GetMesh()->GetOwner()->Tags.Add("Boss");
		GetMesh()->GetOwner()->Tags.Add("MiniMT26");
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimInstance(TEXT("/Game/01_Core/AJH/Enemy/Robot/Boss/AJH_ABP_MiniMT26.AJH_ABP_MiniMT26_C"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	ShotDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("ShotDirection"));
	ShotDirection->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Muzzle_01"));

	RHCollision->SetRelativeLocation(FVector(0, -70, 28));
	RHCollision->SetBoxExtent(FVector(40, 170, 40));
	GetCapsuleComponent()->InitCapsuleSize(200.0f, 370.0f);
}

void AMiniMT26::BeginPlay()
{
	Super::BeginPlay();

	MiniMT26Anim = Cast<UMiniMT26_Anim>(GetMesh()->GetAnimInstance());
	if (!MiniMT26Anim) return;

	AIController = Cast<AAIController_MiniMT26>(GetController());
	if (!AIController) return;
}

void AMiniMT26::Attack()
{
	if (!bIsEnemyDie) {
		Super::Attack();
		damage = 50.0f;

		MiniMT26Anim->GunAttack();

		MiniMT26Anim->OnMontageEnded.RemoveDynamic(this, &AMiniMT26::OnAttackMontageEnded);
		MiniMT26Anim->OnMontageEnded.AddDynamic(this, &AMiniMT26::OnAttackMontageEnded);
	}
}

void AMiniMT26::EnergyBall()
{
	if (!bIsEnemyDie) {
		AimToValue(-13.0f);
		MiniMT26Anim->EnergyBall();

		MiniMT26Anim->OnMontageEnded.RemoveDynamic(this, &AMiniMT26::OnAttackMontageEnded);
		MiniMT26Anim->OnMontageEnded.AddDynamic(this, &AMiniMT26::OnAttackMontageEnded);
	}
}

void AMiniMT26::Shelling()
{
	if (!bIsEnemyDie) {
		MiniMT26Anim->Shelling();

		MiniMT26Anim->OnMontageEnded.RemoveDynamic(this, &AMiniMT26::OnAttackMontageEnded);
		MiniMT26Anim->OnMontageEnded.AddDynamic(this, &AMiniMT26::OnAttackMontageEnded);
	}
}

void AMiniMT26::LaserShot()
{
	if (!bIsEnemyDie) {
		AimToValue(-13.0f);
		MiniMT26Anim->LaserShot();

		MiniMT26Anim->OnMontageEnded.RemoveDynamic(this, &AMiniMT26::OnAttackMontageEnded);
		MiniMT26Anim->OnMontageEnded.AddDynamic(this, &AMiniMT26::OnAttackMontageEnded);
	}
}

void AMiniMT26::HomingRocket()
{
	if (!bIsEnemyDie) {
		MiniMT26Anim->HomingRocket();

		MiniMT26Anim->OnMontageEnded.RemoveDynamic(this, &AMiniMT26::OnAttackMontageEnded);
		MiniMT26Anim->OnMontageEnded.AddDynamic(this, &AMiniMT26::OnAttackMontageEnded);
	}
}

void AMiniMT26::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Super::OnAttackMontageEnded(Montage, bInterrupted);
}

void AMiniMT26::AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::AttackCheckOverlap(OverlapComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

float AMiniMT26::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float actualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (actualDamage > 0.f && !bIsEnemyDie) {
		miniMT26HP -= actualDamage;
		if (miniMT26HP <= 0.f) EnemyDie();
	}
	return actualDamage;
}

void AMiniMT26::EnemyDie()
{
	bIsEnemyDie = true;
	MiniMT26Anim->Die();
}

void AMiniMT26::OnSpawnFromPool_Implementation()
{
}

void AMiniMT26::OnReturnToPool_Implementation()
{
}

void AMiniMT26::OnCollisionStart_Implementation()
{
}

void AMiniMT26::OnCollisionEnd_Implementation()
{
}