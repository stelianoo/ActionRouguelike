// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlackHoleProjectile.h"

#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASBlackHoleProjectile::ASBlackHoleProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComponent->SetupAttachment(RootComponent);
	RadialForceComponent->SetAutoActivate(false);

	RadialForceComponent->AddCollisionChannelToAffect(ECC_WorldDynamic);
	
}

// Called when the game starts or when spawned
void ASBlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBlackHoleProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

