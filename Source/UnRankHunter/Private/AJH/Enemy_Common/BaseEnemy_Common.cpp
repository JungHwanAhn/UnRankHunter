#include "BaseEnemy_Common.h"
#include "AIController_Common.h"
#include "Components/BoxComponent.h"

ABaseEnemy_Common::ABaseEnemy_Common()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AAIController_Common::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetMesh()->GetOwner()->Tags.Add("Enemy");
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));

	RHCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RightHand"));
	RHCollision->SetupAttachment(GetMesh());
	RHCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RHCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHand"));

	LHCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftHand"));
	LHCollision->SetupAttachment(GetMesh());
	LHCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LHCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("LeftHand"));
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
	
}

void ABaseEnemy_Common::EnemyDie()
{
	isEnemyDie = true;
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
	isActive = true;
}

void ABaseEnemy_Common::OnReturnToPool_Implementation()
{
	isActive = false;
}

