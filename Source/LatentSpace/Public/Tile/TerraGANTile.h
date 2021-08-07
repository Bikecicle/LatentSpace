// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <string>

#define LATENT_SIZE 128
#define TILE_RES 256

/**
 * 
 */
class LATENTSPACE_API FTerraGANTile
{
private:
	float Latent[LATENT_SIZE];
	float Terrain[TILE_RES][TILE_RES];

public:
	FTerraGANTile();

	std::string GenerateQuery();
};
