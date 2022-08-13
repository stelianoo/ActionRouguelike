// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModeBase.h"

#include "EngineUtils.h"
#include "SAttributeComponent.h"
#include "SCharacter.h"
#include "SPlayerState.h"
#include "AI/SAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


static TAutoConsoleVariable<bool> CVarSpawnBool(TEXT("su.SpawnBots"),
                                                true,TEXT("Enable spawn of bots via timmer."),ECVF_Cheat);



ASGameModeBase::ASGameModeBase()
{
	SpawnTimerInterval = 2.0f;
}



void ASGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimeHandler_SpawnBots,this,&ASGameModeBase::SpawnBotsElapse,SpawnTimerInterval,true);
	
}

void ASGameModeBase::KillAllAI()
{
	for (TActorIterator<ASAICharacter> IT(GetWorld());IT;++IT)
	{
		ASAICharacter* Bot = *IT;
		USAttributeComponent* HealthAttrib = USAttributeComponent::GetAttributes(Bot);
		if (HealthAttrib && HealthAttrib->IsAlive())
		{
			HealthAttrib->Kill(this); // TODO : pass player for kill credtits?
		}
	}
}

void ASGameModeBase::SpawnBotsElapse()
{
	if (!CVarSpawnBool.GetValueOnGameThread())
	{
		UE_LOG(LogTemp,Warning,TEXT("GAME: Spawn disabled via log commands"))
		return;
	}

	int32 NrOfActorAlive = 0;
	for (TActorIterator<ASAICharacter> IT(GetWorld());IT;++IT)
	{
		ASAICharacter* Bot = *IT;
		USAttributeComponent* HealthAttrib = USAttributeComponent::GetAttributes(Bot);
		if (HealthAttrib && HealthAttrib->IsAlive())
		{
			NrOfActorAlive++;
		}
	}

	//UE_LOG(LogTemp,Warning,TEXT("Capacity : %d"),NrOfActorAlive);
	
	float MaxBotCount = 10;
	if (DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->GetTimeSeconds());
	}
	
	if (NrOfActorAlive >= MaxBotCount)
	{
		//UE_LOG(LogTemp,Warning,TEXT("Max Capacity"));
		return;
	}
	
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this,
		SpawnBotsQuery,this,EEnvQueryRunMode::RandomBest5Pct,nullptr);
	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this,&ASGameModeBase::OnQueryCompleted);	
	}
	
}

void ASGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* EnvQueryInstanceBlueprintWrapper,
	EEnvQueryStatus::Type Arg)
{
	if (Arg != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp,Warning,TEXT("Query fail."))
		return;
	}

	
	
	TArray<FVector> Locations = EnvQueryInstanceBlueprintWrapper->GetResultsAsLocations();
	if (Locations.Num() >0)
	{
		FActorSpawnParameters SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AActor>(MinionClass,Locations[0]+FVector(0,0,50),FRotator::ZeroRotator,SpawnParam);
	}
}


void ASGameModeBase::OnActorKilled(AActor* Killed, AActor* Killer)
{
	//Player killed
	ASCharacter *PlayerChar = Cast<ASCharacter>(Killed);
	if (PlayerChar)
	{
		FTimerHandle TimerHandle;

		FTimerDelegate SpawnPlayer  = FTimerDelegate::CreateUObject(this,
				&ASGameModeBase::RespawnPlayerElapsed, PlayerChar->GetController());
		
		GetWorldTimerManager().SetTimer(TimerHandle,SpawnPlayer,2,false);
		return;
	}
	//Ai Killed
	ASAICharacter *AiChar = Cast<ASAICharacter>(Killed);
	if (AiChar)
	{
		ASPlayerState* PlayerState = Cast<ASPlayerState>(UGameplayStatics::GetPlayerState(this,0));
		if (PlayerState)
		{
			PlayerState->CreditsAdd(1);
			return;
		}
	}
}

void ASGameModeBase::RespawnPlayerElapsed(AController* PlayerController)
{
	if (ensure(PlayerController))
	{
		PlayerController->UnPossess();
		
		RestartPlayer(PlayerController);
	}
}

