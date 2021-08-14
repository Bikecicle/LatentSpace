// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FastNoise/VoxelFastNoise.h"

/**
 * 
 */
class LATENTSPACE_API FNoiseManager
{
private:
	signed int RootSeed;

public:
	FNoiseManager();

	static const unsigned int BIT_NOISE1 = 0x68E31DA4;
	static const unsigned int BIT_NOISE2 = 0xB5297A4D;
	static const unsigned int BIT_NOISE3 = 0x1B56C4E9;
	static const int PRIME1 = 198491317;
	static const int PRIME2 = 6542989;
	static unsigned int Squirrel3(int Position, unsigned int Seed);
	static unsigned int GetValueNoise1D(int X, unsigned int Seed);
	static unsigned int GetValueNoise2D(int X, int Y, unsigned int Seed);
	static unsigned int GetValueNoise3D(int X, int Y, int Z, unsigned int Seed);

	static void GenerateLatent(float Latent[], int LatentSize, unsigned int Seed);
};
