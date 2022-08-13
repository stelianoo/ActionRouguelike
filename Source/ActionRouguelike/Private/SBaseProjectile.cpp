// Fill out your copyright notice in the Description page of Project Settings.


#include "SBaseProjectile.h"

#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


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

	AudioLoopCompt = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	AudioLoopCompt->SetupAttachment(RootComponent);
	
	ProjectileMovmComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovmComp");
	ProjectileMovmComp->bRotationFollowsVelocity = true;
	ProjectileMovmComp->bInitialVelocityInLocalSpace = true;
	ProjectileMovmComp->ProjectileGravityScale = 0;


	OnDestroyed.AddDynamic(this,&ASBaseProjectile::OnProjectileDestroyed);
	
}

// Called when the game starts or when spawned
void ASBaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp,Warning,TEXT("StatMetod of class BaseProjectile"));
	UGameplayStatics::PlaySoundAtLocation(GetWorld(),SoundCueStart,GetActorLocation(),FRotator::ZeroRotator);
	
	SphereComponent->IgnoreActorWhenMoving(this->GetInstigator(),true);
	
}

void ASBaseProjectile::OnProjectileDestroyed(AActor* DestroyedActor)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(),SoundCueEnd,GetActorLocation(),FRotator::ZeroRotator);
	//UE_LOG(LogTemp,Warning,TEXT("Projectile destroyed"));
	UGameplayStatics::PlayWorldCameraShake(GetWorld(),CameraShake,GetActorLocation(),500,2000,0.4f);
}

// Called every frame
void ASBaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

