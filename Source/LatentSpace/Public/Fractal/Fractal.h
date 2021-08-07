// Fill out your copyright notice in the Description page of Project Settings.

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
	std::vector<IFold*> Folds;
	IBaseShape* BaseShape;
public:
	FFractal();

	void AddFold(IFold* Fold);
	void SetBase(IBaseShape* Base);
	float GetSignedDistance(FVector Origin, int Iterations) const;
};
