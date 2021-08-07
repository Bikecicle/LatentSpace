// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fold.h"

/**
 * 
 */
class LATENTSPACE_API FFoldBox : public IFold
{
private:
	FVector Radius;
public:
	FFoldBox(FVector Radius);
	void FoldPosition(FVector4 & Position, FVector Origin);
};
