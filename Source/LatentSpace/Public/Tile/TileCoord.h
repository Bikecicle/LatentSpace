// Copyright 2021 Griffin Page

#pragma once

#include "CoreMinimal.h"
#include "Utils/NoiseManager.h"

/** A set of coordinates representing a tile on the surface of a cube */
class LATENTSPACE_API FTileCoord
{
public:
	FTileCoord();
	
	enum EFace { Front, Back, Left, Right, Top, Bottom, None };

	/** Denotes on which face of the cube the tile lies */
	EFace Face;
	/** The X position of the tile relative to the cube face */
	int FaceX;
	/** The Y position of the tile relative to the cube face */
	int FaceY;
	/** The X position within the tile */
	int TileX;
	/** The Y position within the tile */
	int TileY;

	float PixelX;

	float PixelY;
	/** Number of 90 degree counter-clockwise rotations to perform on coordinates */
	int Rotation;

	int FaceResolution;
	int TileResolution;

	/**
	 * Get the tile relative to this tile given an X and Y displacement and considering passage between faces.
	 * @param StepX - Distance to move in the X direction with respect to this tile's orientation (-FaceResolution, FaceResolution)
	 * @param StepY - Distance to move in the Y direction with respect to this tile's orientation (-FaceResolution, FaceResolution)
	 * @return The new tile
	 */
	FTileCoord TileStep(int StepX, int StepY);
	FTileCoord PixelStep(int StepX, int StepY);

	unsigned int GetSeed(unsigned int SphereSeed);
};
