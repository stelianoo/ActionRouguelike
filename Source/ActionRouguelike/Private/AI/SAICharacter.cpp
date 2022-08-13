// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "SAttributeComponent.h"
#include "SWorldUserWidget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"



// Sets default values
ASAICharacter::ASAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensor");

	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");


	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
}



void ASAICharacter::OnHealthChange(AActor* ActorInstigator, USAttributeComponent* OwningComp, float NewHealth,
                                   float Change)
{
	if (ActorInstigator != this)
	{
		SetTargetActor(ActorInstigator);
	}

	if (ActiveHealthBar == nullptr)
	{
		ActiveHealthBar = CreateWidget<USWorldUserWidget>(GetWorld(),WorldHealthWidget);
		if (ActiveHealthBar)
		{
			ActiveHealthBar->AttachActor = this;
			ActiveHealthBar->AddToViewport();
		}
	}
	
	
	if (Change<0)
	{
		if (NewHealth <= 0)
		{
			// Kill controller
			AAIController* AIC = Cast<AAIController>(GetController());

			if (AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Killed");
			}

			// RagDoll
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();
			
			// Destroy object
			SetLifeSpan(10);
		}
		else
		{
			GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit",GetWorld()->TimeSeconds);
		}
	}
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this,&ASAICharacter::OnPawnSee);
	AttributeComponent->OnHealthChange.AddDynamic(this, &ASAICharacter::OnHealthChange);
}

void ASAICharacter::OnPawnSee(APawn* Pawn)
{
	SetTargetActor(Pawn);

	DrawDebugString(GetWorld(),GetActorLocation(),"Player Spotted",nullptr,FColor::White,3);
	
}

void ASAICharacter::SetTargetActor(AActor* NewActor)
{
	AAIController *AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor",NewActor);
	}
}