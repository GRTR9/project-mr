// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "SpheralTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMR_API ASpheralTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
public:
	ASpheralTargetActor();

	virtual void StartTargeting(UGameplayAbility* Ability) override;

	UFUNCTION(BlueprintCallable, Category = "SpheralTargetActor")
	void ConfirmTargetingByCollision(TArray<AActor*> OtherActors);
};
