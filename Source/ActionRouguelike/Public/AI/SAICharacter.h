// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SAICharacter.generated.h"

class USWorldUserWidget;
class USAttributeComponent;
class UPawnSensingComponent;
UCLASS()
class ACTIONROUGUELIKE_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()

	UFUNCTION()
	
	virtual void PostInitializeComponents() override;

protected:
	
	UPROPERTY(EditDefaultsOnly,Category="AI")
	UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(VisibleAnywhere)
	USAttributeComponent* AttributeComponent;

	UFUNCTION()
	void OnPawnSee(APawn* Pawn);

	UPROPERTY(VisibleDefaultsOnly, Category = UI)
	USWorldUserWidget* ActiveHealthBar;
	
public:

	UPROPERTY(EditDefaultsOnly,Category = UI)
	TSubclassOf<UUserWidget> WorldHealthWidget;
	
	// Sets default values for this character's properties
	ASAICharacter();

	UFUNCTION()
	void SetTargetActor(AActor *NewActor);
	
	UFUNCTION(BlueprintCallable)
	void OnHealthChange(AActor* ActorInstigator,USAttributeComponent* OwningComp,float NewHealth,float Change);

};
