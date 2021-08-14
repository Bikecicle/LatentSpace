// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile/TileCoord.h"
#include "Utils/NoiseManager.h"
#include "MachineLearningRemoteComponent.h"

/**
 * 
 */
class LATENTSPACE_API FTerraGANTile
{
public:
	FTerraGANTile();

	static const int LatentSize = 128;
	static const int TileResolution = 256;

	float Terrain[TileResolution][TileResolution];
	bool bIsGenerated;

	float GetValueAt(FTileCoord TileCoord, int FaceResolution, unsigned int SphereSeed, UMachineLearningRemoteComponent* MLComponent);
};