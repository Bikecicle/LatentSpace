// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile/TileSphere.h"
#include "Tile/TerraGANTile.h"
#include "Utils/NoiseManager.h"
#include "FastNoise/VoxelFastNoise.inl"


FTileSphere::FTileSphere(FVector SphereCenter, float SphereRadius, float SphereElevationAmplitude)
    : Center(SphereCenter)
    , Radius(SphereRadius)
    , ElevationAmplitude(SphereElevationAmplitude)
{ 
}

void FTileSphere::Init(UMachineLearningRemoteComponent* MachineLearningRemoteComponent, unsigned int SphereSeed)
{
    Seed = SphereSeed;
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

void FTileSphere::SetMaterialIndexPositions(TArray<float> SphereMaterialIndexPositions)
{
    MaterialIndexPositions = SphereMaterialIndexPositions;
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

    double FaceXFrac;
    double FaceYFrac;

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
            FaceXFrac = 0.0;
        }
        else
        {
            FaceXFrac = sqrtf(InnerSqrt + A - B + 3.0) * InverseSqrt2;
        }

        if (Z == 0.0 || Z == -0.0)
        {
            FaceYFrac = 0.0;
        }
        else
        {
            FaceYFrac = sqrtf(InnerSqrt - A + B + 3.0) * InverseSqrt2;
        }

        if (FaceXFrac > 1.0) FaceXFrac = 1.0;
        if (FaceYFrac > 1.0) FaceYFrac = 1.0;

        if (Z < 0) FaceYFrac = -FaceYFrac;

        if (X > 0)
        {
            TileCoord.Face = FTileCoord::EFace::Front;
            if (Y > 0) FaceXFrac = -FaceXFrac;
        }
        else
        {
            TileCoord.Face = FTileCoord::EFace::Back;
            if (Y < 0) FaceXFrac = -FaceXFrac;
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
            FaceXFrac = 0.0;
        }
        else
        {
            FaceXFrac = sqrtf(InnerSqrt + A - B + 3.0) * InverseSqrt2;
        }

        if (Z == 0.0 || Z == -0.0)
        {
            FaceYFrac = 0.0;
        }
        else
        {
            FaceYFrac = sqrtf(InnerSqrt - A + B + 3.0) * InverseSqrt2;
        }

        if (FaceXFrac > 1.0) FaceXFrac = 1.0;
        if (FaceYFrac > 1.0) FaceYFrac = 1.0;

        if (Z < 0) FaceYFrac = -FaceYFrac;

        if (Y > 0)
        {
            TileCoord.Face = FTileCoord::EFace::Left;
            if (X < 0) FaceXFrac = -FaceXFrac;
        }
        else
        {
            TileCoord.Face = FTileCoord::EFace::Right;
            if (X > 0) FaceXFrac = -FaceXFrac;
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
            FaceXFrac = 0.0;
        }
        else
        {
            FaceXFrac = sqrtf(InnerSqrt + A - B + 3.0) * InverseSqrt2;
        }

        if (X == 0.0 || X == -0.0)
        {
            FaceYFrac = 0.0;
        }
        else
        {
            FaceYFrac = sqrtf(InnerSqrt - A + B + 3.0) * InverseSqrt2;
        }

        if (FaceXFrac > 1.0) FaceXFrac = 1.0;
        if (FaceYFrac > 1.0) FaceYFrac = 1.0;

        if (Y > 0) FaceXFrac = -FaceXFrac;

        if (Z > 0)
        {
            TileCoord.Face = FTileCoord::EFace::Top;
            if (X > 0) FaceYFrac = -FaceYFrac;
        }
        else
        {
            TileCoord.Face = FTileCoord::EFace::Bottom;
            if (X < 0) FaceYFrac = -FaceYFrac;
        }
    }

    // Recenter between 0 and 1
    FaceXFrac = (FaceXFrac + 1.0) / 2.0 - 1e-8;
    FaceYFrac = (FaceYFrac + 1.0) / 2.0 - 1e-8;

    // Find tile location on face
    TileCoord.FaceX = (int) FMath::RoundToZero(FaceXFrac * TileCoord.FaceResolution);
    TileCoord.FaceY = (int) FMath::RoundToZero(FaceYFrac * TileCoord.FaceResolution);


    float TileXFrac = FaceXFrac * TileCoord.FaceResolution - TileCoord.FaceX;
    float TileYFrac = FaceYFrac * TileCoord.FaceResolution - TileCoord.FaceY;

    // Find pixel location on tile
    TileCoord.TileX = (int) FMath::RoundToZero(TileXFrac * TileCoord.TileResolution);
    TileCoord.TileY = (int) FMath::RoundToZero(TileYFrac * TileCoord.TileResolution);

    // Find offset from pixel for interpolation purposes
    TileCoord.PixelX = TileXFrac * TileCoord.TileResolution - TileCoord.TileX;
    TileCoord.PixelY = TileYFrac * TileCoord.TileResolution - TileCoord.TileY;

    TileCoord.Rotation = 0;

    return TileCoord;
}

float FTileSphere::GetValueAt(FTileCoord TileCoord) const
{
    // Pixel locations for bilerp
    // Q2 Q1
    // Q3 Q4
    FTileCoord Q1;
    FTileCoord Q2;
    FTileCoord Q3;
    FTileCoord Q4;

    float FracX;
    float FracY;

    // Right side
    if (TileCoord.PixelX >= 0.5f)
    {
        // Top
        if (TileCoord.PixelY >= 0.5f)
        {
            Q1 = TileCoord.PixelStep(1, 1);
            Q2 = TileCoord.PixelStep(0, 1);
            Q3 = TileCoord;
            Q4 = TileCoord.PixelStep(1, 0);
            
            FracY = TileCoord.PixelY - 0.5f;
        }
        // Bottom
        else
        {
            Q1 = TileCoord.PixelStep(1, 0);
            Q2 = TileCoord;
            Q3 = TileCoord.PixelStep(0, -1);
            Q4 = TileCoord.PixelStep(1, -1);

            FracY = TileCoord.PixelY + 0.5f;
        }

        FracX = TileCoord.PixelX - 0.5f;
    }
    // Left side
    else
    {
        // Top
        if (TileCoord.PixelY >= 0.5f)
        {
            Q1 = TileCoord.PixelStep(0, 1);
            Q2 = TileCoord.PixelStep(-1, 1);
            Q3 = TileCoord.PixelStep(-1, 0);
            Q4 = TileCoord;

            FracY = TileCoord.PixelY - 0.5f;
        }
        // Bottom
        else
        {
            Q1 = TileCoord;
            Q2 = TileCoord.PixelStep(-1, 0);
            Q3 = TileCoord.PixelStep(-1, -1);
            Q4 = TileCoord.PixelStep(0, -1);

            FracY = TileCoord.PixelY + 0.5f;
        }

        FracX = TileCoord.PixelX + 0.5f;
    }

    // Pixel values for bilerp
    float P00 = 0;
    float P10 = 0;
    float P01 = 0;
    float P11 = 0;

    // Fetch point values (if the tile exists)
    if (Q1.Face != FTileCoord::EFace::None)
    {
        P11 = Tiles[Q1.Face][Q1.FaceX][Q1.FaceY]->GetValueAt(Q1, Seed);
    }
    if (Q2.Face != FTileCoord::EFace::None)
    {
        P01 = Tiles[Q2.Face][Q2.FaceX][Q2.FaceY]->GetValueAt(Q2, Seed);
    }
    if (Q3.Face != FTileCoord::EFace::None)
    {
        P00 = Tiles[Q3.Face][Q3.FaceX][Q3.FaceY]->GetValueAt(Q3, Seed);
    }
    if (Q4.Face != FTileCoord::EFace::None)
    {
        P10 = Tiles[Q4.Face][Q4.FaceX][Q4.FaceY]->GetValueAt(Q4, Seed);
    }

    // Handle cube corners by substituting missing pixel with average of the other three
    if (Q1.Face == FTileCoord::EFace::None)
    {
        P11 = (P00 + P10 + P01) / 3.0f;
    }
    if (Q2.Face == FTileCoord::EFace::None)
    {
        P01 = (P00 + P10 + P11) / 3.0f;
    }
    if (Q3.Face == FTileCoord::EFace::None)
    {
        P00 = (P10 + P01 + P11) / 3.0f;
    }
    if (Q4.Face == FTileCoord::EFace::None)
    {
        P10 = (P00 + P01 + P11) / 3.0f;
    }

    float Value = FMath::BiLerp<float, float>(P00, P10, P01, P11, FracX, FracY);
    //float Value = Tiles[TileCoord.Face][TileCoord.FaceX][TileCoord.FaceY]->GetValueAt(TileCoord, Seed);

    return Value;
}


float FTileSphere::GetSignedDistance(FVector Position) const
{
    Position -= Center;
    float Distance = Position.Size() - Radius;

    FTileCoord TileCoord = GetTileCoords(Position);
    Distance -= GetValueAt(TileCoord) * ElevationAmplitude;

    return Distance;
}

TArray<float> FTileSphere::GetMaterialIndexValues(FVector Position) const
{
    Position -= Center;
    FTileCoord TileCoord = GetTileCoords(Position);
    float Offset = GetValueAt(TileCoord);

    TArray<float> MaterialIndexValues;
    int UpperIndex = -1;
    int LowerIndex = -1;
    float UpperIndexPosition = INT_MAX;
    float LowerIndexPosition = INT_MIN;

    for (int i = 0; i < MaterialIndexPositions.Num(); i++)
    {
        MaterialIndexValues.Add(0.0f);

        // Index is above or equal to offset
        if (Offset <= MaterialIndexPositions[i])
        {
            // Index is new closest upper index
            if (MaterialIndexPositions[i] <= UpperIndexPosition)
            {
                UpperIndex = i;
                UpperIndexPosition = MaterialIndexPositions[i];
            }
        }
        // Index is below offset
        else
        {
            // Index is new closest lower index
            if (MaterialIndexPositions[i] >= LowerIndexPosition)
            {
                LowerIndex = i;
                LowerIndexPosition = MaterialIndexPositions[i];
            }
        }
    }

    // Offset is lower than all index positions
    if (LowerIndex == -1)
    {
        MaterialIndexValues[UpperIndex] = 1.0f;
    }
    // Offset is greater than all index positions
    else if (UpperIndex == -1)
    {
        MaterialIndexValues[LowerIndex] = 1.0f;
    }
    // Offset is between two indices
    else
    {
        // Interpolate between lower and upper indices
        float Alpha = (Offset - LowerIndexPosition) / (UpperIndexPosition - LowerIndexPosition);
        MaterialIndexValues[LowerIndex] = 1.0f - Alpha;
        MaterialIndexValues[UpperIndex] = Alpha;
    }

    return MaterialIndexValues;
}

FColor FTileSphere::ColorCode(FVector Position) const
{
    Position -= Center;
    
    FTileCoord TileCoord = GetTileCoords(Position);
    FLinearColor Color = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //Color.R = (float) TileCoord.TileX / TileCoord.TileResolution;
    
    
    float Offset = GetValueAt(TileCoord);

    if (Offset < 0.5)
    {
        Color.R = 1.0;
        Color.G = Offset * 2.0f;
    } else {
        Color.R = (1.0 - Offset) * 2.0f;
        Color.G = 1.0;
    }
    
    Color.B = (float) TileCoord.TileY / TileCoord.TileResolution;
    
    return Color.ToFColor(false);
}