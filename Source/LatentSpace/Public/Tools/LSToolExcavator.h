// Copyright 2021 Griffin Page

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoxelTools/Tools/VoxelSphereTool.h"
#include "Tools/LSTool.h"
#include "LSToolExcavator.generated.h"

UCLASS()
class LATENTSPACE_API ALSToolExcavator : public ALSTool
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALSToolExcavator();

protected:
	
	UVoxelSphereTool* SphereTool;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void DoAction() override;

};
