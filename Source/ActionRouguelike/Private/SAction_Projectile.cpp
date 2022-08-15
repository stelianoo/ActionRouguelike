// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction_Projectile.h"

#include "SCharacter.h"
#include "Kismet/GameplayStatics.h"

USAction_Projectile::USAction_Projectile()
{
	HandSocketName = "Muzzle_01";
	ProjectDelay = 0.2f;
}



void USAction_Projectile::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ASCharacter* Character = Cast<ASCharacter>(Instigator);
	if (Character)
	{
		Character->PlayAnimMontage(CastAnimMontage);
		
		UGameplayStatics::SpawnEmitterAttached(CastEffect,
			Character->GetMesh(),HandSocketName);

		
		FTimerDelegate CastAction;
		CastAction.BindUFunction(this,"ProjectileCast_Elapsed",Character);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_Cast,CastAction,0.2f,false);

		
	}
}

void USAction_Projectile::ProjectileCast_Elapsed(ASCharacter* InstigatorCharacter)
{
	if (ensureAlways(ProjectClass))
	{
		FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);

		FActorSpawnParameters SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParam.Instigator = InstigatorCharacter;

		FCollisionShape CollisionShape;
		CollisionShape.SetSphere(15.0f);

		FCollisionQueryParams CollisionParam;
		CollisionParam.AddIgnoredActor(InstigatorCharacter);
		
		FCollisionObjectQueryParams ObjQueryParam;
		ObjQueryParam.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjQueryParam.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjQueryParam.AddObjectTypesToQuery(ECC_Pawn);

		FVector TraceStart = InstigatorCharacter->GetPawnViewLocation();

		FVector TraceEnd =TraceStart + InstigatorCharacter->GetControlRotation().Vector()*50000;
	
		
		FHitResult HitResult;
		if (GetWorld()->SweepSingleByObjectType(HitResult,TraceStart,TraceEnd,
			FQuat::Identity,ObjQueryParam,CollisionShape,CollisionParam))
		{
			TraceEnd = HitResult.ImpactPoint;
		}
		
		// DrawDebugLine(GetWorld(),CameraTransform.GetLocation(),CameraTraceEndPoint,
		// 	FColor::Blue,false,5,100,2);

		DrawDebugSphere(GetWorld(),TraceEnd,10,10,FColor::Black,
			false,5,10,2);

		FRotator RotationToTarget = (TraceEnd - HandLocation).Rotation();

		FTransform SpawnTransform = FTransform(RotationToTarget,HandLocation);
		GetWorld()->SpawnActor<AActor>(ProjectClass,SpawnTransform,SpawnParam);
	}
	StopAction(InstigatorCharacter);
}
