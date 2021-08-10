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
	int FaceX;
	int FaceY;
	int TileX;
	int TileY;

	static int GetRotation(EFace Face1, EFace Face2);
	FTileCoord Step();
};
