// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SAICharacter.generated.h"

class UPawnSensingComponent;
UCLASS()
class ACTIONROUGUELIKE_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()

	UFUNCTION()
	
	virtual void PostInitializeComponents() override;

protected:
	
	UPROPERTY(EditDefaultsOnly,Category="AI")
	UPawnSensingComponent* PawnsensingComp;

	UFUNCTION()
	void OnPawnSee(APawn* Pawn);
	
public:
	// Sets default values for this character's properties
	ASAICharacter();

	
};
