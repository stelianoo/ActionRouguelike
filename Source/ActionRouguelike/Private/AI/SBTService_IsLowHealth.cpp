// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_IsLowHealth.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"




void USBTService_IsLowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	
	if (ensure(BlackboardComp))
	{
		AAIController* AiController = OwnerComp.GetAIOwner();
		if (ensure(AiController))
		{
			
			USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(AiController->GetPawn());
			
			if (ensure(AttributeComp))
			{
				bool bIsLowHealth = AttributeComp->HealthPercent() < LowHealthThreshold;

				//UE_LOG(LogTemp,Warning,TEXT("Is low health? %f"),AttributeComp->HealthPercent());
			
				BlackboardComp->SetValueAsBool(LowHealthKey.SelectedKeyName,bIsLowHealth);
			}
		}
	}
	
	
	
}
