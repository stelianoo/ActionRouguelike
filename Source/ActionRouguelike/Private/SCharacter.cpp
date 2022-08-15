// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"


#include "SActionComponent.h"
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
	ActionComponent = CreateDefaultSubobject<USActionComponent>("ActionComp");
}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComponent->OnHealthChange.AddDynamic(this, &ASCharacter::OnHealthChange);
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,&ASCharacter::BeginOverlap);
}

void ASCharacter::HealSelf(float HealAmount /* = 100 */)
{
	AttributeComponent->ApplyHealthChange(this,HealAmount);
}

FVector ASCharacter::GetPawnViewLocation() const
{
	return CameraComponent->GetComponentLocation();
}


void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
}

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
	ActionComponent->StartActionByName(this,"PrimaryAttack");
}

void ASCharacter::AbilityOne()
{
	ActionComponent->StartActionByName(this,"BlackHole");
}

void ASCharacter::AbilityTwo()
{
	ActionComponent->StartActionByName(this,"Dash");
}

void ASCharacter::SprintStart()
{
	ActionComponent->StartActionByName(this,"Sprint");
}

void ASCharacter::SprintStop()
{
	ActionComponent->StopActionByName(this,"Sprint");
}



void ASCharacter::Interact()
{
	InteractionComponent->PrimaryInteract();
}


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

	PlayerInputComponent->BindAction("Sprint",IE_Pressed,this,&ASCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint",IE_Released,this,&ASCharacter::SprintStop);
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

