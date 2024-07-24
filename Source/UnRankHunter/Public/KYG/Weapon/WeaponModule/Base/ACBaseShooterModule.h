// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KYG/Weapon/WeaponModule/Base/ACBaseWeaponModule.h"
#include "ACBaseShooterModule.generated.h"

UENUM(BlueprintType)
enum class EWeaponShooterOrigin : uint8
{
	MainCameraCenter,
	MuzzlePosition,
};

UENUM(BlueprintType)
enum class EWeaponBulletType : uint8
{
	Hitscan,
	Projectile,
	Area
};

USTRUCT(BlueprintType)
struct FShootingInfo
{
	GENERATED_BODY()

	// Specifies whether the projectile is hitscan or an actual projectile actor.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponBulletType BulletType{};

	// Number of bullets fired.
	// For weapons like shotguns that fire multiple pellets, specify the number of pellets fired.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BulletCount{};

	// Used when BulletType == Hitscan.
	// End points of the hitscan.
	// If the hitscan is blocked, it points to the block location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> HitscanEndPoints{};

	// Used when BulletType == Hitscan or BulletType == Area.
	// All hit results of the hitscan or overlap.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FHitResult> HitResults{};

	// Used when BulletType == Projectile.
	// References to all generated projectiles.
	// Avoid storing references to projectiles as it is difficult to predict their destruction time.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Projectiles{};

	// Used when BulletType == Projectile.
	// Class of the projectile.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ProjectileClass{};

	// Center location where the shot was fired.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector MuzzleLocation{};

	// Center direction where the shot was fired.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator MuzzleRotator{};
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnShooterExecutedEvent, AActor*, OwnerActor, ABaseWeapon*, ShooterWeapon, const FShootingInfo&, ShootingInfo);


UCLASS(Abstract, BlueprintType, Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNRANKHUNTER_API UACBaseShooterModule : public UACBaseWeaponModule
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Modules|Shooter Module")
	void ShotBullet(float TriggerRate);

public:
	// Returns the muzzle firing position of the weapon.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Modules|Shooter Module")
	FTransform GetMuzzlePosition();

	// Returns the camera position.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Modules|Shooter Module")
	FTransform GetCameraPosition();

	// Returns the position of either the camera or the muzzle based on the WeaponShooterOrigin setting.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Modules|Shooter Module")
	FTransform GetSettingPosition();


protected:
	// Sets the firing point of the weapon to either the camera or the muzzle.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modules|Shooter Module")
	EWeaponShooterOrigin WeaponShooterOrigin;

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Module|Shooter Module")
	FOnShooterExecutedEvent OnShooterExecutedEvent;
};