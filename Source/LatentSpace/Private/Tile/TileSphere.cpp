// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile/TileSphere.h"
#include "Tile/TerraGANTile.h"
#include "Utils/NoiseManager.h"
#include "FastNoise/VoxelFastNoise.inl"


FTileSphere::FTileSphere(FVector pCenter, float pRadius, unsigned int pSeed, float OverlapFactor)
{
	Center = pCenter;
	Radius = pRadius;
    Seed = pSeed;
    Overlap = (int) (OverlapFactor * FTerraGANTile::TileResolution);

    MachineLearningRemoteComponent = NewObject<UMachineLearningRemoteComponent>();
}

void FTileSphere::Initiallize()
{
}

FTileCoord FTileSphere::GetTileCoords(FVector Position) const
{
    FVector SpherePosition = Position.GetSafeNormal();
    FTileCoord TileCoord;

    double X, Y, Z;
    X = SpherePosition.X;
    Y = SpherePosition.Y;
    Z = SpherePosition.Z;

    double AbsX, AbsY, AbsZ;
    AbsX = fabsf(X);
    AbsY = fabsf(Y);
    AbsZ = fabsf(Z);

    double FaceXScale;
    double FaceYScale;

    const double InverseSqrt2 = 0.70710676908493042;

    // X-axis
    if (AbsX >= AbsY && AbsX >= AbsZ)
    {
        double A = Y * Y * 2.0;
        double B = Z * Z * 2.0;
        double Inner = -A + B - 3;
        double InnerSqrt = -sqrtf((Inner * Inner) - 12.0 * A);

        if (Y == 0.0 || Y == -0.0)
        {
            FaceXScale = 0.0;
        }
        else
        {
            FaceXScale = sqrtf(InnerSqrt + A - B + 3.0) * InverseSqrt2;
        }

        if (Z == 0.0 || Z == -0.0)
        {
            FaceYScale = 0.0;
        }
        else
        {
            FaceYScale = sqrtf(InnerSqrt - A + B + 3.0) * InverseSqrt2;
        }

        if (FaceXScale > 1.0) FaceXScale = 1.0;
        if (FaceYScale > 1.0) FaceYScale = 1.0;

        if (Z < 0) FaceYScale = -FaceYScale;

        if (X > 0)
        {
            TileCoord.Face = FTileCoord::EFace::Front;
            if (Y > 0) FaceXScale = -FaceXScale;
        }
        else
        {
            TileCoord.Face = FTileCoord::EFace::Back;
            if (Y < 0) FaceXScale = -FaceXScale;
        }
    }

    // Y-axis
    else if (AbsY >= AbsX && AbsY >= AbsZ)
    {
        double A = X * X * 2.0;
        double B = Z * Z * 2.0;
        double Inner = -A + B - 3;
        double InnerSqrt = -sqrtf((Inner * Inner) - 12.0 * A);



        if (X == 0.0 || X == -0.0)
        {
            FaceXScale = 0.0;
        }
        else
        {
            FaceXScale = sqrtf(InnerSqrt + A - B + 3.0) * InverseSqrt2;
        }

        if (Z == 0.0 || Z == -0.0)
        {
            FaceYScale = 0.0;
        }
        else
        {
            FaceYScale = sqrtf(InnerSqrt - A + B + 3.0) * InverseSqrt2;
        }

        if (FaceXScale > 1.0) FaceXScale = 1.0;
        if (FaceYScale > 1.0) FaceYScale = 1.0;

        if (Z < 0) FaceYScale = -FaceYScale;

        if (Y > 0)
        {
            TileCoord.Face = FTileCoord::EFace::Left;
            if (X < 0) FaceXScale = -FaceXScale;
        }
        else
        {
            TileCoord.Face = FTileCoord::EFace::Right;
            if (X > 0) FaceXScale = -FaceXScale;
        }
    }

    // Z-axis
    else {
        double A = Y * Y * 2.0;
        double B = X * X * 2.0;
        double Inner = -A + B - 3;
        double InnerSqrt = -sqrtf((Inner * Inner) - 12.0 * A);

        if (Y == 0.0 || Y == -0.0)
        {
            FaceXScale = 0.0;
        }
        else
        {
            FaceXScale = sqrtf(InnerSqrt + A - B + 3.0) * InverseSqrt2;
        }

        if (X == 0.0 || X == -0.0)
        {
            FaceYScale = 0.0;
        }
        else
        {
            FaceYScale = sqrtf(InnerSqrt - A + B + 3.0) * InverseSqrt2;
        }

        if (FaceXScale > 1.0) FaceXScale = 1.0;
        if (FaceYScale > 1.0) FaceYScale = 1.0;

        if (Y > 0) FaceXScale = -FaceXScale;

        if (Z > 0)
        {
            TileCoord.Face = FTileCoord::EFace::Top;
            if (X > 0) FaceYScale = -FaceYScale;
        }
        else
        {
            TileCoord.Face = FTileCoord::EFace::Bottom;
            if (X < 0) FaceYScale = -FaceYScale;
        }
    }

    TileCoord.FaceX = (int) FMath::RoundToZero(FaceXScale * FaceResolution);
    TileCoord.FaceY = (int) FMath::RoundToZero(FaceYScale * FaceResolution);

    TileCoord.TileX = (int) FMath::RoundToZero((TileCoord.FaceX * FaceResolution - FaceXScale) * FTerraGANTile::TileResolution);
    TileCoord.TileY = (int) FMath::RoundToZero((TileCoord.FaceY * FaceResolution - FaceYScale) * FTerraGANTile::TileResolution);

    return TileCoord;
}

float FTileSphere::GetValue(FTileCoord TileCoord) const
{
    
    //int TileMax = FaceResolution - 1;
    
    //TArray<float> Latents[3][3];
    //int TileIDs[3][3];

    //int Empty = -1;

    /*
    switch (TileCoord.Face)
    {
    case FTileCoord::EFace::Front:
        // Bottom edge
        if (TileY == 0)
        {
            // Bottom left corner
            if (TileX == 0)
            {
                TileIDs[0][0] = Empty;

                TileIDs[1][0] = NoiseManager::GetValueNoise3D(FTileCoord::EFace::Bottom, TileMin, TileMax, Seed) / 2;
                Latents[1][0] = NoiseManager::GetLatent(FTerraGANTile::LatentSize, TileIDs[1][0]);

                TileIDs[2][0] = NoiseManager::GetValueNoise3D(FTileCoord::EFace::Bottom, 1, TileMax, Seed) / 2;
                Latents[2][0] = NoiseManager::GetLatent(FTerraGANTile::LatentSize, TileIDs[2][0]);
            }
            // Bottom right corner
            else if (TileX == TileMax)
            {
                TileIDs[0][0] = NoiseManager::GetValueNoise3D(FTileCoord::EFace::Bottom, TileMax - 1, TileMax, Seed) / 2;
                Latents[0][0] = NoiseManager::GetLatent(FTerraGANTile::LatentSize, TileIDs[0][0]);

                TileIDs[1][0] = NoiseManager::GetValueNoise3D(FTileCoord::EFace::Bottom, TileMax, TileMax, Seed) / 2;
                Latents[1][0] = NoiseManager::GetLatent(FTerraGANTile::LatentSize, TileIDs[1][0]);

                TileIDs[2][0] = Empty;
            }
            // Rest of the bottom edge
            else
            {
                TileIDs[0][0] = NoiseManager::GetValueNoise3D(FTileCoord::EFace::Bottom, TileX, TileMax, Seed) / 2;
                Latents[0][0] = NoiseManager::GetLatent(FTerraGANTile::LatentSize, TileIDs[1][0]);
            }
        }
        break;
    
    case TileCoord::EFace::Back:
        break;

    case TileCoord::EFace::Left:
        break;

    case TileCoord::EFace::Right:
        break;

    case TileCoord::EFace::Top:
        break;

    case TileCoord::EFace::Bottom:
        break;

    default:
        break;
    }
    */

   return 0.0f;
}


float FTileSphere::GetSignedDistance(FVector4 Position) const
{
    FVector Position3D = FVector(Position);
    Position3D -= Center;
    float Distance = Position3D.Size() - Radius;

    FTileCoord TileCoord = GetTileCoords(Position3D);

    return Distance;
}

FColor FTileSphere::ColorCode(FVector4 Position) const
{
	FVector Position3D = FVector(Position);
    Position3D -= Center;
    Position3D = Position3D.GetSafeNormal();
    

    
    FLinearColor Color = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    FVoxelFastNoise FastNoise;
    FastNoise.SetSeed(2);
    float Offset = FastNoise.GetPerlin_3D(Position3D.X, Position3D.Y, Position3D.Z, 2.0f) / 2.0f;

    Color.R += Offset;
    Color.G += Offset;
    Color.B += Offset;
    

    return Color.ToFColor(false);
}