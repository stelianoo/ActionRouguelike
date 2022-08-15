// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SBaseProjectile.h"
#include "SMagicProjectile.generated.h"


UCLASS()
class ACTIONROUGUELIKE_API ASMagicProjectile : public ASBaseProjectile
{
	GENERATED_BODY()
	
public:	
	ASMagicProjectile();

	UPROPERTY(EditAnywhere,Category="Parameters")
	float ProjectileDamage = 10;

	UPROPERTY(EditAnywhere,Category="Parameters")
	FGameplayTag ParryTag;

	
	
protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OverlapEvent(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult);

	
public:	
	virtual void Tick(float DeltaTime) override;

};
