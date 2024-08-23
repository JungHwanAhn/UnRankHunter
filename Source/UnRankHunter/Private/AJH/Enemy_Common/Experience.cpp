#include "Experience.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AExperience::AExperience()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	ExperienceCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	ExperienceCollision->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		ExperienceEffectObj(TEXT("ParticleSystem'/Game/02_Asset/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Elemental/Fire/P_ElementalFire_Sm.P_ElementalFire_Sm'"));
	if (ExperienceEffectObj.Succeeded()) {
		ExperienceEffect = ExperienceEffectObj.Object;
	}

	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	ParticleComponent->SetupAttachment(RootComponent);
	ParticleComponent->SetTemplate(ExperienceEffect);
	addXP = 0;
}

void AExperience::BeginPlay()
{
	Super::BeginPlay();
	
	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!Player) {
		UE_LOG(LogTemp, Warning, TEXT("Experience Actor Can't Find Player"));
	}

	ExperienceCollision->OnComponentBeginOverlap.AddDynamic(this, &AExperience::OnOverlapBegin);
}

void AExperience::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float distance = FVector::Distance(GetActorLocation(), Player->GetActorLocation());
	float clampedDistance = FMath::GetMappedRangeValueClamped(FVector2D(0, 1500), FVector2D(12, 1), distance);
	FVector NewLocation = FMath::VInterpTo(GetActorLocation(), Player->GetActorLocation(), DeltaTime, clampedDistance);
	SetActorLocation(NewLocation);
}

void AExperience::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor && OtherActor->ActorHasTag(TEXT("Player"))) {
		AddXPToPlayer(addXP);
	}
}