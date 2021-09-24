// Copyright 2021 Griffin Page


#include "Utils/NoiseManager.h"


FNoiseManager::FNoiseManager()
{
}

unsigned int FNoiseManager::Squirrel3(int Position, unsigned int Seed)
{
    unsigned int MangledBits = (unsigned int) Position;
    MangledBits *= BIT_NOISE1;
    MangledBits += Seed;
    MangledBits ^= (MangledBits >> 8);
    MangledBits += BIT_NOISE2;
    MangledBits ^= (MangledBits << 8);
    MangledBits *= BIT_NOISE3;
    MangledBits ^= (MangledBits >> 8);
    return MangledBits;
}

unsigned int FNoiseManager::GetValueNoise1D(int X, unsigned int Seed)
{
    return Squirrel3(X, Seed);
}

unsigned int FNoiseManager::GetValueNoise2D(int X, int Y, unsigned int Seed)
{
    return Squirrel3(X + (Y * PRIME1), Seed);
}

unsigned int FNoiseManager::GetValueNoise3D(int X, int Y, int Z, unsigned int Seed)
{
    return Squirrel3(X + (Y * PRIME1) + (Z * PRIME2), Seed);
}

void FNoiseManager::GenerateLatent(float Latent[], int LatentSize, unsigned int Seed)
{
    for (int i = 0; i < LatentSize; i++)
    {
        Latent[i] = (float) GetValueNoise1D(i, Seed) / UINT_MAX * 2.0f - 1.0f;
    }
}