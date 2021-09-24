// Copyright 2021 Griffin Page

#pragma once

#include "CoreMinimal.h"
#include "Fold.h"

/**
 * 
 */
class LATENTSPACE_API FFoldScaleOrigin : public IFold
{
private:
	float Scale;
public:
	FFoldScaleOrigin(float Scale);
	void FoldPosition(FVector4 & Position, FVector Origin);
};
