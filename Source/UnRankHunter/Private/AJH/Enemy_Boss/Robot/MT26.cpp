#include "MT26.h"
#include "MT26_Anim.h"
#include "AIController_MT26.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"

AMT26::AMT26()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AAIController_MT26::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MT26Mesh(TEXT("SkeletalMesh'/Game/02_Asset/ParagonGRIMexe/Characters/Heroes/GRIM/Meshes/GRIM_GDC.GRIM_GDC'"));
	if (MT26Mesh.Succeeded()) {
		GetMesh()->SetRelativeScale3D(FVector(80));
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

	ShotDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("ShotDirection"));
	ShotDirection->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Muzzle_01"));
}

void AMT26::BeginPlay()
{
	Super::BeginPlay();

	MT26Anim = Cast<UMT26_Anim>(GetMesh()->GetAnimInstance());
	if (!MT26Anim) return;

	AIController = Cast<AAIController_MT26>(GetController());
	if (!AIController) return;
}

void AMT26::EnergyBall()
{
	if (!bIsEnemyDie) {
		MT26Anim->EnergyBall();

		AimToValue(-67.0f, "SingleShot");

		MT26Anim->OnMontageEnded.RemoveDynamic(this, &AMT26::OnAttackMontageEnded);
		MT26Anim->OnMontageEnded.AddDynamic(this, &AMT26::OnAttackMontageEnded);
	}
}

void AMT26::PlazmaArea()
{
	if (!bIsEnemyDie) {
		MT26Anim->PlazmaArea();

		MT26Anim->OnMontageEnded.RemoveDynamic(this, &AMT26::OnAttackMontageEnded);
		MT26Anim->OnMontageEnded.AddDynamic(this, &AMT26::OnAttackMontageEnded);
	}
}

void AMT26::PlazmaToPlayer()
{
	if (!bIsEnemyDie) {
		MT26Anim->PlazmaToPlayer();

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

void AMT26::LaserBeam()
{
	if (!bIsEnemyDie) {
		MT26Anim->LaserBeam();
		AIController->bIsLaserAttack = true;
		FVector PlayerLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
		if (PlayerLocation.X + PlayerLocation.Y >= 145000.0f) {
			AimToValue(-42.0f, "AllPlace");
		}
		else {
			AimToValue(-92.0f, "AllPlace");
		}

		MT26Anim->OnMontageEnded.RemoveDynamic(this, &AMT26::OnAttackMontageEnded);
		MT26Anim->OnMontageEnded.AddDynamic(this, &AMT26::OnAttackMontageEnded);
	}
}

void AMT26::LaserShot()
{
	if (!bIsEnemyDie) {
		MT26Anim->LaserShot();

		AimToValue(-67.0f, "SingleShot");

		MT26Anim->OnMontageEnded.RemoveDynamic(this, &AMT26::OnAttackMontageEnded);
		MT26Anim->OnMontageEnded.AddDynamic(this, &AMT26::OnAttackMontageEnded);
	}
}

void AMT26::MultiLaserShot()
{
	if (!bIsEnemyDie) {
		MT26Anim->MultiLaserShot();

		AIController->bIsLaserAttack = true;
		FVector PlayerLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
		if (PlayerLocation.X + PlayerLocation.Y >= 145000.0f) {
			AimToValue(-42.0f, "AllPlace");
		}
		else {
			AimToValue(-92.0f, "AllPlace");
		}

		MT26Anim->OnMontageEnded.RemoveDynamic(this, &AMT26::OnAttackMontageEnded);
		MT26Anim->OnMontageEnded.AddDynamic(this, &AMT26::OnAttackMontageEnded);
	}
}

void AMT26::HomingRocket()
{
	if (!bIsEnemyDie) {
		MT26Anim->HomingRocket();

		AimToValue(-67.0f, "SingleShot");

		MT26Anim->OnMontageEnded.RemoveDynamic(this, &AMT26::OnAttackMontageEnded);
		MT26Anim->OnMontageEnded.AddDynamic(this, &AMT26::OnAttackMontageEnded);
	}
}

void AMT26::ChangeForm()
{
	if (!bIsEnemyDie) {
		MT26Anim->ChangeForm();

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