// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fold.h"

/**
 * 
 */
class LATENTSPACE_API FFoldScaleTranslate : public IFold
{
private:
	float Scale;
	FVector Translation;
public:
	FFoldScaleTranslate(float Scale, FVector Translation);
	void FoldPosition(FVector4 & Position, FVector Origin);
};
