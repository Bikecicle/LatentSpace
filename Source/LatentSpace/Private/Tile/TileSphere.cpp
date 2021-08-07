// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile/TileSphere.h"
#include "FastNoise/VoxelFastNoise.inl"


FTileSphere::FTileSphere(FVector Center, float Radius, int Resolution)
{
	this->Center = Center;
	this->Radius = Radius;
    this->Resolution = Resolution;

    MachineLearningRemoteComponent = NewObject<UMachineLearningRemoteComponent>();
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

    const double InverseSqrt2 = 0.70710676908493042;

    // X-axis
    if (AbsX >= AbsY && AbsX >= AbsZ) {
        double A = Y * Y * 2.0;
        double B = Z * Z * 2.0;
        double Inner = -A + B - 3;
        double InnerSqrt = -sqrtf((Inner * Inner) - 12.0 * A);

        if (Y == 0.0 || Y == -0.0) {
            TileCoord.X = 0.0;
        }
        else {
            TileCoord.X = sqrtf(InnerSqrt + A - B + 3.0) * InverseSqrt2;
        }

        if (Z == 0.0 || Z == -0.0) {
            TileCoord.Y = 0.0;
        }
        else {
            TileCoord.Y = sqrtf(InnerSqrt - A + B + 3.0) * InverseSqrt2;
        }

        if (TileCoord.X > 1.0) TileCoord.X = 1.0;
        if (TileCoord.Y > 1.0) TileCoord.Y = 1.0;

        if (Z < 0) TileCoord.Y = -TileCoord.Y;

        if (X > 0) {
            TileCoord.Face = FTileCoord::EFace::Front;
            if (Y > 0) TileCoord.X = -TileCoord.X;
        }
        else {
            TileCoord.Face = FTileCoord::EFace::Back;
            if (Y < 0) TileCoord.X = -TileCoord.X;
        }
    }

    // Y-axis
    else if (AbsY >= AbsX && AbsY >= AbsZ) {
        double A = X * X * 2.0;
        double B = Z * Z * 2.0;
        double Inner = -A + B - 3;
        double InnerSqrt = -sqrtf((Inner * Inner) - 12.0 * A);

        if (X == 0.0 || X == -0.0) {
            TileCoord.X = 0.0;
        }
        else {
            TileCoord.X = sqrtf(InnerSqrt + A - B + 3.0) * InverseSqrt2;
        }

        if (Z == 0.0 || Z == -0.0) {
            TileCoord.Y = 0.0;
        }
        else {
            TileCoord.Y = sqrtf(InnerSqrt - A + B + 3.0) * InverseSqrt2;
        }

        if (TileCoord.X > 1.0) TileCoord.X = 1.0;
        if (TileCoord.Y > 1.0) TileCoord.Y = 1.0;

        if (Z < 0) TileCoord.Y = -TileCoord.Y;

        if (Y > 0) {
            TileCoord.Face = FTileCoord::EFace::Left;
            if (X < 0) TileCoord.X = -TileCoord.X;
        }
        else {
            TileCoord.Face = FTileCoord::EFace::Right;
            if (X > 0) TileCoord.X = -TileCoord.X;
        }
    }

    // Z-axis
    else {
        double A = Y * Y * 2.0;
        double B = X * X * 2.0;
        double Inner = -A + B - 3;
        double InnerSqrt = -sqrtf((Inner * Inner) - 12.0 * A);

        if (Y == 0.0 || Y == -0.0) {
            TileCoord.X = 0.0;
        }
        else {
            TileCoord.X = sqrtf(InnerSqrt + A - B + 3.0) * InverseSqrt2;
        }

        if (X == 0.0 || X == -0.0) {
            TileCoord.Y = 0.0;
        }
        else {
            TileCoord.Y = sqrtf(InnerSqrt - A + B + 3.0) * InverseSqrt2;
        }

        if (TileCoord.X > 1.0) TileCoord.X = 1.0;
        if (TileCoord.Y > 1.0) TileCoord.Y = 1.0;

        if (Y > 0) TileCoord.X = -TileCoord.X;

        if (Z > 0) {
            TileCoord.Face = FTileCoord::EFace::Top;
            if (X > 0) TileCoord.Y = -TileCoord.Y;
        }
        else {
            TileCoord.Face = FTileCoord::EFace::Bottom;
            if (X < 0) TileCoord.Y = -TileCoord.Y;
        }
    }

    return TileCoord;
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