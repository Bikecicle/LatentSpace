// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile/TerraGANTile.h"
#include "GenericPlatform/GenericPlatformProcess.h"

FTerraGANTile::FTerraGANTile(UMachineLearningRemoteComponent *pMachineLearningRemoteComponent)
	: MachineLearningRemoteComponent(pMachineLearningRemoteComponent)
{
	for (int i = 0; i < TileResolution; i++) {
		for (int j = 0; j < TileResolution; j++) {
			Terrain[i][j] = MakeShared<float, ESPMode::ThreadSafe>(0.0f);
		}
	}
}

float FTerraGANTile::GetValueAt(FTileCoord TileCoord, int FaceResolution, unsigned int SphereSeed)
{
	if (!bIsGenerated)
	{
		// Server is ready to generate tile

		if (MachineLearningRemoteComponent != nullptr && MachineLearningRemoteComponent->bScriptRunning)
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

			// Prepare data for sending to server
			TArray<TSharedPtr<FJsonValue>> TileIDArray;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					TileIDArray.Add(MakeShareable(new FJsonValueNumber(TileIDs[i][j])));
				}
			}
			TArray<TSharedPtr<FJsonValue>> LatentArray;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < LatentSize; k++)
					{
						LatentArray.Add(MakeShareable(new FJsonValueNumber(Latents[i][j][k])));
					}
				}
			}
			TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
			JsonObject->SetArrayField(TEXT("tile_ids"), TileIDArray);
			JsonObject->SetArrayField(TEXT("latents"), LatentArray);
			FString InputString = USIOJConvert::ToJsonString(JsonObject);

			FString FunctionName = TEXT("on_json_input");

			// Send data to server and handle response
			FEvent* ReceiveTileEvent = FGenericPlatformProcess::GetSynchEventFromPool(false);
			MachineLearningRemoteComponent->SendStringInput(
				InputString, [ReceiveTileEvent](const FString &ResultData)
				{
					TSharedPtr<FJsonObject> JsonObject = USIOJConvert::ToJsonObject(ResultData);
					TArray<TSharedPtr<FJsonValue>> TileIDArray = JsonObject->GetArrayField("tile_out");
					
					UE_LOG(LogTemp, Log, TEXT("Generated tile"));

					ReceiveTileEvent->Trigger();
				},
				FunctionName);
			ReceiveTileEvent->Wait();
			FGenericPlatformProcess::ReturnSynchEventToPool(ReceiveTileEvent);

			// Flag tile as generated
			bIsGenerated = true;
			UE_LOG(LogTemp, Log, TEXT("Tile flagged for generation %d %d %d"), TileCoord.Face, TileCoord.FaceX, TileCoord.FaceY);
		}
	}
	return 0.0f;
}
