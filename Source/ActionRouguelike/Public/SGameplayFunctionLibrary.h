// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SGameplayFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGUELIKE_API USGameplayFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable,Category=Gameplay)
	static bool ApplyDamage(AActor* DamageApplier,AActor* DamageTaker,float DamageAmount);

	UFUNCTION(BlueprintCallable,Category=Gameplay)
	static bool ApplyDamageDirectinal(AActor* DamageApplier,AActor* DamageTaker,float DamageAmount,const FHitResult& HitResult);
	
	
	
};
