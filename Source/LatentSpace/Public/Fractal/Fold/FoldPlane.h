// Copyright 2021 Griffin Page

#pragma once

#include "CoreMinimal.h"
#include "Fold.h"

/**
 * 
 */
class LATENTSPACE_API FFoldPlane : public IFold
{
private:
	FVector Normal;
public:
	FFoldPlane(FVector Normal);
	void FoldPosition(FVector4 & Position, FVector Origin);
};
