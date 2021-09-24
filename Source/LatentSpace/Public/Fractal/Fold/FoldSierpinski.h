// Copyright 2021 Griffin Page

#pragma once

#include "CoreMinimal.h"
#include "Fold.h"

/**
 * 
 */
class LATENTSPACE_API FFoldSierpinski : public IFold
{
public:
	FFoldSierpinski();
	void FoldPosition(FVector4 & Position, FVector Origin);
};
