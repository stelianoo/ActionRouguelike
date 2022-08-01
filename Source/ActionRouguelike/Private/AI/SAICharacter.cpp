// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"



// Sets default values
ASAICharacter::ASAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnsensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensor");
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnsensingComp->OnSeePawn.AddDynamic(this,&ASAICharacter::OnPawnSee);
}

void ASAICharacter::OnPawnSee(APawn* Pawn)
{
	AAIController *AiController = Cast<AAIController>(GetController());
	if (AiController)
	{
		UBlackboardComponent* BlackboardComponent = AiController->GetBlackboardComponent();

		BlackboardComponent->SetValueAsObject("TargetActor",Pawn);

		DrawDebugString(GetWorld(),GetActorLocation(),"Player Spotted",nullptr,
			FColor::White,3);
	}
}
