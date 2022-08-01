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
	// Sets default values for this component's properties
	USAttributeComponent();

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Attributes")
	float MaxHealth=100 ;
	
protected:
	
	UPROPERTY(BlueprintReadOnly,VisibleDefaultsOnly,Category="Attributes")
	float Health;

public:

	UPROPERTY(BlueprintAssignable,Category=Events)
	FOnHealthChange OnHealthChange;
	
	UFUNCTION(BlueprintCallable,Category="Attributes")
	bool ApplyHealthChange(float ChangeValue);

	UFUNCTION(BlueprintCallable) 
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable) 
	bool IsFullHealth();

protected:
	virtual void BeginPlay() override;
	
};
