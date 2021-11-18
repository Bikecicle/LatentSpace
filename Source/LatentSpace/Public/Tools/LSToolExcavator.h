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

	ALSToolExcavator(const FObjectInitializer& ObjectInitializer);

	virtual void TickTool(bool bUse) override;

protected:
	
	UPROPERTY(Transient)
	class UVoxelSphereTool* VoxelSphereTool;

};
