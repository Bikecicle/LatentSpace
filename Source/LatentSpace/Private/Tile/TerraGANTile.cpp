// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile/TerraGANTile.h"

FTerraGANTile::FTerraGANTile(UMachineLearningRemoteComponent* pMachineLearningRemoteComponent)
	: MachineLearningRemoteComponent(pMachineLearningRemoteComponent)
{
}

float FTerraGANTile::GetValueAt(FTileCoord TileCoord, int FaceResolution, unsigned int SphereSeed)
{
	if (!bIsGenerated)
	{
		float Latents[3][3][LatentSize];
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
					if (Neighbor.Face != FTileCoord::EFace::None)
					{
						TileSeed = FNoiseManager::GetValueNoise3D(Neighbor.Face, Neighbor.FaceX, Neighbor.FaceY, SphereSeed) / 2;
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
					TileSeed = FNoiseManager::GetValueNoise3D(TileCoord.Face, TileCoord.FaceX, TileCoord.FaceY, SphereSeed) / 2;
				}

				FNoiseManager::GenerateLatent(Latents[i][j], LatentSize, TileSeed);
				TileIDs[i][j] = TileSeed;
			}
		}

		// Flatten data
		TArray<float> InputData;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < LatentSize; k++)
				{
					InputData.Add(Latents[i][j][k]);
				}
			}
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				InputData.Add(TileIDs[i][j]);
			}
		}
		
		if (MachineLearningRemoteComponent != nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("Valid UMachineLearningRemoteComponent found"));
			
			FString FunctionName = TEXT("on_float_array_input");
			
			MachineLearningRemoteComponent->SendRawInput(InputData, [this](TArray<float>& ResultData)
			{
				//Now we got our results back, do something with them here
			}, FunctionName);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("No valid UMachineLearningRemoteComponent found"));
		}
		

		bIsGenerated = true;
		UE_LOG(LogTemp, Log, TEXT("Generated tile %d %d %d"), TileCoord.Face, TileCoord.FaceX, TileCoord.FaceY);
	}

	return 0.0f;
}
