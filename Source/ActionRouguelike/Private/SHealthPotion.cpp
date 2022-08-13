// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "SAttributeComponent.h"
#include "SCharacter.h"


ASHealthPotion::ASHealthPotion()
{
 	
}



void ASHealthPotion::Interact_Implementation(APawn* InteractedPawn)
{

	ASCharacter* Character = Cast<ASCharacter>(InteractedPawn);
	if (Character)
	{
		USAttributeComponent* Atribute = USAttributeComponent::GetAttributes(InteractedPawn);
	
		if (Atribute && !Atribute->IsFullHealth())
		{
			if(CheckInteractCost(InteractedPawn,true,1))
			{
				Atribute->ApplyHealthChange(this,HealthPoints);

				TriggerInactivity();
			}
		}
	}
		
}



