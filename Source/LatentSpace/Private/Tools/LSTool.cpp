// Copyright 2021 Griffin Page


#include "Tools/LSTool.h"

ALSTool::ALSTool(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Mesh1P = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh1P"));
	Mesh1P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	Mesh1P->bReceivesDecals = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh1P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh1P->SetCollisionResponseToAllChannels(ECR_Ignore);
	RootComponent = Mesh1P;

	bIsEquipped = false;
	bWantsToUse = false;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
}

//////////////////////////////////////////////////////////////////////////
// Inventory

//////////////////////////////////////////////////////////////////////////
// Input

//////////////////////////////////////////////////////////////////////////
// Tool usage

//////////////////////////////////////////////////////////////////////////
// Tool usage helpers

void ALSTool::SetOwningPawn(ALSFirstPersonCharacter* NewOwner)
{
	if (MyPawn != NewOwner)
	{
		SetInstigator(NewOwner);
		MyPawn = NewOwner;
		// net owner for RPC calls
		SetOwner(NewOwner);
	}	
}

//////////////////////////////////////////////////////////////////////////
// Reading data

USkeletalMeshComponent* ALSTool::GetToolMesh() const
{
	return Mesh1P;
}

class ALSFirstPersonCharacter* ALSTool::GetPawnOwner() const
{
	return MyPawn;
}