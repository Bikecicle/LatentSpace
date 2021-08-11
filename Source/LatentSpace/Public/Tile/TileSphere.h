// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile/TileCoord.h"
#include "Tile/TerraGANTile.h"
#include "MachineLearningRemoteComponent.h"


/** Represents a sphere where each point on the surface is mapped to a tile on a cube */
class LATENTSPACE_API FTileSphere
{
public:
	/** Width of a cube face in number of tiles */
	static const int FaceResolution = 4;
	/** Number of sides on a cube */
	static const int SideCount = 6;

private:
	/** Position of the center of the sphere */
	FVector Center;
	/** Radius of the sphere in voxels */
	float Radius;
	/** Seed to be passed to any contained noise generators */
	unsigned int Seed;
	/** Amount to overlap tiles when blending contents */
	int Overlap;

	FTerraGANTile* Tiles[SideCount][FaceResolution][FaceResolution];

	UMachineLearningRemoteComponent* MachineLearningRemoteComponent;

public:
	FTileSphere(FVector pCenter, float pRadius, unsigned int pSeed, float OverlapFactor);

	void Initiallize();

	FTileCoord GetTileCoords(FVector Position) const;
	float GetValueAt(FTileCoord TileCoord) const;
	float GetSignedDistance(FVector4 Position) const;
	FColor ColorCode(FVector4 Position) const;
};
