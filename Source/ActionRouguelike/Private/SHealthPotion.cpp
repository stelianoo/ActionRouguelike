// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"

#include "SAttributeComponent.h"
#include "Components/SphereComponent.h"



// Sets default values
ASHealthPotion::ASHealthPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComponent->SetupAttachment(RootComponent);

}



// Called when the game starts or when spawned
void ASHealthPotion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASHealthPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASHealthPotion::Interact_Implementation(APawn* InteractedPawn)
{
	USAttributeComponent* Atribute = Cast<USAttributeComponent>(InteractedPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
	
	// Can apply?
	if (Atribute->IsFullHealth())
	{
		return;
	}
	
	// Buff
	
	Atribute->ApplyHealthChange(HealthPoints);

	// Cool Down

	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComponent->SetVisibility(false,true);
	
	GetWorldTimerManager().SetTimer(timeHandler,this,&ASHealthPotion::SetupHeathPotion,
		InactiveTime,false);
}

void ASHealthPotion::SetupHeathPotion()
{
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetVisibility(true,true);
}

