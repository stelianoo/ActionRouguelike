// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SPickUpBase.generated.h"

class USphereComponent;

UCLASS()
class ACTIONROUGUELIKE_API ASPickUpBase : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPickUpBase();

	UPROPERTY(EditAnywhere)
	float InactiveTime = 10;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;

	FTimerHandle timeHandler;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(APawn* InteractedPawn) override;

protected:

	bool CheckInteractCost(APawn* InteractedPawn, bool CostInteract,float CostOfInteract);
	
	void TriggerInactivity();

	
private:
	void TriggerCooldownFalse();
	void TriggerCooldown(bool bNewState);
};
