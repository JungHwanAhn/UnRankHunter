#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Experience.generated.h"

UCLASS()
class UNRANKHUNTER_API AExperience : public AActor
{
	GENERATED_BODY()
	
public:	
	AExperience();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "XP Value", meta = (ExposeOnSpawn = true))
	float addXP;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CPP Function")
	void AddXPToPlayer(float xpValue);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* ExperienceCollision;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystem* ExperienceEffect;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* ParticleComponent;

	class AActor* Player;
};