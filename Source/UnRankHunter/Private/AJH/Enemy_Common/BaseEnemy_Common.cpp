#include "BaseEnemy_Common.h"
#include "PoolSubsystem.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

#define ECC_Enemy ECC_GameTraceChannel1

ABaseEnemy_Common::ABaseEnemy_Common()
{
	PrimaryActorTick.bCanEverTick = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetMesh()->GetOwner()->Tags.Add("Enemy");
	GetMesh()->GetOwner()->Tags.Add("Common");
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));

	RHCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RightHand"));
	RHCollision->SetupAttachment(GetMesh());
	RHCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RHCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Enemy, ECollisionResponse::ECR_Ignore);
	RHCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHand"));

	LHCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftHand"));
	LHCollision->SetupAttachment(GetMesh());
	LHCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LHCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Enemy, ECollisionResponse::ECR_Ignore);
	LHCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("LeftHand"));

	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_Enemy);
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void ABaseEnemy_Common::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseEnemy_Common::OnAttackMontageEnded(UAnimMontage* Montage, bool Interrupted)
{
	OnAttackEnd.Broadcast();
}

void ABaseEnemy_Common::AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Player = Cast<AActor>(OtherActor);
	if (Player && Player->ActorHasTag("Player")) {
		UGameplayStatics::ApplyDamage(OtherActor, damage, GetController(), nullptr, NULL);
	}
}

void ABaseEnemy_Common::Attack()
{
	RHCollision->OnComponentBeginOverlap.RemoveDynamic(this, &ABaseEnemy_Common::AttackCheckOverlap);
	RHCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemy_Common::AttackCheckOverlap);
	LHCollision->OnComponentBeginOverlap.RemoveDynamic(this, &ABaseEnemy_Common::AttackCheckOverlap);
	LHCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemy_Common::AttackCheckOverlap);
}

void ABaseEnemy_Common::DashAttack()
{
}

void ABaseEnemy_Common::JumpAttack()
{
}

void ABaseEnemy_Common::EnemyDie()
{
	UPoolSubsystem* PoolSubsystem = GetWorld()->GetSubsystem<UPoolSubsystem>();
	if (PoolSubsystem) {
		PoolSubsystem->ReturnToPool(this);
		bIsEnemyDie = false;
	}
}

void ABaseEnemy_Common::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseEnemy_Common::OnCollisionStart_Implementation()
{
}

void ABaseEnemy_Common::OnCollisionEnd_Implementation()
{
}

void ABaseEnemy_Common::OnSpawnFromPool_Implementation()
{
	bIsActive = true;
}

void ABaseEnemy_Common::OnReturnToPool_Implementation()
{
	bIsEnemyDie = false;
	bIsActive = false;
	bIsNear = false;
	enemyHP = 100.0f;

	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

