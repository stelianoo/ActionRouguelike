// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "SBlinkProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGUELIKE_API ASBlinkProjectile : public ASBaseProjectile
{
	GENERATED_BODY()

	void BeginPlay();


	FTimerHandle TimerHandleProjectile;
	FTimerHandle TimerHandleBlink;
	
protected:
	
	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	
	void BlinkStart();
	void Blink();
};
