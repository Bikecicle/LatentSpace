// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseShape.h"

/**
 * 
 */
class LATENTSPACE_API FBaseSphere : public IBaseShape
{
private:
	float Radius;
	FVector Center, Color;
public:
	FBaseSphere(float Radius, FVector Center, FVector Color);
	float GetSignedDistance(FVector4 Position);
};
