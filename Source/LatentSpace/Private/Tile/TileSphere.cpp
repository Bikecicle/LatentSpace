// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile/TileSphere.h"
#include "Tile/TerraGANTile.h"
#include "Utils/NoiseManager.h"
#include "FastNoise/VoxelFastNoise.inl"


FTileSphere::FTileSphere(FVector pCenter, float pRadius, float pElevationAmplitude, unsigned int pSeed)
    : Center(pCenter)
    , Radius(pRadius)
    , ElevationAmplitude(pElevationAmplitude)
    , Seed(pSeed)
{ 
}

void FTileSphere::Init(UMachineLearningRemoteComponent* MachineLearningRemoteComponent)
{
    for (int i = 0; i < SideCount; i++)
    {
        for (int j = 0; j < FaceResolution; j++)
        {
            for (int k = 0; k < FaceResolution; k++)
            {
                Tiles[i][j][k] = new FTerraGANTile(MachineLearningRemoteComponent);
            }
        }
    }
    UE_LOG(LogTemp, Log, TEXT("Initialization complete"));
}

FTileCoord FTileSphere::GetTileCoords(FVector Position) const
{
    FVector SpherePosition = Position.GetSafeNormal();
    FTileCoord TileCoord;

    TileCoord.FaceResolution = FaceResolution;
    TileCoord.TileResolution = FTerraGANTile::TileResolution;

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

    FaceXScale = (FaceXScale + 1.0) / 2.0;
    FaceYScale = (FaceYScale + 1.0) / 2.0;

    TileCoord.FaceX = (int) FMath::RoundToZero(FaceXScale * TileCoord.FaceResolution);
    TileCoord.FaceY = (int) FMath::RoundToZero(FaceYScale * TileCoord.FaceResolution);

    TileCoord.TileX = (int) FMath::RoundToZero((FaceXScale * TileCoord.FaceResolution - TileCoord.FaceX) * TileCoord.TileResolution);
    TileCoord.TileY = (int) FMath::RoundToZero((FaceYScale * TileCoord.FaceResolution - TileCoord.FaceY) * TileCoord.TileResolution);

    TileCoord.Rotation = 0;

    return TileCoord;
}

float FTileSphere::GetValueAt(FTileCoord TileCoord) const
{
    FTerraGANTile* Tile = Tiles[TileCoord.Face][TileCoord.FaceX][TileCoord.FaceY];
    return Tile->GetValueAt(TileCoord, Seed);
}


float FTileSphere::GetSignedDistance(FVector4 Position) const
{
    FVector Position3D = FVector(Position);
    Position3D -= Center;
    float Distance = Position3D.Size() - Radius;

    FTileCoord TileCoord = GetTileCoords(Position3D);
    Distance -= GetValueAt(TileCoord) * ElevationAmplitude;

    return Distance;
}

FColor FTileSphere::ColorCode(FVector4 Position) const
{
	FVector Position3D = FVector(Position);
    Position3D -= Center;
    
    FTileCoord TileCoord = GetTileCoords(Position3D);
    FLinearColor Color = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //Color.R = (float) TileCoord.TileX / TileCoord.TileResolution;
    //Color.B = (float) TileCoord.TileY / TileCoord.TileResolution;

    float Offset = GetValueAt(TileCoord);
    Offset -= 0.125f;
    Offset *= 10.0f;

    if (Offset < 0)
    {
        Color.R = 1.0;
        Color.G = 1.0 + Offset;
    } else {
        Color.R = 1.0 - Offset;
        Color.G = 1.0;
    }
    

    return Color.ToFColor(false);
}