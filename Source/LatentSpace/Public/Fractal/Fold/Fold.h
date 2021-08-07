// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class LATENTSPACE_API IFold
{
public:
	virtual void FoldPosition(FVector4 & Position, FVector Origin) = 0;
	//virtual void Unfold(FVector4 & p, FVector4 & q) = 0;
	//virtual FString Shader() = 0;
};
