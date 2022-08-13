// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameplayFunctionLibrary.h"

#include "SAttributeComponent.h"
#include "GameFramework/PlayerState.h"

bool USGameplayFunctionLibrary::ApplyDamage(AActor* DamageApplier, AActor* DamageTaker, float DamageAmount)
{
	USAttributeComponent* AttributeComponent = USAttributeComponent::GetAttributes(DamageTaker);
	if (AttributeComponent)
	{
		return AttributeComponent->ApplyHealthChange(DamageApplier,-DamageAmount);
	}
	return false;
}

bool USGameplayFunctionLibrary::ApplyDamageDirectinal(AActor* DamageApplier, AActor* DamageTaker, float DamageAmount,
	const FHitResult& HitResult)
{
	if (ApplyDamage(DamageApplier,DamageTaker,DamageAmount))
	{
		UPrimitiveComponent* HitComp = HitResult.GetComponent();
		if (HitComp && HitComp->IsSimulatingPhysics(HitResult.BoneName))
		{
			// Direction = trarget - origin
			FVector Direction = HitResult.TraceStart-HitResult.TraceEnd;
			Direction.Normalize();
			UE_LOG(LogTemp,Warning,TEXT("Appling directional force : %s"),*Direction.ToString());
			HitComp->AddImpulseAtLocation(Direction * 100000,HitResult.ImpactPoint,HitResult.BoneName);
		}
		return true;
	}
	return false;
}

