// Fill out your copyright notice in the Description page of Project Settings.

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
