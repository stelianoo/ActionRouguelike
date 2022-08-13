// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

class UEnvQueryInstanceBlueprintWrapper;
/**
 * 
 */
UCLASS()
class ACTIONROUGUELIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	FTimerHandle TimeHandler_SpawnBots;
	UPROPERTY(EditDefaultsOnly,Category = AI)
	float SpawnTimerInterval;

	UPROPERTY(EditDefaultsOnly,Category = AI)
	UEnvQuery *SpawnBotsQuery;

	UPROPERTY(EditDefaultsOnly,Category = AI)
	TSubclassOf<AActor> MinionClass;

	UPROPERTY(EditDefaultsOnly,Category = AI)
	UCurveFloat *DifficultyCurve;
	
private:
	ASGameModeBase();
	
public:
	UFUNCTION(BlueprintCallable)
	void RespawnPlayerElapsed(AController* PlayerController);
	
	UFUNCTION(BlueprintCallable)
	virtual void OnActorKilled(AActor* Killed,AActor *Killer); 
	
	UFUNCTION(BlueprintCallable)
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* EnvQueryInstanceBlueprintWrapper, EEnvQueryStatus::Type Arg);
	UFUNCTION()
	void SpawnBotsElapse();
	virtual void StartPlay() override;

	UFUNCTION(Exec)
	void KillAllAI();
	
};
