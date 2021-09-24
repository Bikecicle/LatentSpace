// Copyright 2021 Griffin Page

#pragma once

#include "CoreMinimal.h"
#include "BaseShape.h"

/**
 * 
 */
class LATENTSPACE_API FBaseSphere : public IBaseShape
{
private:
	float Radius;
	FVector Center, Color;
public:
	FBaseSphere(float Radius, FVector Center, FVector Color);
	float GetSignedDistance(FVector4 Position);
};
