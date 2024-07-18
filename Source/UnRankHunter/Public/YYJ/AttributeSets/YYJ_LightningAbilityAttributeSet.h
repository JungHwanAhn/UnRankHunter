// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "YYJ_LightningAbilityAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 *
 */
UCLASS()
class UNRANKHUNTER_API UYYJ_LightningAbilityAttributeSet : public UAttributeSet
{
	GENERATED_BODY()


	UPROPERTY()
	FGameplayAttributeData Damage;

	ATTRIBUTE_ACCESSORS(ULightningAbilityAttributeSet, Damage)

		UPROPERTY()
	FGameplayAttributeData MaxBounces;

	ATTRIBUTE_ACCESSORS(ULightningAbilityAttributeSet, MaxBounces)

		UPROPERTY()
	FGameplayAttributeData Duration;

	ATTRIBUTE_ACCESSORS(ULightningAbilityAttributeSet, Duration)

		UPROPERTY()
	FGameplayAttributeData BounceRadius;

	ATTRIBUTE_ACCESSORS(ULightningAbilityAttributeSet, BounceRadius)
};
