// Copyright 2021 Griffin Page

#pragma once

#include "CoreMinimal.h"
#include "Fold.h"

/**
 * 
 */
class LATENTSPACE_API FFoldAbs : public IFold
{
private:
	FVector Center;
public:
	FFoldAbs(FVector Center);
	void FoldPosition(FVector4 & Position, FVector Origin);
};
