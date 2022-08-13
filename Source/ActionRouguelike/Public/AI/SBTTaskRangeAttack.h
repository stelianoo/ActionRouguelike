// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SBTTaskRangeAttack.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGUELIKE_API USBTTaskRangeAttack : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
public:
	USBTTaskRangeAttack();
	
protected:

	UPROPERTY(EditAnywhere,Category="AI")
	float ShootingSpread;
	
	UPROPERTY(EditAnywhere,Category="AI")
	TSubclassOf<AActor> ProjectileClass;
};
