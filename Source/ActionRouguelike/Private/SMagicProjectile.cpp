// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"


#include "SActionComponent.h"
#include "SAttributeComponent.h"
#include "SGameplayFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASMagicProjectile::ASMagicProjectile() : ASBaseProjectile()
{

	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovmComp->InitialSpeed = 2500;
	
}

void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&ASMagicProjectile::OverlapEvent);
}

void ASMagicProjectile::OverlapEvent(UPrimitiveComponent* PrimitiveComponent, AActor* OtherActor,
	UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		
		USActionComponent* ActionComp = Cast<USActionComponent>(
			OtherActor->GetComponentByClass(USActionComponent::StaticClass()));
		if (ActionComp && ActionComp->ActiveGameplayTags.HasTag(ParryTag))
		{
			UE_LOG(LogTemp,Error,TEXT("REFLECTED"));
			ProjectileMovmComp->Velocity = -ProjectileMovmComp->Velocity;

			SetInstigator(Cast<APawn>(OtherActor));
			return;
		}
		
		if(	USGameplayFunctionLibrary::ApplyDamageDirectinal(GetInstigator(),
				OtherActor,ProjectileDamage,HitResult))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),EndParticle,GetActorLocation());
			Destroy();
		}
	}
}

void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

