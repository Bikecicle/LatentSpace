// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile/TileCoord.h"

FTileCoord::FTileCoord()
{
}

int FTileCoord::GetRotation(FTileCoord::EFace Face1, FTileCoord::EFace Face2)
{
    int Rotation;

    switch (Face1)
    {
    case FTileCoord::EFace::Front:
        switch (Face2)
        {
        case FTileCoord::EFace::Right:
            Rotation = 0;
            break;

        case FTileCoord::EFace::Top:
            Rotation = 0;
            break;
        
        case FTileCoord::EFace::Left:
            Rotation = 0;
            break;

        case FTileCoord::EFace::Bottom:
            Rotation = 0;
            break;
        
        default:
            Rotation = -1;
            break;
        }
        break;

    case FTileCoord::EFace::Back:
        switch (Face2)
        {
        case FTileCoord::EFace::Left:
            Rotation = 0;
            break;

        case FTileCoord::EFace::Top:
            Rotation = 2;
            break;
        
        case FTileCoord::EFace::Right:
            Rotation = 0;
            break;

        case FTileCoord::EFace::Bottom:
            Rotation = 2;
            break;
        
        default:
            Rotation = -1;
            break;
        }
        break;

    case FTileCoord::EFace::Left:
        switch (Face2)
        {
        case FTileCoord::EFace::Front:
            Rotation = 0;
            break;

        case FTileCoord::EFace::Top:
            Rotation = 1;
            break;
        
        case FTileCoord::EFace::Back:
            Rotation = 0;
            break;

        case FTileCoord::EFace::Bottom:
            Rotation = 3;
            break;
        
        default:
            Rotation = -1;
            break;
        }
        break;

    case FTileCoord::EFace::Right:
        switch (Face2)
        {
        case FTileCoord::EFace::Back:
            Rotation = 0;
            break;

        case FTileCoord::EFace::Top:
            Rotation = 3;
            break;
        
        case FTileCoord::EFace::Front:
            Rotation = 0;
            break;

        case FTileCoord::EFace::Bottom:
            Rotation = 1;
            break;
        
        default:
            Rotation = -1;
            break;
        }
        break;

    case FTileCoord::EFace::Top:
        switch (Face2)
        {
        case FTileCoord::EFace::Right:
            Rotation = 1;
            break;

        case FTileCoord::EFace::Back:
            Rotation = 2;
            break;
        
        case FTileCoord::EFace::Left:
            Rotation = 3;
            break;

        case FTileCoord::EFace::Front:
            Rotation = 0;
            break;
        
        default:
            Rotation = -1;
            break;
        }
        break;

    case FTileCoord::EFace::Bottom:
        switch (Face2)
        {
        case FTileCoord::EFace::Right:
            Rotation = 3;
            break;

        case FTileCoord::EFace::Front:
            Rotation = 0;
            break;
        
        case FTileCoord::EFace::Left:
            Rotation = 1;
            break;

        case FTileCoord::EFace::Back:
            Rotation = 2;
            break;
        
        default:
            Rotation = -1;
            break;
        }
        break;
    
    default:
        Rotation = -1;
        break;
    }

    return Rotation;
}

FTileCoord FTileCoord::Step()
{
    FTileCoord NewTileCoord;
    //...
    return NewTileCoord;
}
