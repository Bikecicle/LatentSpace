// Copyright 2021 Griffin Page


#include "Tile/TileCoord.h"

FTileCoord::FTileCoord()
    : Face(EFace::None)
    , FaceX(0)
    , FaceY(0)
    , TileX(0)
    , TileY(0)
    , PixelX(0)
    , PixelY(0)
    , Rotation(0)
{
}

FTileCoord FTileCoord::TileStep(int TileStepX, int TileStepY)
{
    FTileCoord NewTileCoord = *this;

    bool bIsHorizontalEdge;
    bool bIsVerticalEdge;
    
    // Stepping over east edge of face
    if (FaceX + TileStepX >= FaceResolution)
    {
        bIsHorizontalEdge = true;
        NewTileCoord.FaceX = FaceX + TileStepX - FaceResolution;

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
    // Stepping over west edge of face
    else if (FaceX + TileStepX < 0)
    {
        bIsHorizontalEdge = true;
        NewTileCoord.FaceX = FaceX + TileStepX + FaceResolution;

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
    // Stepping within horizontal bounds of face
    else
    {
        bIsHorizontalEdge = false;
        NewTileCoord.FaceX = FaceX + TileStepX;
    }

    // Stepping over north edge of face
    if (FaceY + TileStepY >= FaceResolution)
    {
        bIsVerticalEdge = true;
        NewTileCoord.FaceY = FaceY + TileStepY - FaceResolution;

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
    // Stepping over south edge of face
    else if (FaceY + TileStepY < 0)
    {
        bIsVerticalEdge = true;
        NewTileCoord.FaceY = FaceY + TileStepY + FaceResolution;

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
    // Stepping within vertical bounds of face
    else
    {
        bIsVerticalEdge = false;
        NewTileCoord.FaceY = FaceY + TileStepY;
    }

    // Stepping over corner of face
    if (bIsHorizontalEdge && bIsVerticalEdge)
    {
        NewTileCoord.Face = FTileCoord::EFace::None;
    }
    // Stepping within all bounds of face
    else if (!bIsHorizontalEdge && !bIsVerticalEdge)
    {
        NewTileCoord.Face = Face;
        NewTileCoord.Rotation = 0;
    }
    // Stepping over a single edge of face
    else
    {
        int TempFaceX = NewTileCoord.FaceX;
        int TempFaceY = NewTileCoord.FaceY;

        int TempTileX = NewTileCoord.TileX;
        int TempTileY = NewTileCoord.TileY;

        float TempPixelX = NewTileCoord.PixelX;
        float TempPixelY = NewTileCoord.PixelY;

        // Perform counter-clockwise rotation of coordinates
        switch (NewTileCoord.Rotation)
        {
            // Rotate 90 degrees
            case 1:
                NewTileCoord.FaceX = TempFaceY;
                NewTileCoord.FaceY = FaceResolution - TempFaceX - 1;

                NewTileCoord.TileX = TempTileY;
                NewTileCoord.TileY = TileResolution - TempTileX - 1;

                NewTileCoord.PixelX = TempPixelY;
                NewTileCoord.PixelY = 1 - TempPixelX;

                break;

            // Rotate 180 degrees
            case 2:
                NewTileCoord.FaceX = FaceResolution - TempFaceX - 1;
                NewTileCoord.FaceY = FaceResolution - TempFaceY - 1;

                NewTileCoord.TileX = TileResolution - TempTileX - 1;
                NewTileCoord.TileY = TileResolution - TempTileY - 1;

                NewTileCoord.PixelX = 1 - TempPixelX;
                NewTileCoord.PixelY = 1 - TempPixelY;

                break;

            // Rotate 270 degrees
            case 3:
                NewTileCoord.FaceX = FaceResolution - TempFaceY - 1;
                NewTileCoord.FaceY = TempFaceX;

                NewTileCoord.TileX = TileResolution - TempTileY - 1;
                NewTileCoord.TileY = TempTileX;

                NewTileCoord.PixelX = 1 - TempPixelY;
                NewTileCoord.PixelY = TempPixelX;

                break;
        }
    }

    return NewTileCoord;
}

FTileCoord FTileCoord::PixelStep(int PixelStepX, int PixelStepY)
{
    FTileCoord NewTileCoord = *this;

    int TileStepX = 0;
    int TileStepY = 0;
    
    // Stepping over east edge of tile
    if (TileX + PixelStepX >= TileResolution)
    {
        NewTileCoord.TileX = TileX + PixelStepX - TileResolution;
        TileStepX = 1;
    }
    // Stepping over west edge of tile
    else if (TileX + PixelStepX < 0)
    {
        NewTileCoord.TileX = TileX + PixelStepX + TileResolution;
        TileStepX = -1;
    }
    // Stepping within horizontal bounds of tile
    else
    {
        NewTileCoord.TileX = TileX + PixelStepX;
        TileStepX = 0;
    }

    // Stepping over north edge of tile
    if (TileY + PixelStepY >= TileResolution)
    {
        NewTileCoord.TileY = TileY + PixelStepY - TileResolution;
        TileStepY = 1;
    }
    // Stepping over south edge of tile
    else if (TileY + PixelStepY < 0)
    {
        NewTileCoord.TileY = TileY + PixelStepY + TileResolution;
        TileStepY = -1;
    }
    // Stepping within vertical bounds of tile
    else
    {
        NewTileCoord.TileY = TileY + PixelStepY;
        TileStepY = 0;
    }

    // Step to adjacent tile if needed
    if (TileStepX != 0 || TileStepY != 0)
    {
        NewTileCoord = NewTileCoord.TileStep(TileStepX, TileStepY);
    }

    return NewTileCoord;
}

unsigned int FTileCoord::GetSeed(unsigned int SphereSeed)
{
    return FNoiseManager::GetValueNoise3D(Face, FaceX, FaceY, SphereSeed);
}