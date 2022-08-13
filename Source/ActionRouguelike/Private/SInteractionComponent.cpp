// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "SGameplayInterface.h"



static TAutoConsoleVariable<bool> CVarDrawDebug(TEXT("su.DebugDraw"),
	false,TEXT("Draw debug visibility."),ECVF_Cheat);



// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	
}

void USInteractionComponent::PrimaryInteract()
{

	bool DrawDebug = CVarDrawDebug.GetValueOnGameThread();
	
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
		if (DrawDebug)
		{
			DrawDebugSphere(GetWorld(),HitResult.Location,15,8,FColor::White,false,5,100,2);
		}
		if (HitActor->Implements<USGameplayInterface>())
		{
			APawn* MyPawn = Cast<APawn>(MyOwner);

			ISGameplayInterface::Execute_Interact(HitActor,MyPawn);
		}
		
	}
	if (DrawDebug)
	{
		DrawDebugLine(GetWorld(),EyeLocation,EndTrace,FColor::Red,false,5,100,3);
	}
	
	
}


void USInteractionComponent::OnInteractBeginOverlap(AActor* Actor)
{
	if (Actor->Implements<USGameplayInterface>())
	{
		APawn* MyPawn = Cast<APawn>(GetOwner());
		ISGameplayInterface::Execute_Interact(Actor,MyPawn);
	}
}











