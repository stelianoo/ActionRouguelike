// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlinkProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


void ASBlinkProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComponent->OnComponentHit.AddDynamic(this,&ASBlinkProjectile::OnCompHit);
	
	GetWorldTimerManager().SetTimer(TimerHandleProjectile,this,&ASBlinkProjectile::BlinkStart,
		0.2f,false);
	
}


void ASBlinkProjectile::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit)
{
	BlinkStart();
}

void ASBlinkProjectile::BlinkStart()
{
	ProjectileMovmComp->StopMovementImmediately();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),EndParticle,GetActorLocation());
	GetWorldTimerManager().SetTimer(TimerHandleBlink,this,&ASBlinkProjectile::Blink,
		0.2f,false);
	ProjectileEffectComp->SetVisibility(false);
}

void ASBlinkProjectile::Blink()
{
	FTransform Transform = FTransform(GetInstigator()->GetActorRotation(),GetActorLocation());
	//Transform.Rotator() = GetInstigator()->GetActorRotation();
	GetInstigator()->SetActorTransform(Transform,false,
		nullptr,ETeleportType::TeleportPhysics);
	Destroy();
}
