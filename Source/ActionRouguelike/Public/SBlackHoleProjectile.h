// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "SBlackHoleProjectile.generated.h"

class URadialForceComponent;
UCLASS()
class ACTIONROUGUELIKE_API ASBlackHoleProjectile : public ASBaseProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASBlackHoleProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	URadialForceComponent* RadialForceComponent;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
