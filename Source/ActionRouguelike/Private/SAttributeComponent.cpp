// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

#include "SGameModeBase.h"


static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.DamageMultiplier"),
	1.0f,TEXT("Damage Multiplier"),ECVF_Cheat);


// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	
}

USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(StaticClass()));
	}
	return nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
	USAttributeComponent *ActorAttributes = GetAttributes(Actor);
	if (ActorAttributes)
	{
		return ActorAttributes->IsAlive();
	}
	return false;
}

void USAttributeComponent::ResetHealth(AActor* Actor)
{
	USAttributeComponent *ActorAttributes = GetAttributes(Actor);
	if (ActorAttributes)
	{
		ActorAttributes->Health = ActorAttributes->MaxHealth;
	}
}


bool USAttributeComponent::Kill(AActor* Insigator)
{
	return  ApplyHealthChange(Insigator,-MaxHealth);
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor,float ChangeValue)
{
	if (!GetOwner()->CanBeDamaged() && ChangeValue < 0)
	{
		return false;
	}

	if (ChangeValue <0)
	{
		ChangeValue *= CVarDamageMultiplier.GetValueOnGameThread();
	}
	
	const auto OldHealth =  Health;
	
	Health = FMath::Clamp(OldHealth+ChangeValue,0,MaxHealth);

	float ActualChangeVal = Health - OldHealth;
	OnHealthChange.Broadcast(InstigatorActor,this,Health,ActualChangeVal);

	//Died
	if (ActualChangeVal < 0.0f && Health == 0)
	{
		ASGameModeBase* GM = GetWorld()->GetAuthGameMode<ASGameModeBase>();
		if (GM)
		{
			GM->OnActorKilled(GetOwner(),InstigatorActor);
		}
	}
	
	return true;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0;
}

bool USAttributeComponent::IsFullHealth()
{
	return Health == MaxHealth;
}

float USAttributeComponent::HealthPercent()
{
	return Health/MaxHealth;
}

void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	
	Health = MaxHealth;

	UE_LOG(LogTemp,Warning,TEXT("Actor health set to %d"),Health);
}




