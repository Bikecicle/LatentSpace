// Fill out your copyright notice in the Description page of Project Settings.

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
