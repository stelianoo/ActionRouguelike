// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"


#include "SAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASMagicProjectile::ASMagicProjectile() : ASBaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovmComp->InitialSpeed = 2500;

	
}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&ASMagicProjectile::OverlapEvent);
	SphereComponent->OnComponentHit.AddDynamic(this,&ASMagicProjectile::HitEvent);
}

void ASMagicProjectile::OverlapEvent(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
	UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult)
{
	if (Actor)
	{
		USAttributeComponent* Atribute = Cast<USAttributeComponent>(Actor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (Atribute)
		{
			Atribute->ApplyHealthChange(-ProjectileDamage);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),EndParticle,GetActorLocation());
			UE_LOG(LogTemp,Warning,TEXT("Overlap"));
			Destroy();
		}
	}
}

void ASMagicProjectile::HitEvent(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
	UPrimitiveComponent* PrimitiveComponent1, FVector Vector, const FHitResult& HitResult)
{
	if (Actor != GetInstigator())
	{
		UE_LOG(LogTemp,Warning,TEXT("ObjectHit"));
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),EndParticle,GetActorLocation());
		Destroy();
	}
	
	
}


void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

