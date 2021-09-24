// Copyright 2021 Griffin Page

#pragma once

#include "CoreMinimal.h"
#include "BaseShape.h"

/**
 * 
 */
class LATENTSPACE_API FBaseBox : public IBaseShape
{
private:
	FVector Shape, Center, Color;
public:
	FBaseBox(FVector Shape, FVector Center, FVector Color);
	float GetSignedDistance(FVector4 Position);
};
