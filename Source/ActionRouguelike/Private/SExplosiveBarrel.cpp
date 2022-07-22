// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"

#include "PhysicsEngine/RadialForceComponent.h"
#include "SMagicProjectile.h"
#include "Particles/ParticleSystemComponent.h"


void ASExplosiveBarrel::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                  FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		// if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
		// 	FString::Printf(TEXT("I Hit: %s"), *OtherActor->GetName()));
		
		if (Cast<ASMagicProjectile>(OtherActor))
		{
			RadialForceComponent->FireImpulse();
			EffectComp->Activate();
			//this->Destroy();
		}
	}
}

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	StaticMeshComponent->SetSimulatePhysics(true);
	
	
	RootComponent = StaticMeshComponent;
	
	
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComponent->SetupAttachment(RootComponent);
	

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent->OnComponentHit.AddDynamic(this,&ASExplosiveBarrel::OnCompHit);
}

// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

