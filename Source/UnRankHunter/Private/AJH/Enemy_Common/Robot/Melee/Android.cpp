#include "Android.h"
#include "Android_Anim.h"
#include "AIController_Common.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

AAndroid::AAndroid()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AAIController_Common::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		AndroidMesh(TEXT("SkeletalMesh'/Game/02_Asset/SteamPunkCollection/SteamPunkAndroid/Mesh/Character/SK_SteamPunkAndroid.SK_SteamPunkAndroid'"));
	if (AndroidMesh.Succeeded()) {
		GetMesh()->SetRelativeLocation(FVector(0, 0, -120));
		GetMesh()->SetRelativeScale3D(FVector(1.4));
		GetMesh()->SetSkeletalMesh(AndroidMesh.Object);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	AndroidWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AndroidWeapon"));
	AndroidWeapon->SetupAttachment(GetMesh());
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		WeaponMesh(TEXT("StaticMesh'/Game/02_Asset/SteamPunkCollection/SteamPunkAndroid/Mesh/Weapon/AndroidWeapon.AndroidWeapon'"));
	if (WeaponMesh.Succeeded()) {
		AndroidWeapon->SetStaticMesh(WeaponMesh.Object);
		AndroidWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHand"));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimInstance(TEXT("/Game/01_Core/AJH/Enemy/Robot/Melee/AJH_ABP_Android.AJH_ABP_Android_C"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	RHCollision->SetBoxExtent(FVector(28, 16, 45));
	RHCollision->SetRelativeLocation(FVector(0, 0, 70));
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 110.0f);
}

void AAndroid::Attack()
{
	if (!bIsEnemyDie) {
		Super::Attack();

		damage = 20.0f;
		randomPattern = FMath::RandRange(1, 9);

		UAndroid_Anim* AndroidAnim = Cast<UAndroid_Anim>(GetMesh()->GetAnimInstance());
		if (AndroidAnim == nullptr) return;

	
		if (randomPattern <= 3) {
			AndroidAnim->Attack("Attack_A");
		}
		else if (randomPattern <= 6) {
			AndroidAnim->Attack("Attack_B");
		}
		else {
			AndroidAnim->Attack("Attack_C");
		}

		AndroidAnim->OnMontageEnded.RemoveDynamic(this, &AAndroid::OnAttackMontageEnded);
		AndroidAnim->OnMontageEnded.AddDynamic(this, &AAndroid::OnAttackMontageEnded);
	}
}

void AAndroid::OnSpawnFromPool_Implementation()
{
	Super::OnSpawnFromPool_Implementation();
}

void AAndroid::OnReturnToPool_Implementation()
{
	Super::OnReturnToPool_Implementation();
}

void AAndroid::OnCollisionStart_Implementation()
{
}

void AAndroid::OnCollisionEnd_Implementation()
{
}

void AAndroid::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Super::OnAttackMontageEnded(Montage, bInterrupted);
}

void AAndroid::AttackCheckOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::AttackCheckOverlap(OverlapComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

float AAndroid::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float actualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (actualDamage > 0.f && !bIsEnemyDie) {
		enemyHP -= actualDamage;
		if (enemyHP <= 0.f) EnemyDie();
	}
	return actualDamage;
}

void AAndroid::EnemyDie()
{
	bIsEnemyDie = true;

	UAndroid_Anim* AndroidAnim = Cast<UAndroid_Anim>(GetMesh()->GetAnimInstance());
	if (AndroidAnim == nullptr) return;

	AndroidAnim->Die();

	FTimerHandle DieTimerHandle;
	FTimerDelegate CallEnemyDie = FTimerDelegate::CreateLambda([this]() { Super::EnemyDie(); });
	GetWorld()->GetTimerManager().SetTimer(DieTimerHandle, CallEnemyDie, dieDelay, false);
}
