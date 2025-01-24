// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageExecutionCalculation.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.h"

#define BREAK_DEFENSE_N 1000

struct SDamageStatics
{
	//Source
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritRate);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BreakDefense);
	//Target
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Defense);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AvoidRate);

	SDamageStatics()
	{
		//Source
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Attack, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, CritRate, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, CritDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, BreakDefense, Source, false);
		//Target
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Health, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Defense, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, AvoidRate, Target, false);
	}
};

static const SDamageStatics& DamageStatics()
{
	static SDamageStatics DStatics;
	return DStatics;
}
UDamageExecutionCalculation::UDamageExecutionCalculation()
{
	RelevantAttributesToCapture.Add(DamageStatics().AttackDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritRateDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().BreakDefenseDef);
	RelevantAttributesToCapture.Add(DamageStatics().HealthDef);
	RelevantAttributesToCapture.Add(DamageStatics().DefenseDef);
	RelevantAttributesToCapture.Add(DamageStatics().AvoidRateDef);
}

void UDamageExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UE_LOG(LogTemp, Log, TEXT("Execute_Implementation"));
	UAbilitySystemComponent* TargetAbilitySystemComp = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComp = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* TargetActor = TargetAbilitySystemComp ? TargetAbilitySystemComp->GetAvatarActor() : nullptr;
	AActor* SourceActor = SourceAbilitySystemComp ? SourceAbilitySystemComp->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	//Source
	float Attack = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AttackDef, EvaluationParameters, Attack);
	float CritRate = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritRateDef, EvaluationParameters, CritRate);
	float CritDamage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritDamageDef, EvaluationParameters, CritDamage);
	float BreakDefense = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BreakDefenseDef, EvaluationParameters, BreakDefense);
	//Target
	float Health = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().HealthDef, EvaluationParameters, Health);
	float Defense = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DefenseDef, EvaluationParameters, Defense);
	float AvoidRate = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AvoidRateDef, EvaluationParameters, AvoidRate);

	float Damage = Attack;
	bool IsAvoid = FMath::FRand() <= AvoidRate;
	bool IsCrit = FMath::FRand() <= CritRate;

	if (IsCrit)
		Damage *= CritDamage;

	//(1+old defense/n)/(1+new defense/n)
	float PostBreakDefenseMultiplier = (1 + Defense / BREAK_DEFENSE_N) / (1 + FMath::Max(Defense - BreakDefense, 0.0f) / BREAK_DEFENSE_N);
	Damage *= PostBreakDefenseMultiplier;

	//Damage / (1+old defense/n)
	Damage /= (1 + Defense / BREAK_DEFENSE_N);

	//Log
	//UE_LOG(LogTemp, Log, TEXT("Attack is %.2f"), Attack);
	//UE_LOG(LogTemp, Log, TEXT("CritRate is %.2f"), CritRate);
	//UE_LOG(LogTemp, Log, TEXT("CritDamage is %.2f"), CritDamage);
	//UE_LOG(LogTemp, Log, TEXT("BreakDefense is %.2f"), BreakDefense);
	//UE_LOG(LogTemp, Log, TEXT("Defense is %.2f"), Defense);
	//UE_LOG(LogTemp, Log, TEXT("AvoidRate is %.2f"), AvoidRate);
	//UE_LOG(LogTemp, Log, TEXT("Damage is %.2f"), Damage);

	//Limit
	Damage = FMath::Clamp(Damage, 0.0f, Health);

	//Avoid Or Not
	if (!IsAvoid)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HealthProperty, EGameplayModOp::Additive, -Damage));
	}
}
