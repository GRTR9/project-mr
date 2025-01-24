// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

UBaseAttributeSet::UBaseAttributeSet()
{
}

void UBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	else if (Attribute == GetMaxHealthAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.0f);
	}
	else if (Attribute == GetAttackAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.0f);
	}
	else if (Attribute == GetDefenseAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.0f);
	}
	else if (Attribute == GetSpeedAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.0f);
	}
	else if (Attribute == GetAvoidRateAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, 100.0f);
	}
	else if (Attribute == GetCritRateAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, 100.0f);
	}
	else if (Attribute == GetCritDamageAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.0f);
	}
	else if (Attribute == GetBreakDefenseAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.0f);
	}
}

//void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
//{
//	Super::PostGameplayEffectExecute(Data);
//
//	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
//	{
//		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
//	}
//
//	if (Data.EvaluatedData.Attribute == GetAttackAttribute())
//	{
//		SetAttack(FMath::Max(GetAttack(), 0.0f));
//	}
//
//	if (Data.EvaluatedData.Attribute == GetDefenseAttribute())
//	{
//		SetDefense(FMath::Max(GetDefense(), 0.0f));
//	}
//
//	if (Data.EvaluatedData.Attribute == GetSpeedAttribute())
//	{
//		SetSpeed(FMath::Max(GetSpeed(), 0.0f));
//	}
//
//	if (Data.EvaluatedData.Attribute == GetAvoidRateAttribute())
//	{
//		SetAvoidRate(FMath::Clamp(GetAvoidRate(), 0.0f, 100.0f));
//	}
//
//	if (Data.EvaluatedData.Attribute == GetCritRateAttribute())
//	{
//		SetCritRate(FMath::Clamp(GetCritRate(), 0.0f, 100.0f));
//	}
//
//	if (Data.EvaluatedData.Attribute == GetCritDamageAttribute())
//	{
//		SetCritDamage(FMath::Max(GetCritDamage(), 0.0f));
//	}
//
//	if (Data.EvaluatedData.Attribute == GetBreakDefenseAttribute())
//	{
//		SetBreakDefense(FMath::Max(GetBreakDefense(), 0.0f));
//	}
//}
