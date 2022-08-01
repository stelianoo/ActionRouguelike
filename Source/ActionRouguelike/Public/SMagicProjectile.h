// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "SMagicProjectile.generated.h"




UCLASS()
class ACTIONROUGUELIKE_API ASMagicProjectile : public ASBaseProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASMagicProjectile();


	UPROPERTY(EditAnywhere,Category="Parameters")
	float ProjectileDamage = 10;
	
protected:

	
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OverlapEvent(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult);

	UFUNCTION()
	void HitEvent(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1,FVector Vector, const FHitResult& HitResult);
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
