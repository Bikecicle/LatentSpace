// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile/TileCoord.h"
#include "Tile/TerraGANTile.h"
#include "FastNoise/VoxelFastNoise.h"
#include "MachineLearningRemoteComponent.h"

/**
 * 
 */
class LATENTSPACE_API FTileSphere
{
private:
	FVector Center;
	float Radius;
	int Resolution;

	FTerraGANTile* Sides;
	FTerraGANTile* Edges;

	UMachineLearningRemoteComponent* MachineLearningRemoteComponent;

public:
	FTileSphere(FVector Center, float Radius, int Resolution);

	void Initiallize();

	FTileCoord GetTileCoords(FVector Position) const;
	float GetValue(FTileCoord Coordinate) const;
	float GetSignedDistance(FVector4 Position) const;
	FColor ColorCode(FVector4 Position) const;
};
