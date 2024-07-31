#include "Dynamite.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#define ECC_Enemy ECC_GameTraceChannel1

ADynamite::ADynamite()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	DynamiteCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	DynamiteCollision->SetupAttachment(RootComponent);
	DynamiteCollision->SetBoxExtent(FVector(6, 17, 5));
	DynamiteCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DynamiteCollision->SetCollisionObjectType(ECC_WorldDynamic);
	DynamiteCollision->SetCollisionResponseToAllChannels(ECR_Block);
	DynamiteCollision->SetCollisionResponseToChannel(ECC_Enemy, ECR_Ignore);
	DynamiteCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	DynamiteCollision->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);

	Dynamite = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Dynamite"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		DynamiteMesh(TEXT("StaticMesh'/Game/02_Asset/dynamite/source/Dynamite/Dynamite.Dynamite'"));
	if (DynamiteMesh.Succeeded()) {
		Dynamite->SetStaticMesh(DynamiteMesh.Object);
		Dynamite->SetRelativeLocation(FVector(0, -3, -5));
		Dynamite->SetupAttachment(DynamiteCollision);
		Dynamite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->SetUpdatedComponent(DynamiteCollision);
}

void ADynamite::BeginPlay()
{
	Super::BeginPlay();
	LaunchTowardsPlayer();
}

void ADynamite::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADynamite::LaunchTowardsPlayer()
{
	AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (Player) {
		FVector PlayerLocation = Player->GetActorLocation();
		FVector LaunchDirection = (PlayerLocation - GetActorLocation()).GetSafeNormal();

		float distance = FVector::Dist(PlayerLocation, GetActorLocation());
		float launchSpeed = CalculateLaunchSpeed(distance);

		FVector LaunchVelocity = LaunchDirection * launchSpeed;
		LaunchVelocity.Z = CalculateLaunchZVelocity(launchSpeed);

		ProjectileMovement->Velocity = LaunchVelocity;
	}
}

float ADynamite::CalculateLaunchSpeed(float distance)
{
	const float MinSpeed = 500.0f;
	const float MaxSpeed = 1000.0f;
	return FMath::Clamp(distance * 0.6f, MinSpeed, MaxSpeed);
}

float ADynamite::CalculateLaunchZVelocity(float launchSpeed)
{
	const float Angle = 45.0f;
	return launchSpeed * FMath::Sin(FMath::DegreesToRadians(Angle));
}

