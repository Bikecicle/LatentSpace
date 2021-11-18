// Copyright 2021 Griffin Page

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/LSFirstPersonCharacter.h"
#include "LSTool.generated.h"

UCLASS(Abstract)
class LATENTSPACE_API ALSTool : public AActor
{
	GENERATED_BODY()

public:	

	ALSTool(const FObjectInitializer& ObjectInitializer);

	//////////////////////////////////////////////////////////////////////////
	// Inventory

	/** check if it's currently equipped */
	bool IsEquipped() const;

	/** check if mesh is already attached */
	bool IsAttachedToPawn() const;

	//////////////////////////////////////////////////////////////////////////
	// Input

	//////////////////////////////////////////////////////////////////////////
	// Tool usage

	/** [local] tool specific use implementation */
	virtual void TickTool(bool bUse) PURE_VIRTUAL(ALSTool::TickTool,);

	//////////////////////////////////////////////////////////////////////////
	// Reading data

	/** get tool mesh (needs pawn owner to determine variant) */
	USkeletalMeshComponent* GetToolMesh() const;

	/** get pawn owner */
	UFUNCTION(BlueprintCallable, Category="Game|Tool")
	class ALSFirstPersonCharacter* GetPawnOwner() const;

	/** set the tool's owning pawn */
	void SetOwningPawn(ALSFirstPersonCharacter* LSFirstPersonCharacter);

private:

	/** weapon mesh: 1st person view */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

protected:

	/** pawn owner */
	UPROPERTY(Transient)
	class ALSFirstPersonCharacter* MyPawn;

	/** is tool currently equipped? */
	bool bIsEquipped;

	/** is tool use active? */
	bool bWantsToUse;


	//////////////////////////////////////////////////////////////////////////
	// Inventory

	//////////////////////////////////////////////////////////////////////////
	// Weapon usage helpers

	/** Returns Mesh1P subobject **/
	FORCEINLINE USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
};
