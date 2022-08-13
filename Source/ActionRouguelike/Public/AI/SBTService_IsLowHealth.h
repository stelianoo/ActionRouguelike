// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SBTService_IsLowHealth.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGUELIKE_API USBTService_IsLowHealth : public UBTService
{
	GENERATED_BODY()

	
protected:

	UPROPERTY(EditAnywhere,Category="AI")
	FBlackboardKeySelector LowHealthKey;
	
	UPROPERTY(EditAnywhere,Category="AI")
	float LowHealthThreshold = 0.3f;
	
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, float DeltaSeconds) override;
	
};
