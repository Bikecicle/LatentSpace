// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile/TileCoord.h"

FTileCoord::FTileCoord()
{
}

FTileCoord FTileCoord::Step(int StepX, int StepY)
{
    FTileCoord NewTileCoord;
    NewTileCoord.FaceResolution = FaceResolution;
    NewTileCoord.TileResolution = TileResolution;

    bool bIsHorizontalEdge;
    bool bIsVerticalEdge;
    
    // Stepping over east edge
    if (FaceX + StepX >= FaceResolution)
    {
        bIsHorizontalEdge = true;
        NewTileCoord.FaceX = FaceX + StepX - FaceResolution;

        switch (Face)
        {
            case FTileCoord::EFace::Front:
                NewTileCoord.Face = FTileCoord::EFace::Right;
                NewTileCoord.Rotation = 0;
                break;

            case FTileCoord::EFace::Back:
                NewTileCoord.Face = FTileCoord::EFace::Left;
                NewTileCoord.Rotation = 0;
                break;

            case FTileCoord::EFace::Left:
                NewTileCoord.Face = FTileCoord::EFace::Front;
                NewTileCoord.Rotation = 0;
                break;

            case FTileCoord::EFace::Right:
                NewTileCoord.Face = FTileCoord::EFace::Back;
                NewTileCoord.Rotation = 0;
                break;

            case FTileCoord::EFace::Top:
                NewTileCoord.Face = FTileCoord::EFace::Right;
                NewTileCoord.Rotation = 1;
                break;

            case FTileCoord::EFace::Bottom:
                NewTileCoord.Face = FTileCoord::EFace::Right;
                NewTileCoord.Rotation = 3;
                break;
            
            default:
                break;
        }
    }
    // Stepping over west edge
    else if (FaceX + StepX < 0)
    {
        bIsHorizontalEdge = true;
        NewTileCoord.FaceX = FaceX + StepX + FaceResolution;

        switch (Face)
        {
            case FTileCoord::EFace::Front:
                NewTileCoord.Face = FTileCoord::EFace::Left;
                NewTileCoord.Rotation = 0;
                break;

            case FTileCoord::EFace::Back:
                NewTileCoord.Face = FTileCoord::EFace::Right;
                NewTileCoord.Rotation = 0;
                break;

            case FTileCoord::EFace::Left:
                NewTileCoord.Face = FTileCoord::EFace::Back;
                NewTileCoord.Rotation = 0;
                break;

            case FTileCoord::EFace::Right:
                NewTileCoord.Face = FTileCoord::EFace::Front;
                NewTileCoord.Rotation = 0;
                break;

            case FTileCoord::EFace::Top:
                NewTileCoord.Face = FTileCoord::EFace::Left;
                NewTileCoord.Rotation = 3;
                break;

            case FTileCoord::EFace::Bottom:
                NewTileCoord.Face = FTileCoord::EFace::Left;
                NewTileCoord.Rotation = 1;
                break;
            
            default:
                break;
        }
    }
    // Stepping within horizontal bounds
    else
    {
        bIsHorizontalEdge = false;
        NewTileCoord.FaceX = FaceX + StepX;
    }

    // Stepping over north edge
    if (FaceY + StepY >= FaceResolution)
    {
        bIsVerticalEdge = true;
        NewTileCoord.FaceY = FaceY + StepY - FaceResolution;

        switch (Face)
        {
            case FTileCoord::EFace::Front:
                NewTileCoord.Face = FTileCoord::EFace::Top;
                NewTileCoord.Rotation = 0;
                break;

            case FTileCoord::EFace::Back:
                NewTileCoord.Face = FTileCoord::EFace::Top;
                NewTileCoord.Rotation = 2;
                break;

            case FTileCoord::EFace::Left:
                NewTileCoord.Face = FTileCoord::EFace::Top;
                NewTileCoord.Rotation = 1;
                break;

            case FTileCoord::EFace::Right:
                NewTileCoord.Face = FTileCoord::EFace::Top;
                NewTileCoord.Rotation = 3;
                break;

            case FTileCoord::EFace::Top:
                NewTileCoord.Face = FTileCoord::EFace::Back;
                NewTileCoord.Rotation = 2;
                break;

            case FTileCoord::EFace::Bottom:
                NewTileCoord.Face = FTileCoord::EFace::Front;
                NewTileCoord.Rotation = 0;
                break;
            
            default:
                break;
            }
    }
    // Stepping over south edge
    else if (FaceY + StepY < 0)
    {
        bIsVerticalEdge = true;
        NewTileCoord.FaceY = FaceY + StepY + FaceResolution;

        switch (Face)
        {
            case FTileCoord::EFace::Front:
                NewTileCoord.Face = FTileCoord::EFace::Bottom;
                NewTileCoord.Rotation = 0;
                break;

            case FTileCoord::EFace::Back:
                NewTileCoord.Face = FTileCoord::EFace::Bottom;
                NewTileCoord.Rotation = 2;
                break;

            case FTileCoord::EFace::Left:
                NewTileCoord.Face = FTileCoord::EFace::Bottom;
                NewTileCoord.Rotation = 1;
                break;

            case FTileCoord::EFace::Right:
                NewTileCoord.Face = FTileCoord::EFace::Bottom;
                NewTileCoord.Rotation = 3;
                break;

            case FTileCoord::EFace::Top:
                NewTileCoord.Face = FTileCoord::EFace::Front;
                NewTileCoord.Rotation = 0;
                break;

            case FTileCoord::EFace::Bottom:
                NewTileCoord.Face = FTileCoord::EFace::Back;
                NewTileCoord.Rotation = 2;
                break;
            
            default:
                break;
        }
    }
    // Stepping within vertical bounds
    else
    {
        bIsVerticalEdge = false;
        NewTileCoord.FaceY = FaceY + StepY;
    }

    // Stepping over corner
    if (bIsHorizontalEdge && bIsVerticalEdge)
    {
        NewTileCoord.Face = FTileCoord::EFace::None;
    }
    // Stepping within all bounds
    else if (!bIsHorizontalEdge && !bIsVerticalEdge)
    {
        NewTileCoord.Face = Face;
        NewTileCoord.Rotation = 0;
    }
    // Stepping over a single edge
    else
    {
        int TempFaceX = NewTileCoord.FaceX;
        int TempFaceY = NewTileCoord.FaceY;
        int TempTileX = NewTileCoord.TileX;
        int TempTileY = NewTileCoord.TileY;

        // Perform counter-clockwise rotation of coordinates
        switch (Rotation)
        {
            // Rotate 90 degrees
            case 1:
                NewTileCoord.FaceX = FaceResolution - TempFaceY;
                NewTileCoord.FaceY = TempFaceX;
                NewTileCoord.TileX = FaceResolution - TempTileY;
                NewTileCoord.TileY = TempTileX;
                break;

            // Rotate 180 degrees
            case 2:
                NewTileCoord.FaceX = FaceResolution - TempFaceX;
                NewTileCoord.FaceY = FaceResolution - TempFaceY;
                NewTileCoord.TileX = TileResolution - TempTileX;
                NewTileCoord.TileY = TileResolution - TempTileY;
                break;

            // Rotate 270 degrees
            case 3:
                NewTileCoord.FaceX = TempFaceY;
                NewTileCoord.FaceY = FaceResolution - TempFaceX;
                NewTileCoord.TileX = TempTileY;
                NewTileCoord.TileY = TileResolution - TempTileX;
                break;
        }
    }

    return NewTileCoord;
}

unsigned int FTileCoord::GetSeed(unsigned int SphereSeed)
{
    return FNoiseManager::GetValueNoise3D(Face, FaceX, FaceY, SphereSeed);
}