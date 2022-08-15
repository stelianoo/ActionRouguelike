// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SAction_Projectile.generated.h"

class ASCharacter;
/**
 * 
 */
UCLASS()
class ACTIONROUGUELIKE_API USAction_Projectile : public USAction
{
	GENERATED_BODY()

public:
	USAction_Projectile();
	
protected:

	UPROPERTY(EditAnywhere,Category = "Attack")
	TSubclassOf<AActor> ProjectClass;

	UPROPERTY(VisibleAnywhere,Category="Attack")
	FName HandSocketName;

	UPROPERTY(EditAnywhere,Category = "Attack")
	float ProjectDelay;
	
	UPROPERTY(EditAnywhere,Category = "Attack")
	UParticleSystem* CastEffect;
	
	UPROPERTY(EditAnywhere,Category = "Attack")
	UAnimMontage* CastAnimMontage;
	
	FTimerHandle TimerHandle_Cast;

	UFUNCTION()
	void ProjectileCast_Elapsed(ASCharacter* InstigatorCharacter);
	
public:

	virtual void StartAction_Implementation(AActor* Instigator) override;

	
	
};
