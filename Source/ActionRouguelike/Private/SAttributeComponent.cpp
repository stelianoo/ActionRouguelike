// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	
}

bool USAttributeComponent::ApplyHealthChange(float ChangeValue)
{
	Health += ChangeValue;
	
	Health = FMath::Clamp(Health,0,MaxHealth);
	
	OnHealthChange.Broadcast(nullptr,this,Health,ChangeValue);
	
	return true;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0;
}

bool USAttributeComponent::IsFullHealth()
{
	return Health == MaxHealth;
}

void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp,Warning,TEXT("HERE"));
	Health = MaxHealth;
}




