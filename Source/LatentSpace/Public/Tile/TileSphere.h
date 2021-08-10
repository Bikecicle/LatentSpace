// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile/TileCoord.h"
#include "Tile/TerraGANTile.h"
#include "MachineLearningRemoteComponent.h"


/**
 * 
 */
class LATENTSPACE_API FTileSphere
{
public:
	static const int FaceResolution = 4;
	static const int SideCount = 6;

private:
	FVector Center;
	float Radius;
	unsigned int Seed;
	int Overlap;

	FTerraGANTile* Sides[SideCount][FaceResolution][FaceResolution];

	UMachineLearningRemoteComponent* MachineLearningRemoteComponent;

public:
	FTileSphere(FVector pCenter, float pRadius, unsigned int pSeed, float OverlapFactor);

	void Initiallize();

	FTileCoord GetTileCoords(FVector Position) const;
	float GetValue(FTileCoord TileCoord) const;
	float GetSignedDistance(FVector4 Position) const;
	FColor ColorCode(FVector4 Position) const;
};
