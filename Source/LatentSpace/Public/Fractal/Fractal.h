// Copyright 2021 Griffin Page

#pragma once

#include "CoreMinimal.h"
#include "Fractal/Fold/Fold.h"
#include "Fractal/Base/BaseShape.h"
#include <vector>

/**
 * 
 */
class LATENTSPACE_API FFractal
{
private:
	TArray<IFold*> Folds;
	IBaseShape* BaseShape;
	
	float Scale;
	float DistanceOffset;
	int Iterations;

public:
	FFractal(float pScale, float pDistanceOffset, int pIterations);

	void AddFold(IFold* Fold);
	void SetBase(IBaseShape* Base);
	float GetSignedDistance(FVector Origin) const;
};
