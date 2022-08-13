// Fill out your copyright notice in the Description page of Project Settings.


#include "STargetDummy.h"

#include "SAttributeComponent.h"

// Sets default values
ASTargetDummy::ASTargetDummy()
{
 	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;
	
	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>("AttributeComponent");
	AttributeComponent->OnHealthChange.AddDynamic(this,&ASTargetDummy::OnHealthChange);
	
}

void ASTargetDummy::OnHealthChange(AActor* ActorInstigator, USAttributeComponent* OwningComp, float NewHealth,
	float Change)
{
	
	if (Change < 0.0f)
	{
		UE_LOG(LogTemp,Warning,TEXT("Dummy Hit Effect"));
		MeshComponent->SetScalarParameterValueOnMaterials("TimeToHit",GetWorld()->TimeSeconds);
	}
}



