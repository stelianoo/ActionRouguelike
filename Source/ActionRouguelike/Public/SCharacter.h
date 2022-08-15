// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USActionComponent;
class ASBaseProjectile;
class USpringArmComponent;
class UCameraComponent;
class USAttributeComponent;
class USInteractionComponent;

UCLASS()
class ACTIONROUGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	ASCharacter();

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere)
	USAttributeComponent* AttributeComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USActionComponent* ActionComponent;
	
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;

	void MoveForward(float value);
	void MoveRight(float value);
	
	void PrimaryAttack();
	void AbilityOne();
	void AbilityTwo();

	void SprintStart();
	void SprintStop();

	void Interact();
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void OnHealthChange(AActor* ActorInstigator,USAttributeComponent* OwningComp,float NewHealth,float Change);

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult);

	virtual void PostInitializeComponents() override;


	UFUNCTION(Exec)
	void HealSelf(float HealAmount = 100);

	virtual FVector GetPawnViewLocation() const override;
	
};


