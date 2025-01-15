// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePaperZDCharacter.h"
#include "BaseAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"

ABasePaperZDCharacter::ABasePaperZDCharacter()
{
	//GAS
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	BaseAttributeSetComp = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("BaseAttributeSetComp"));
}

void ABasePaperZDCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComp)
	{
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(BaseAttributeSetComp->GetHealthAttribute()).AddUObject(this, &ABasePaperZDCharacter::OnHealthChangeNative);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(BaseAttributeSetComp->GetAttackAttribute()).AddUObject(this, &ABasePaperZDCharacter::OnAttackChangeNative);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(BaseAttributeSetComp->GetDefenseAttribute()).AddUObject(this, &ABasePaperZDCharacter::OnDenseChangeNative);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(BaseAttributeSetComp->GetSpeedAttribute()).AddUObject(this, &ABasePaperZDCharacter::OnSpeedChangeNative);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(BaseAttributeSetComp->GetAvoidRateAttribute()).AddUObject(this, &ABasePaperZDCharacter::OnAvoidRateChangeNative);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(BaseAttributeSetComp->GetCritRateAttribute()).AddUObject(this, &ABasePaperZDCharacter::OnCritRateChangeNative);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(BaseAttributeSetComp->GetCritDamageAttribute()).AddUObject(this, &ABasePaperZDCharacter::OnCritDamageChangeNative);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(BaseAttributeSetComp->GetBreakDefenseAttribute()).AddUObject(this, &ABasePaperZDCharacter::OnBreakDefenseChangeNative);
	}
}

UAbilitySystemComponent* ABasePaperZDCharacter::GetUAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void ABasePaperZDCharacter::OnHealthChangeNative(const FOnAttributeChangeData& Data)
{
	OnHealthChange(Data.OldValue, Data.NewValue);
}

void ABasePaperZDCharacter::OnAttackChangeNative(const FOnAttributeChangeData& Data)
{
	OnAttackChange(Data.OldValue, Data.NewValue);
}

void ABasePaperZDCharacter::OnDenseChangeNative(const FOnAttributeChangeData& Data)
{
	OnDenseChange(Data.OldValue, Data.NewValue);
}

void ABasePaperZDCharacter::OnSpeedChangeNative(const FOnAttributeChangeData& Data)
{
	UCharacterMovementComponent* CharMoveComp = Cast<UCharacterMovementComponent>(GetCharacterMovement());
	CharMoveComp->MaxWalkSpeed = Data.NewValue;
	OnSpeedChange(Data.OldValue, Data.NewValue);
}

void ABasePaperZDCharacter::OnAvoidRateChangeNative(const FOnAttributeChangeData& Data)
{
	OnAvoidRateChange(Data.OldValue, Data.NewValue);
}

void ABasePaperZDCharacter::OnCritRateChangeNative(const FOnAttributeChangeData& Data)
{
	OnCritRateChange(Data.OldValue, Data.NewValue);
}

void ABasePaperZDCharacter::OnCritDamageChangeNative(const FOnAttributeChangeData& Data)
{
	OnCritDamageChange(Data.OldValue, Data.NewValue);
}

void ABasePaperZDCharacter::OnBreakDefenseChangeNative(const FOnAttributeChangeData& Data)
{
	OnBreakDefenseChange(Data.OldValue, Data.NewValue);
}
