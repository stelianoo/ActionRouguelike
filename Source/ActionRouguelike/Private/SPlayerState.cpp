// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

#include "Kismet/GameplayStatics.h"


float ASPlayerState::GetCredits()
{
	return Credits;
}

bool ASPlayerState::CreditsAdd(int AddAmount)
{
	if (AddAmount <0)
	{
		UE_LOG(LogTemp,Warning,TEXT("Added negative value to credits."))
		return false;
	}
	Credits+=AddAmount;
	CreditsUpdate.Broadcast(Credits);
	return true;
}

bool ASPlayerState::CreditsSubtract(int SubtractAmount)
{
	if (SubtractAmount <0)
	{
		UE_LOG(LogTemp,Warning,TEXT("Subracted positive value value to credits."))
		return false;
	}
	Credits-=SubtractAmount;
	CreditsUpdate.Broadcast(Credits);
	return true;
}
