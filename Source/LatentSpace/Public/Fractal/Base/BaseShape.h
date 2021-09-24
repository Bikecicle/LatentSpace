// Copyright 2021 Griffin Page

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class LATENTSPACE_API IBaseShape
{
public:
	virtual float GetSignedDistance(FVector4 Position) = 0;
};
