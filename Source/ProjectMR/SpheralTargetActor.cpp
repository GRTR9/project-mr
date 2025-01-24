// Fill out your copyright notice in the Description page of Project Settings.


#include "SpheralTargetActor.h"
#include "Abilities/GameplayAbility.h"

ASpheralTargetActor::ASpheralTargetActor()
{
}

void ASpheralTargetActor::StartTargeting(UGameplayAbility* Ability)
{
	OwningAbility = Ability;
	PrimaryPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
	SourceActor = Ability->GetOwningActorFromActorInfo();
}

void ASpheralTargetActor::ConfirmTargetingByCollision(TArray<AActor*> OtherActors)
{
	TArray<TWeakObjectPtr<AActor>> OverlapActors;
	
	for (AActor* NowActor : OtherActors)
	{
		if (IsValid(NowActor))
		{
			OverlapActors.AddUnique(TWeakObjectPtr<AActor>(NowActor));
		}
	}
	

	if (OverlapActors.Num() > 0)
	{
		const FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromActors(OverlapActors);
		TargetDataReadyDelegate.Broadcast(TargetData);
	}
	else
	{
		Super::CancelTargeting();
	}
}
