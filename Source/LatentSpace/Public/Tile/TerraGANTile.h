// Copyright 2021 Griffin Page

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
private:
	bool bIsGenerated;

public:
	FTerraGANTile(UMachineLearningRemoteComponent* TileMachineLearningRemoteComponent);

	static const int LatentSize = 128;
	static const int TileResolution = 128;

	float Terrain[TileResolution][TileResolution];

	UMachineLearningRemoteComponent* MachineLearningRemoteComponent;

	void Generate(FTileCoord TileCoord, unsigned int SphereSeed);
	float GetValueAt(FTileCoord TileCoord, unsigned int SphereSeed);
};