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

    int Rotation;

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
                Rotation = 0;
                break;

            case FTileCoord::EFace::Back:
                NewTileCoord.Face = FTileCoord::EFace::Left;
                Rotation = 0;
                break;

            case FTileCoord::EFace::Left:
                NewTileCoord.Face = FTileCoord::EFace::Front;
                Rotation = 0;
                break;

            case FTileCoord::EFace::Right:
                NewTileCoord.Face = FTileCoord::EFace::Back;
                Rotation = 0;
                break;

            case FTileCoord::EFace::Top:
                NewTileCoord.Face = FTileCoord::EFace::Right;
                Rotation = 1;
                break;

            case FTileCoord::EFace::Bottom:
                NewTileCoord.Face = FTileCoord::EFace::Right;
                Rotation = 3;
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
                Rotation = 0;
                break;

            case FTileCoord::EFace::Back:
                NewTileCoord.Face = FTileCoord::EFace::Right;
                Rotation = 0;
                break;

            case FTileCoord::EFace::Left:
                NewTileCoord.Face = FTileCoord::EFace::Back;
                Rotation = 0;
                break;

            case FTileCoord::EFace::Right:
                NewTileCoord.Face = FTileCoord::EFace::Front;
                Rotation = 0;
                break;

            case FTileCoord::EFace::Top:
                NewTileCoord.Face = FTileCoord::EFace::Left;
                Rotation = 3;
                break;

            case FTileCoord::EFace::Bottom:
                NewTileCoord.Face = FTileCoord::EFace::Left;
                Rotation = 1;
                break;
            
            default:
                break;
        }
    }
    // Stepping within horizontal bounds
    else
    {
        bIsHorizontalEdge = false;
        NewTileCoord.TileX = TileX + StepX;
    }

    // Stepping over north edge
    if (FaceY + StepY >= FaceResolution)
    {
        bIsVerticalEdge = true;
        NewTileCoord.TileY = TileY + StepY - FaceResolution;

        switch (Face)
        {
            case FTileCoord::EFace::Front:
                NewTileCoord.Face = FTileCoord::EFace::Top;
                Rotation = 0;
                break;

            case FTileCoord::EFace::Back:
                NewTileCoord.Face = FTileCoord::EFace::Top;
                Rotation = 2;
                break;

            case FTileCoord::EFace::Left:
                NewTileCoord.Face = FTileCoord::EFace::Top;
                Rotation = 1;
                break;

            case FTileCoord::EFace::Right:
                NewTileCoord.Face = FTileCoord::EFace::Top;
                Rotation = 3;
                break;

            case FTileCoord::EFace::Top:
                NewTileCoord.Face = FTileCoord::EFace::Back;
                Rotation = 2;
                break;

            case FTileCoord::EFace::Bottom:
                NewTileCoord.Face = FTileCoord::EFace::Front;
                Rotation = 0;
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
                Rotation = 0;
                break;

            case FTileCoord::EFace::Back:
                NewTileCoord.Face = FTileCoord::EFace::Bottom;
                Rotation = 2;
                break;

            case FTileCoord::EFace::Left:
                NewTileCoord.Face = FTileCoord::EFace::Bottom;
                Rotation = 1;
                break;

            case FTileCoord::EFace::Right:
                NewTileCoord.Face = FTileCoord::EFace::Bottom;
                Rotation = 3;
                break;

            case FTileCoord::EFace::Top:
                NewTileCoord.Face = FTileCoord::EFace::Front;
                Rotation = 0;
                break;

            case FTileCoord::EFace::Bottom:
                NewTileCoord.Face = FTileCoord::EFace::Back;
                Rotation = 2;
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
    }
    // Stepping over a single edge
    else
    {
        int TempX = NewTileCoord.TileX;
        int TempY = NewTileCoord.TileY;

        // Perform counter-clockwise rotation of tile coordinates
        switch (Rotation)
        {
            // Rotate 90 degrees
            case 1:
                NewTileCoord.TileX = TileResolution - TempY;
                NewTileCoord.TileY = TempX;
                break;

            // Rotate 180 degrees
            case 2:
                NewTileCoord.TileX = TileResolution - TempX;
                NewTileCoord.TileY = TileResolution - TempY;
                break;

            // Rotate 270 degrees
            case 3:
                NewTileCoord.TileX = TempY;
                NewTileCoord.TileY = TileResolution - TempX;
                break;

            default:
                break;
        }
    }

    return NewTileCoord;
}

unsigned int FTileCoord::GetSeed(unsigned int SphereSeed)
{
    return FNoiseManager::GetValueNoise3D(Face, FaceX, FaceY, SphereSeed);
}