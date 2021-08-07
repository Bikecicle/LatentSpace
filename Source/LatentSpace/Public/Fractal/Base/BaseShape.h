// Fill out your copyright notice in the Description page of Project Settings.

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
