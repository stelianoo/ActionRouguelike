// Fill out your copyright notice in the Description page of Project Settings.


#include "SBaseProjectile.h"

#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ASBaseProjectile::ASBaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComponent->SetCollisionProfileName("Projectile");
	RootComponent = SphereComponent;

	ProjectileEffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	ProjectileEffectComp->SetupAttachment(RootComponent);
	
	ProjectileMovmComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovmComp");
	ProjectileMovmComp->bRotationFollowsVelocity = true;
	ProjectileMovmComp->bInitialVelocityInLocalSpace = true;
	ProjectileMovmComp->ProjectileGravityScale = 0;
}

// Called when the game starts or when spawned
void ASBaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp,Warning,TEXT("StatMetod of class BaseProjectile"));
	
	SphereComponent->IgnoreActorWhenMoving(this->GetInstigator(),true);
	
}

// Called every frame
void ASBaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

