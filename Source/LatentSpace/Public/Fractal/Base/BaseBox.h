// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseShape.h"

/**
 * 
 */
class LATENTSPACE_API FBaseBox : public IBaseShape
{
private:
	FVector Shape, Center, Color;
public:
	FBaseBox(FVector Shape, FVector Center, FVector Color);
	float GetSignedDistance(FVector4 Position);
};
