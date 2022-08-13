// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

class USAttributeComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChange,AActor*,InstigatorActor,USAttributeComponent*,OwningComp,float,Health,float,Change);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROUGUELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintCallable,Category = Attributes)
	static USAttributeComponent* GetAttributes(AActor* FromActor);

	UFUNCTION(BlueprintCallable,Category = Attributes)
	static bool IsActorAlive(AActor* Actor);

	UFUNCTION(BlueprintCallable,Category = Attributes)
	static void ResetHealth(AActor* Actor);
	
	USAttributeComponent();

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Attributes")
	float MaxHealth=100 ;
	
protected:
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Attributes")
	float Health;

public:

	UFUNCTION(BlueprintCallable) 
	bool Kill(AActor* Insigator);
	
	UPROPERTY(BlueprintAssignable,Category=Events)
	FOnHealthChange OnHealthChange;
	
	UFUNCTION(BlueprintCallable,Category="Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor,float ChangeValue);

	UFUNCTION(BlueprintCallable) 
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable) 
	bool IsFullHealth();

	UFUNCTION(BlueprintCallable)
	float HealthPercent();

protected:
	virtual void BeginPlay() override;
	
};
