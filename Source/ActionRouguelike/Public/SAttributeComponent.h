// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROUGUELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();

protected:

	UPROPERTY(BlueprintReadOnly,VisibleDefaultsOnly,Category="Attributes")
	float Health;

public:

	UFUNCTION(BlueprintCallable,Category="Attributes")
	bool ApplyHealthChange(float ChangeValue);
};
