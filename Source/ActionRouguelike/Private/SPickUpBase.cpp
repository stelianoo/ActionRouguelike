// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickUpBase.h"

#include "SCharacter.h"
#include "SPlayerState.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASPickUpBase::ASPickUpBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComponent->SetupAttachment(RootComponent);

	SphereComponent->SetSphereRadius(64);
	
}

// Called when the game starts or when spawned
void ASPickUpBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASPickUpBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASPickUpBase::Interact_Implementation(APawn* InteractedPawn)
{
	
}

bool ASPickUpBase::CheckInteractCost(APawn* InteractedPawn, bool CostInteract, float CostOfInteract)
{
	if (CostInteract)
	{
		ASCharacter* Character = Cast<ASCharacter>(InteractedPawn);
		if (Character)
		{
			ASPlayerState* PlayerState = Cast<ASPlayerState>(UGameplayStatics::GetPlayerState(this,0));
			//UE_LOG(LogTemp,Warning,TEXT("v1 - %f v2 - %f"),PlayerState->GetCredits() , CostOfInteract)
			if (PlayerState->GetCredits() >= CostOfInteract)
			{
				PlayerState->CreditsSubtract(CostOfInteract);
				return true;
			}
		}
		return false;
	}
	return true;
}

void ASPickUpBase::TriggerInactivity()
{
	TriggerCooldown(false);
	GetWorldTimerManager().SetTimer(timeHandler,this,
		&ASPickUpBase::TriggerCooldownFalse,InactiveTime,false);
}

void ASPickUpBase::TriggerCooldownFalse()
{
	TriggerCooldown(true);
}

void ASPickUpBase::TriggerCooldown(bool bNewState)
{
	SetActorEnableCollision(bNewState);
	SphereComponent->SetVisibility(bNewState,true);
}

