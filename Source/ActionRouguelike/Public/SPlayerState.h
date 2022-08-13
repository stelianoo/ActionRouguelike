// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCreditsUpdate,float,CreditAmount);

/**
 * 
 */
UCLASS()
class ACTIONROUGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

	
protected:
	
	//UPROPERTY(Replicated, BlueprintReadOnly, Category=PlayerState)
	float Credits;
	
public:

	UFUNCTION(BlueprintCallable,Category=Credits)
	float GetCredits();
	
	UFUNCTION(BlueprintCallable,Category=Credits)
	bool CreditsAdd(int AddAmount);

	UFUNCTION(BlueprintCallable,Category=Credits)
	bool CreditsSubtract(int SubtractAmount);

	UPROPERTY(BlueprintAssignable,Category=Events)
	FCreditsUpdate CreditsUpdate;
	
};
