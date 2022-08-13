// Fill out your copyright notice in the Description page of Project Settings.


#include "SBTTask_Healing.h"

#include "AIController.h"
#include "SAttributeComponent.h"

EBTNodeResult::Type USBTTask_Healing::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AiController = OwnerComp.GetAIOwner();
	
	if (ensure(AiController))
	{
		
		USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(AiController->GetPawn());
		if (AttributeComp)
		{
			USAttributeComponent::ResetHealth(AiController->GetPawn());

			UE_LOG(LogTemp,Warning,TEXT("AI HEALED"));
			return EBTNodeResult::Succeeded;
		}
		
	}

	return EBTNodeResult::Failed;
}
