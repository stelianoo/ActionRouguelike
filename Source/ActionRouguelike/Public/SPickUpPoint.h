// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPickUpBase.h"
#include "SPickUpPoint.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGUELIKE_API ASPickUpPoint : public ASPickUpBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere,Category=PickUp)
	float GivenCredits;
	
protected:
	void Interact_Implementation(APawn* InteractedPawn) override;
	
};
