// Fill out your copyright notice in the Description page of Project Settings.


#include "KYG/ArtifactSystem/ArtifactObject_BleedingHeart.h"
#include "Weapon/WeaponManager/ACWeaponManager.h"
#include "Weapon/Structure/WeaponStructure.h"
#include "Kismet/GameplayStatics.h"
#include "BlueprintInterface/PlayerStatInterface.h"

UArtifactObject_BleedingHeart::UArtifactObject_BleedingHeart()
{
	ArtifactID = "001";
	Rarity = EItemRarity::Unique;

	bUseTick = false;
}

void UArtifactObject_BleedingHeart::EnableArtifact()
{
	Super::EnableArtifact();

	WeaponManager = ArtifactOwner->GetComponentByClass<UACWeaponManager>();

	ArtifactOwner->OnTakeAnyDamage.AddDynamic(this, &UArtifactObject_BleedingHeart::OnActorDamaged);

	auto PlayerStatArr = ArtifactOwner->GetComponentsByInterface(UPlayerStatInterface::StaticClass());
	if (ensure(PlayerStatArr.IsEmpty() == false))
	{
		PlayerStat = PlayerStatArr[0];

		if (PlayerStat == nullptr)
			UH_LogTemp(Log, TEXT("Stat component not implements the interface"));
	}
	else
	{
		UH_LogTemp(Log, TEXT("Player has not stat component"));
	}

	UH_LogTempParam(Log, TEXT("Artifact Enabled: %s[%s]"), *this->ArtifactName, *this->ArtifactID.ToString());
}

void UArtifactObject_BleedingHeart::DisableArtifect()
{
	Super::EnableArtifact();

	ArtifactOwner->OnTakeAnyDamage.RemoveDynamic(this, &UArtifactObject_BleedingHeart::OnActorDamaged);

	UH_LogTempParam(Log, TEXT("Artifact Disabled: %s[%s]"), *this->ArtifactName, *this->ArtifactID.ToString());
}

void UArtifactObject_BleedingHeart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Get the left duration of bleeding heart's buff.
double UArtifactObject_BleedingHeart::GetDuration()
{
	double ElapsedTime = GetWorld()->GetTimeSeconds() - BuffStartTime;
	double Duration = BuffDuration - ElapsedTime;

	return Duration;
}

float UArtifactObject_BleedingHeart::GetCooldownDuration()
{
	float RemainCooldown = GetWorld()->GetTimerManager().GetTimerRemaining(CooldownTimer);
	return RemainCooldown;
}

void UArtifactObject_BleedingHeart::OnActorDamaged(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	// If buff is already active, escape the process.
	if (bIsBuffActive || bIsCooldown)
	{
		return;
	}

	// When the player's health decrease below 50%, attack speed and reload speed are increased by 50%.
	if (ensure(PlayerStat != nullptr && PlayerStat->Implements<UPlayerStatInterface>()))
	{
		float CurrentHealth = IPlayerStatInterface::Execute_GetHealth(PlayerStat);
		float MaxHealth = IPlayerStatInterface::Execute_GetMaxHealth(PlayerStat);
		float HealthRatio = CurrentHealth / MaxHealth;

		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Cyan, *FString::Printf(TEXT("HP Ratio: %f"), HealthRatio));// Debug

		if (HealthRatio < ActiveHealthRatio)
		{
			GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Cyan, TEXT("Reach Ratio"));	// Debug
			AffectBuff();
		}
	}
	else
	{
		UH_LogTemp(Log, TEXT("Player do not have stat component"));
	}
}

void UArtifactObject_BleedingHeart::StatUpModifier(FWeaponBonusStat& Stat)
{
	Stat.FireSpeedUp += FireSpeedUp;
	Stat.ReloadSpeedUp += ReloadSpeedUp;
}

void UArtifactObject_BleedingHeart::StatDownModifier(FWeaponBonusStat& Stat)
{
	Stat.FireSpeedUp -= FireSpeedUp;
	Stat.ReloadSpeedUp -= ReloadSpeedUp;
}

// Increase fire and reload rate speed while {BuffDuration} seconds.
void UArtifactObject_BleedingHeart::AffectBuff()
{
	if (ensure(WeaponManager == nullptr))
	{
		UH_LogTemp(Warning, TEXT(""));
		return;
	}

	// Apply buff stat.
	FWeaponStatSetterCallback Modifier;
	Modifier.BindDynamic(this, &UArtifactObject_BleedingHeart::StatUpModifier);
	WeaponManager->ModifyDynamicStat(Modifier);

	// Set timer of disapplying buff stat after {BuffDuration} seconds.
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Cyan, TEXT("Begin Bleeding Heart Effect"));	// Debug

	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([this]() {
		// Decrease buff stat.
		FWeaponStatSetterCallback RevertModifier;
		RevertModifier.BindDynamic(this, &UArtifactObject_BleedingHeart::StatUpModifier);
		WeaponManager->ModifyDynamicStat(RevertModifier);

		bIsBuffActive = false;

		// Cooldown timer.
		bIsCooldown = true;

		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Cyan, TEXT("End Bleeding Heart Effect"));	// Debug


		FTimerDelegate CooldownCallback;
		CooldownCallback.BindLambda([this]() {
			bIsCooldown = false;
			GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Cyan, TEXT("End Bleeding Heart Cooldown"));	// Debug
			});
		GetWorld()->GetTimerManager().SetTimer(CooldownTimer, CooldownCallback, CooldownTime, false);
		});
	GetWorld()->GetTimerManager().SetTimer(BuffTimer, TimerCallback, BuffDuration, false);

	// Set buff state variables.
	BuffStartTime = GetWorld()->GetTimeSeconds();
	bIsBuffActive = true;

	// ---End setting timer---
}
