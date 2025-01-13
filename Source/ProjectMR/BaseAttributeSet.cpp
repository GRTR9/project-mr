// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

UBaseAttributeSet::UBaseAttributeSet()
{
}

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetAttackAttribute())
	{
		SetAttack(GetAttack());
	}

	if (Data.EvaluatedData.Attribute == GetDefenseAttribute())
	{
		SetDefense(GetDefense());
	}

	if (Data.EvaluatedData.Attribute == GetSpeedAttribute())
	{
		SetSpeed(GetSpeed());
	}

	if (Data.EvaluatedData.Attribute == GetAvoidRateAttribute())
	{
		SetAvoidRate(FMath::Clamp(GetAvoidRate(), 0.0f, 100.0f));
	}

	if (Data.EvaluatedData.Attribute == GetCritRateAttribute())
	{
		SetCritRate(FMath::Clamp(GetCritRate(), 0.0f, 100.0f));
	}

	if (Data.EvaluatedData.Attribute == GetCritDamageAttribute())
	{
		SetCritDamage(GetCritDamage());
	}

	if (Data.EvaluatedData.Attribute == GetBreakDefenseAttribute())
	{
		SetBreakDefense(GetBreakDefense());
	}
}
