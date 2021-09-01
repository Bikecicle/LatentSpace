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
	FTerraGANTile(UMachineLearningRemoteComponent* pMachineLearningRemoteComponent);

	static const int LatentSize = 128;
	static const int TileResolution = 128;

	float Terrain[TileResolution][TileResolution];
	
	bool bIsGenerated;

	UMachineLearningRemoteComponent* MachineLearningRemoteComponent;

	void Generate(FTileCoord TileCoord, unsigned int SphereSeed);
	float GetValueAt(FTileCoord TileCoord, unsigned int SphereSeed);
};