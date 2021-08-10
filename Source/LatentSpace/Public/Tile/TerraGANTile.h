// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class LATENTSPACE_API FTerraGANTile
{
public:
	FTerraGANTile();

	static const int LatentSize = 128;
	static const int TileResolution = 256;

	float Latent[LatentSize];
	float Terrain[TileResolution][TileResolution];

	FString GenerateQuery();
};
