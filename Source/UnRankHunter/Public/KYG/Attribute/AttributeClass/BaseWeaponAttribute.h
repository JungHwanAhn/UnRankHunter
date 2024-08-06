// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Weapon/Structure/WeaponStructure.h"
#include "Weapon/Core/BaseClass/BaseWeapon.h"
#include "BaseWeaponAttribute.generated.h"


/**
 *
 */
UCLASS(Abstract, BlueprintType)
class UNRANKHUNTER_API UBaseWeaponAttribute : public UObject
{
	GENERATED_BODY()

protected:
	virtual void OnAttributeEnabled() PURE_VIRTUAL(UBaseWeaponAttribute::OnAttributeAttached, ;);
	virtual void OnAttributeDisabled() PURE_VIRTUAL(UBaseWeaponAttribute::OnAttributeDetached, ;);

public:
	UFUNCTION(BlueprintCallable, Category = "Weapon Attribute")
	void InitializeOnCreated(class ABaseWeapon* BaseWeapon);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon Attribute")
	void ApplyBonusStat(FWeaponBonusStat& InWeapon) const;

	UFUNCTION(BlueprintCallable, Category = "Weapon Attribute")
	void EnableAttribute(bool bUpdate = false);

	UFUNCTION(BlueprintCallable, Category = "Weapon Attribute")
	void DisableAttribute(bool bUpdate = false);

	UFUNCTION(BlueprintCallable, Category = "Weapon Attribute")
	FName GetAttributeID() const
	{
		return AttributeID;
	}

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Attribute")
	FName AttributeID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Attribute")
	FWeaponBonusStat BonusStat;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon Attribute")
	class ABaseWeapon* ParentWeapon;
};
