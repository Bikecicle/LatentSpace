// Fill out your copyright notice in the Description page of Project Settings.

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
