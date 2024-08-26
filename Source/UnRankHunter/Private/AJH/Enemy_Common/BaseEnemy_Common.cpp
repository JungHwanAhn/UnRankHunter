#include "BaseEnemy_Common.h"
#include "UnRankHunter/UnRankHunter.h"
#include "PoolSubsystem.h"
#include "AIController_Rambo.h"
#include "AIController_Spider.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Experience.h"

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

void ABaseEnemy_Common::OnAttackMontageEnded(UAnimMontage* Montage, bool Interrupted)
{
	OnAttackEnd.Broadcast();
}

void ABaseEnemy_Common::AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* Player = Cast<AActor>(OtherActor);
	if (Player && Player->ActorHasTag("Player") && bIsDamage) {
		UGameplayStatics::ApplyDamage(OtherActor, damage, GetController(), nullptr, NULL);
		bIsDamage = false;
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

void ABaseEnemy_Common::Slow(float Value, bool bIsSlow)
{
	float velocity;
	velocity = BaseMoveSpeed;
	//if (GetController()->IsA(AAIController_Rambo::StaticClass()) || GetController()->IsA(AAIController_Spider::StaticClass())) {
	//	velocity = 800.0f;
	//}
	//else {
	//	velocity = 850.0f;
	//}
	
	if (bIsSlow) {
		velocity *= Value;
	}

	GetCharacterMovement()->MaxWalkSpeed = velocity;

	UE_LOG(UH_LogDefault, Warning, TEXT("Enemy is slow of %f percents."), velocity);
}

void ABaseEnemy_Common::EnemyDie()
{
	UPoolSubsystem* PoolSubsystem = GetWorld()->GetSubsystem<UPoolSubsystem>();
	if (PoolSubsystem) {
		PoolSubsystem->ReturnToPool(this);
		bIsEnemyDie = false;
		
		FTransform SpawnTransform(FRotator::ZeroRotator, GetActorLocation());
		UClass* ExperienceClass = LoadObject<UClass>(nullptr, TEXT("/Game/01_Core/AJH/Enemy/AJH_BP_Experience.AJH_BP_Experience_C"));
		
		if (ExperienceClass) {
			AExperience* Experience = Cast<AExperience>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ExperienceClass, SpawnTransform, ESpawnActorCollisionHandlingMethod::AlwaysSpawn));
			if (Experience) {
				Experience->addXP = BaseDropExp;
				UGameplayStatics::FinishSpawningActor(Experience, SpawnTransform);
			}
		}
	}

	OnDeath.Broadcast(this);
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

float ABaseEnemy_Common::GetMoveSpeed_Implementation()
{
	return BaseMoveSpeed;
}

void ABaseEnemy_Common::InitializeEnemyStat(float MaxHealth, float Damage, float MoveSpeed, float DropExp, int32 DropMoney, int32 DropToken)
{
	this->BaseMaxHealth = MaxHealth;
	this->BaseDamange = Damage;
	this->BaseMoveSpeed = MoveSpeed;

	this->BaseDropExp = DropExp;
	this->BaseDropMoney = DropMoney;
	this->BaseDropToken = DropToken;

	enemyHP = MaxHealth;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
}

