// Fill out your copyright notice in the Description page of Project Settings.


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

TArray<float> FNoiseManager::GetLatent(int LatentSize, unsigned int Seed)
{
    TArray<float> Latent;
    for (int Position = 0; Position < LatentSize; Position++)
    {
        float Component = (float) GetValueNoise1D(Position, Seed) / UINT_MAX * 2.0f - 1.0f;
        Latent.Add(Component);
    }
    return Latent;
}