// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"

// Sets default values
ASItemChest::ASItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChestBase = CreateDefaultSubobject<UStaticMeshComponent>("ChestBase");
	RootComponent =	ChestBase;
	
	ChestTop = CreateDefaultSubobject<UStaticMeshComponent>("ChestTop");
	ChestTop->SetupAttachment(RootComponent);

	TargetPitch = 110;
}

void ASItemChest::Interact_Implementation(APawn* InteractedPawn)
{
	ChestTop->SetRelativeRotation(FRotator(TargetPitch,0,0));
}

// Called when the game starts or when spawned
void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

