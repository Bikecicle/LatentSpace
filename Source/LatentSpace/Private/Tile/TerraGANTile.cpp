// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile/TerraGANTile.h"

FTerraGANTile::FTerraGANTile()
{
}

float FTerraGanTile::GetValueAt(FTileCoord TileCoord, int FaceResolution, unsigned int SphereSeed, UMachineLearningRemoteComponent* MachineLearningRemoteComponent)
{
	if (!bIsGenerated)
	{
		TArray<float> Latents[3][3];
		int TileIDs[3][3];
		FTileCoord Neighbor;
		int TileSeed;

		for (int i = 0; i < 3; i++)
		{
			int StepX = i - 1;
			for (int j = 0; j < 3; j++)
			{
				int StepY = j - 1;
				
				// We are looking at a neighboring tile
				if (StepX != 0 || StepY != 0)
				{
					Neighbor = TileCoord.Step(StepX, StepY, FaceResolution);

					// Neighboring tile is valid
					if (Neighbor != FTileCoord::EFace::None)
					{
						TileSeed = NoiseManager::GetValueNoise3D(Neighbor.Face, Neighbor.FaceX, Neighbor.FaceY, SphereSeed) / 2;
					}
					// Neighboring tile is over a corner (leave empty by setting TileID to -1)
					else
					{
						TileSeed = -1;
					}
				}
				// We are looking at the center tile
				else
				{
					TileSeed = NoiseManager::GetValueNoise3D(TileCoord.Face, TileCoord.FaceX, TileCoord.FaceY, SphereSeed) / 2;
				}

				Latents[i][j] = NoiseManager::GetLatent(LatentSize, TileSeed);
				TileIDs[i][j] = TileSeed;
			}
		}

		// TODO: Package latents and tileIDs and send to machine learning remote server
	}

	return Terrain[TileCoord.TileX][TileCoord.TileY];
}
