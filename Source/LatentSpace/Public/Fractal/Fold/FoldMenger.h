// Copyright 2021 Griffin Page

#pragma once

#include "CoreMinimal.h"
#include "Fold.h"

/**
 * 
 */
class LATENTSPACE_API FFoldMenger : public IFold
{
public:
	FFoldMenger();
	void FoldPosition(FVector4 & Position, FVector Origin);
};
