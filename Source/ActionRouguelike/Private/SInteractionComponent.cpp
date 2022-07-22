// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "SGameplayInterface.h"


// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjQueryParam;
	ObjQueryParam.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation,EyeRotation);

	FVector EndTrace = EyeLocation + (EyeRotation.Vector()*1000);
	
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(HitResult,EyeLocation,EndTrace,ObjQueryParam);

	AActor* HitActor = HitResult.GetActor();

	if (HitActor)
	{
		if (HitActor->Implements<USGameplayInterface>())
		{
			APawn* MyPawn = Cast<APawn>(MyOwner);

			ISGameplayInterface::Execute_Interact(HitActor,MyPawn);
		}	
	}

	DrawDebugLine(GetWorld(),EyeLocation,EndTrace,FColor::Red,false,5,100,3);
	
}













