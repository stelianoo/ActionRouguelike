// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBaseProjectile.generated.h"

class USoundCue;
class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONROUGUELIKE_API ASBaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASBaseProjectile();

	
	UPROPERTY(EditAnywhere,Category = "Effect")
	UParticleSystem* EndParticle;
	
	UPROPERTY(EditAnywhere,Category = "Effect")
	TSubclassOf<UCameraShakeBase> CameraShake;



	
	UPROPERTY(EditAnywhere,Category = "Sound")
	USoundBase* SoundCueStart;

	// UPROPERTY(EditAnywhere,Category = "Sound")
	// USoundCue* SoundCueLoop;
	
	UPROPERTY(EditAnywhere,Category = "Sound")
	USoundBase* SoundCueEnd;
	
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UProjectileMovementComponent* ProjectileMovmComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UParticleSystemComponent* ProjectileEffectComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UAudioComponent* AudioLoopCompt;

	
	
public:

	UFUNCTION()
	void OnProjectileDestroyed(AActor* DestroyedActor);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
