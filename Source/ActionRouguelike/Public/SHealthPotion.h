// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPickUpBase.h"
#include "SHealthPotion.generated.h"



UCLASS()
class ACTIONROUGUELIKE_API ASHealthPotion : public ASPickUpBase
{
	GENERATED_BODY()
	
public:

	ASHealthPotion();
	
	UPROPERTY(EditAnywhere)
	float HealthPoints = 10;

public:	

	void Interact_Implementation(APawn* InteractedPawn) override;
	
};
