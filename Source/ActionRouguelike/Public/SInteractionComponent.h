// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SInteractionComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROUGUELIKE_API USInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	USInteractionComponent();


	void PrimaryInteract();
	
	void OnInteractBeginOverlap(AActor* Actor);

};
