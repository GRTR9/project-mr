// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "BasePaperZDCharacter.generated.h"

/**
 *
 */
UCLASS()
class PROJECTMR_API ABasePaperZDCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	ABasePaperZDCharacter();

protected:
	virtual void BeginPlay() override;

public:
	//GAS
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BasePaperZDCharacter")
	UAbilitySystemComponent* AbilitySystemComp;

	virtual UAbilitySystemComponent* GetUAbilitySystemComponent() const;

	//Declare BaseAttributeSetComp
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BasePaperZDCharacter")
	class UBaseAttributeSet* BaseAttributeSetComp;

	//On Attribute Change
	void OnHealthChangeNative(const FOnAttributeChangeData& Data);

	void OnAttackChangeNative(const FOnAttributeChangeData& Data);

	void OnDenseChangeNative(const FOnAttributeChangeData& Data);

	void OnSpeedChangeNative(const FOnAttributeChangeData& Data);

	void OnAvoidRateChangeNative(const FOnAttributeChangeData& Data);

	void OnCritRateChangeNative(const FOnAttributeChangeData& Data);

	void OnCritDamageChangeNative(const FOnAttributeChangeData& Data);

	void OnBreakDefenseChangeNative(const FOnAttributeChangeData& Data);

	//Blueprint Event
	UFUNCTION(BlueprintImplementableEvent, Category = "BasePaperZDCharacter")
	void OnHealthChange(float OldValue, float NewValue);

	UFUNCTION(BlueprintImplementableEvent, Category = "BasePaperZDCharacter")
	void OnAttackChange(float OldValue, float NewValue);

	UFUNCTION(BlueprintImplementableEvent, Category = "BasePaperZDCharacter")
	void OnDenseChange(float OldValue, float NewValue);

	UFUNCTION(BlueprintImplementableEvent, Category = "BasePaperZDCharacter")
	void OnSpeedChange(float OldValue, float NewValue);

	UFUNCTION(BlueprintImplementableEvent, Category = "BasePaperZDCharacter")
	void OnAvoidRateChange(float OldValue, float NewValue);

	UFUNCTION(BlueprintImplementableEvent, Category = "BasePaperZDCharacter")
	void OnCritRateChange(float OldValue, float NewValue);

	UFUNCTION(BlueprintImplementableEvent, Category = "BasePaperZDCharacter")
	void OnCritDamageChange(float OldValue, float NewValue);

	UFUNCTION(BlueprintImplementableEvent, Category = "BasePaperZDCharacter")
	void OnBreakDefenseChange(float OldValue, float NewValue);
};
