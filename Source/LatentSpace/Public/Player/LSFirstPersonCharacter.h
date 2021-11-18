// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VoxelComponents/VoxelInvokerComponent.h"
#include "Player/GravityMovementComponent.h"
#include "Tools/LSTool.h"
#include "LSFirstPersonCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class ALSFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ALSFirstPersonCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay();

	void Tick(float DeltaSeconds) override;

	void UpdateGravity(FVector NewGravityDirection);

	//////////////////////////////////////////////////////////////////////////
	// Inventory

	void EquipTool(class ALSTool* Tool);

	//////////////////////////////////////////////////////////////////////////
	// Tool usage

	/** Tool usage */
	void StartUseTool();

	/** Tool usage */
	void StopUseTool();

	//////////////////////////////////////////////////////////////////////////
	// Input handlers

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	void TurnAngle(float Val);

	void LookUpAngle(float Val);

	/** Player pressed use tool action */
	void OnStartUseTool();

	/** Player released use tool action */
	void OnStopUseTool();

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	//////////////////////////////////////////////////////////////////////////
	// Reading data

	/** Get casted movement componment */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character")
	UGravityMovementComponent* GetGravityMovementComponent();


protected:

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AFirstPersonExampleProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Current down direction in world space */
	FVector GravityDirection;

	/** Currently equipped tool */
	UPROPERTY(Transient)
	class ALSTool* EquippedTool;

	/** Current using state */
	uint8 bWantsToUseTool : 1;

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

