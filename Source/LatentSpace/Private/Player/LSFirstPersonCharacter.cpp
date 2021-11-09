// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/LSFirstPersonCharacter.h"
#include "Tools/LSToolExcavator.h"
#include "FirstPersonExampleProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ALSFirstPersonCharacter

ALSFirstPersonCharacter::ALSFirstPersonCharacter(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer.SetDefaultSubobjectClass<UGravityMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Disable Controller rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = false;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(false);			// otherwise won't be visible in the multiplayer
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	PrimaryActorTick.bCanEverTick = true;

	GravityDirection = FVector(0, 0, -1);
}

UGravityMovementComponent* ALSFirstPersonCharacter::GetGravityMovementComponent()
{
	return Cast<UGravityMovementComponent>(GetMovementComponent());
}

void ALSFirstPersonCharacter::UpdateGravity(FVector NewGravityDirection)
{
	GravityDirection = NewGravityDirection.GetSafeNormal();

	// Update movement component gravity
	GetGravityMovementComponent()->SetGravityDirection(GravityDirection);
}

void ALSFirstPersonCharacter::Tick(float DeltaSeconds)
{
	// Point gravity to origin for now
	UpdateGravity(-GetActorLocation());
}

void ALSFirstPersonCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	Mesh1P->SetHiddenInGame(false, true);
}

//////////////////////////////////////////////////////////////////////////
// Inventory

void ALSFirstPersonCharacter::EquipTool(ALSTool* Tool)
{
	if (Tool)
	{
		EquippedTool = Tool;

		Tool->SetOwningPawn(this);
	}
}

//////////////////////////////////////////////////////////////////////////
// Tool usage

void ALSFirstPersonCharacter::StartUseTool()
{
	if (!bWantsToUse)
	{
		bWantsToUse = true;
		if (EquippedTool)
		{
			EquippedTool->DoAction();
		}
	}
}

void ALSFirstPersonCharacter::StopUseTool()
{
	if (bWantsToUse)
	{
		bWantsToUse = false;
		if (EquippedTool)
		{
			EquippedTool->DoAction();
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ALSFirstPersonCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("UseTool", IE_Pressed, this, &ALSFirstPersonCharacter::OnStartUseTool);
	PlayerInputComponent->BindAction("UseTool", IE_Released, this, &ALSFirstPersonCharacter::OnStopUseTool);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ALSFirstPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALSFirstPersonCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &ALSFirstPersonCharacter::TurnAngle);
	PlayerInputComponent->BindAxis("TurnRate", this, &ALSFirstPersonCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &ALSFirstPersonCharacter::LookUpAngle);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ALSFirstPersonCharacter::LookUpAtRate);
}

void ALSFirstPersonCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ALSFirstPersonCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ALSFirstPersonCharacter::TurnAngle(float Value)
{
	if (Value != 0.0f)
	{
		// Update actor rotation
		AddActorLocalRotation(FRotator(0, Value, 0));
	}
}

void ALSFirstPersonCharacter::LookUpAngle(float Value)
{
	if (Value != 0.0f)
	{
		// Update camera orientation
		float NewPitch = FirstPersonCameraComponent->GetRelativeRotation().Pitch - Value;
		FirstPersonCameraComponent->SetRelativeRotation(FRotator(FMath::Clamp(NewPitch, -90.0f, 90.0f), 0, 0));
	}
}

void ALSFirstPersonCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	//AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ALSFirstPersonCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	//AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ALSFirstPersonCharacter::OnStartUseTool()
{
	StartUseTool();
}

void ALSFirstPersonCharacter::OnStopUseTool()
{
	StopUseTool();
}