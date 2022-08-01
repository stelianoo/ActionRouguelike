// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"


#include "SAttributeComponent.h"
#include "SInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComponent->SetupAttachment(SpringArmComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	
	InteractionComponent = CreateDefaultSubobject<USInteractionComponent>("InteractComp");
	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComponent->OnHealthChange.AddDynamic(this, &ASCharacter::OnHealthChange);
	// GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,
	// 	InteractionComponent->OnOverlapBegin);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,&ASCharacter::BeginOverlap);
}


// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASCharacter::MoveForward(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	
	AddMovementInput(ControlRot.Vector(),value);
}

void ASCharacter::MoveRight(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(RightVector,value);
}

void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AnimationMontage);

	
	UGameplayStatics::SpawnEmitterAttached(ChargeParticle,GetMesh(),"Muzzle_01");
	
	const FTimerDelegate AttackAction  = FTimerDelegate::CreateUObject(this,
		&ASCharacter::PrimaryAttackTimeElapsed, PrimaryAttackProjectileClass);
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack,AttackAction,0.2f,false);
}

void ASCharacter::AbilityOne()
{
	PlayAnimMontage(AnimationMontage);

	
	
	const FTimerDelegate AttackAction  = FTimerDelegate::CreateUObject(this,
		&ASCharacter::PrimaryAttackTimeElapsed, AbilityOneProjectileClass);
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack,AttackAction,0.2f,false);
	
}

void ASCharacter::AbilityTwo()
{
	PlayAnimMontage(AnimationMontage);

	const FTimerDelegate AttackAction  = FTimerDelegate::CreateUObject(this,
		&ASCharacter::PrimaryAttackTimeElapsed, AbilityTwoProjectileClass);
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack,AttackAction,0.2f,false);
	
}

void ASCharacter::PrimaryAttackTimeElapsed(TSubclassOf<AActor> SpawnProjectile)
{
	// Cast Effect
	// UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ChargeParticle,
	// 		GetMesh()->GetSocketLocation("Muzzle_01"));
	
	FVector StartProjectileLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	
	FTransform CameraTransform = CameraComponent->GetComponentTransform();

	FVector CameraTraceEndPoint =
		CameraTransform.GetLocation() + CameraTransform.GetRotation().GetForwardVector()*50000;
	
	FCollisionObjectQueryParams ObjQueryParam;
	ObjQueryParam.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjQueryParam.AddObjectTypesToQuery(ECC_WorldDynamic);
	FHitResult HitResult;
	bool hit =	GetWorld()->LineTraceSingleByObjectType(
		HitResult,CameraTransform.GetLocation(),CameraTraceEndPoint,ObjQueryParam);

	// DrawDebugLine(GetWorld(),CameraTransform.GetLocation(),CameraTraceEndPoint,
	// 	FColor::Blue,false,5,100,2);

	FVector EndProjectileLocation =	hit? HitResult.ImpactPoint:CameraTraceEndPoint;

	DrawDebugSphere(GetWorld(),EndProjectileLocation,10,10,FColor::Black,
		false,5,10,2);

	FRotator RotationToTarget = (EndProjectileLocation - StartProjectileLocation).Rotation();

	FTransform SpawnTransform = FTransform(RotationToTarget,StartProjectileLocation);

	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParam.Instigator = this;
	
	GetWorld()->SpawnActor<AActor>(SpawnProjectile,SpawnTransform,SpawnParam);
}



void ASCharacter::Interact()
{

	InteractionComponent->PrimaryInteract();
	
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LockRight",this,&APawn::AddControllerYawInput);
	
	PlayerInputComponent->BindAxis("LockUp",this,&APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack",IE_Pressed,this,&ASCharacter::PrimaryAttack);

	PlayerInputComponent->BindAction("AbilityOne",IE_Pressed,this,&ASCharacter::AbilityOne);

	PlayerInputComponent->BindAction("AbilityTwo",IE_Pressed,this,&ASCharacter::AbilityTwo);
	
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ASCharacter::Jump);

	PlayerInputComponent->BindAction("Interact",IE_Pressed,this,&ASCharacter::Interact);
	
}

void ASCharacter::OnHealthChange(AActor* ActorInstigator, USAttributeComponent* OwningComp, float NewHealth, float Change)
{
	if (Change<0)
	{
		GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit",GetWorld()->TimeSeconds);
		GetMesh()->SetScalarParameterValueOnMaterials("HitSpeed",3);
		GetMesh()->SetVectorParameterValueOnMaterials("HitColor",FVector(1,0,0));
	}
	
	if (NewHealth<=0 && Change <= 0)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}

inline void ASCharacter::BeginOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
	UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult)
{
	InteractionComponent->OnInteractBeginOverlap(Actor);
}

