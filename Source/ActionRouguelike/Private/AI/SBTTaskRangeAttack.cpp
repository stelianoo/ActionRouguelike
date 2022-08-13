// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTaskRangeAttack.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"


USBTTaskRangeAttack::USBTTaskRangeAttack()
{
	ShootingSpread=2.0f;
}



EBTNodeResult::Type USBTTaskRangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	
	AAIController* AiController = OwnerComp.GetAIOwner();
	if (ensure(AiController))
	{
		ACharacter* MyPawn = Cast<ACharacter>(AiController->GetPawn());
		if (MyPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		FVector  MuzzleLocation = MyPawn->GetMesh()->GetSocketLocation("Muzzle_Front") ;

		AActor *TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (TargetActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		if (!USAttributeComponent::IsActorAlive(TargetActor))
		{
			return EBTNodeResult::Failed;
		}

		FVector Direction = TargetActor->GetActorLocation()-MuzzleLocation;
		FRotator MuzzleRotation = Direction.Rotation();

		MuzzleRotation.Pitch += FMath::RandRange(-ShootingSpread,ShootingSpread);
		MuzzleRotation.Yaw += FMath::RandRange(-ShootingSpread,ShootingSpread);

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.Instigator = MyPawn;
		
		AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass,MuzzleLocation,MuzzleRotation,SpawnParameters);

		return Projectile? EBTNodeResult::Succeeded : EBTNodeResult::Failed; 
		
	}
	return EBTNodeResult::Failed;
}

