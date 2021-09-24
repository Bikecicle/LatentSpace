// Copyright 2021 Griffin Page

#pragma once

#include "CoreMinimal.h"
#include "Fold.h"

/**
 * 
 */
class LATENTSPACE_API FFoldSphere : public IFold
{
private:
	float RMin, RMax;
public:
	FFoldSphere(float RMin, float RMax);
	void FoldPosition(FVector4 & Position, FVector Origin);
};
