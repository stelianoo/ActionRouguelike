// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickUpPoint.h"

#include "SCharacter.h"
#include "SPlayerState.h"
#include "Kismet/GameplayStatics.h"

void ASPickUpPoint::Interact_Implementation(APawn* InteractedPawn)
{
	ASCharacter* Character = Cast<ASCharacter>(InteractedPawn);
	if (Character)
	{
		ASPlayerState* PlayerState = Cast<ASPlayerState>(UGameplayStatics::GetPlayerState(this,0));

		if (PlayerState)
		{
			PlayerState->CreditsAdd(GivenCredits);

			TriggerInactivity();
			
		}
		
	}
}
