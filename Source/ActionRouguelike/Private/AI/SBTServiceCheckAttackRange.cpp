// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTServiceCheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTServiceCheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	
	UBlackboardComponent *BlackboardComponent = OwnerComp.GetBlackboardComponent();

	if (ensure(BlackboardComponent))
	{
		AActor *TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor"));
		if (TargetActor)
		{
			AAIController* AiController = OwnerComp.GetAIOwner();
			if (ensure(AiController))
			{
				APawn *AiPawn = AiController->GetPawn();
				if (ensure(AiPawn))
				{
					float Distance = FVector::Distance(TargetActor->GetActorLocation(),AiPawn->GetActorLocation());

					bool bWithInRange = Distance < 2000.0f;
					
					bool bLineOfSight = false;
					if (bWithInRange)
					{
						bLineOfSight = AiController->LineOfSightTo(TargetActor);
					}
					
					BlackboardComponent->SetValueAsBool(AttackRangeKey.SelectedKeyName,(bWithInRange && bLineOfSight));
				}
			}
		}
	}
	
}
