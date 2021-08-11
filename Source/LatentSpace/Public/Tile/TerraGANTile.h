// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utils/NoiseManager.h"

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
	bool bIsGenerated = False;

	FString GenerateQuery();
	float GetValueAt(FTileCoord TileCoord, unsigned int Seed, UMachineLearningRemoteComponent* MachineLearningRemoteComponent);
};
