// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"


#include "SAttributeComponent.h"
#include "SGameplayFunctionLibrary.h"
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

void ASMagicProjectile::OverlapEvent(UPrimitiveComponent* PrimitiveComponent, AActor* OtherActor,
	UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		// USAttributeComponent* Atribute = USAttributeComponent::GetAttributes(OtherActor);
		// if (Atribute)
		// {
		// 	Atribute->ApplyHealthChange(GetInstigator(),-ProjectileDamage);
		// 	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),EndParticle,GetActorLocation());
		// 	UE_LOG(LogTemp,Warning,TEXT("Overlap"));
		// 	Destroy();
		// }

		if(	USGameplayFunctionLibrary::ApplyDamageDirectinal(GetInstigator(),
				OtherActor,ProjectileDamage,HitResult))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),EndParticle,GetActorLocation());
			Destroy();
		}

		
	}
}

void ASMagicProjectile::HitEvent(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
	UPrimitiveComponent* PrimitiveComponent1, FVector Vector, const FHitResult& HitResult)
{
	// if (Actor)
	// {
	// 	if (Actor != GetInstigator())
	// 	{
	// 		//UE_LOG(LogTemp,Warning,TEXT("ObjectHit"));
	// 		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),EndParticle,GetActorLocation());
	// 		Destroy();
	// 	}
	//
	// 	USAttributeComponent* Atribute = USAttributeComponent::GetAttributes(Actor);
	// 	if (Atribute)
	// 	{
	// 		Atribute->ApplyHealthChange(GetInstigator(),-ProjectileDamage);
	// 		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),EndParticle,GetActorLocation());
	// 		//UE_LOG(LogTemp,Warning,TEXT("Overlap"));
	// 		Destroy();
	// 	}
	// }
}


void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

