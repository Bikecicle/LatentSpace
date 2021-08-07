// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class LATENTSPACE_API FTileCoord
{
public:
	FTileCoord();
	
	enum EFace { Front, Back, Left, Right, Top, Bottom };

	EFace Face;
	double X;
	double Y;
};
