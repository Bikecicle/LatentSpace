// Copyright 2021 Griffin Page

#include "Tile/TerraGANTile.h"
#include "GenericPlatform/GenericPlatformProcess.h"

FTerraGANTile::FTerraGANTile(UMachineLearningRemoteComponent *TileMachineLearningRemoteComponent)
	: MachineLearningRemoteComponent(TileMachineLearningRemoteComponent)
{
	for (int i = 0; i < TileResolution; i++)
	{
		for (int j = 0; j < TileResolution; j++)
		{
			Terrain[i][j] = 0.0f;
		}
	}
	bIsGenerated = false;
}

void FTerraGANTile::Generate(FTileCoord TileCoord, unsigned int SphereSeed)
{
	if (MachineLearningRemoteComponent != nullptr && MachineLearningRemoteComponent->bIsConnectedToBackend)
	{
		UE_LOG(LogTemp, Log, TEXT("MachineLearningRemoteComponent Connected... beginning generation"));
		float Latents[3][3][LatentSize];
		int TileIDs[3][3];
		FTileCoord TileCoords[3][3];

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
					Neighbor = TileCoord.TileStep(StepX, StepY);

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
					TileCoords[i][j] = Neighbor;
				}
				// We are looking at the center tile
				else
				{
					TileSeed = FNoiseManager::GetValueNoise3D(TileCoord.Face, TileCoord.FaceX, TileCoord.FaceY, SphereSeed) / 2;
					TileCoords[i][j] = TileCoord;
				}

				FNoiseManager::GenerateLatent(Latents[i][j], LatentSize, TileSeed);
				TileIDs[i][j] = TileSeed;
			}
		}

		// Prepare data for sending to server
		TArray<TSharedPtr<FJsonValue>> TileIDArray;
		TArray<TSharedPtr<FJsonValue>> FaceArray;
		TArray<TSharedPtr<FJsonValue>> FaceXArray;
		TArray<TSharedPtr<FJsonValue>> FaceYArray;
		TArray<TSharedPtr<FJsonValue>> RotationArray;
		TArray<TSharedPtr<FJsonValue>> LatentArray;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				TileIDArray.Add(MakeShareable(new FJsonValueNumber(TileIDs[j][i])));
				FaceArray.Add(MakeShareable(new FJsonValueNumber(TileCoords[j][i].Face)));
				FaceXArray.Add(MakeShareable(new FJsonValueNumber(TileCoords[j][i].FaceX)));
				FaceYArray.Add(MakeShareable(new FJsonValueNumber(TileCoords[j][i].FaceY)));
				RotationArray.Add(MakeShareable(new FJsonValueNumber(TileCoords[j][i].Rotation)));
				for (int k = 0; k < LatentSize; k++)
				{
					LatentArray.Add(MakeShareable(new FJsonValueNumber(Latents[j][i][k])));
				}
				UE_LOG(LogTemp, Log, TEXT("Gathered adjecent tile %d %d %d %d: %d"), TileCoords[j][i].Face, TileCoords[j][i].FaceX, TileCoords[j][i].FaceY, TileCoords[j][i].Rotation, TileIDs[j][i]);
			}
		}
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
		JsonObject->SetArrayField(TEXT("tile_ids"), TileIDArray);
		JsonObject->SetArrayField(TEXT("faces"), FaceArray);
		JsonObject->SetArrayField(TEXT("x"), FaceXArray);
		JsonObject->SetArrayField(TEXT("y"), FaceYArray);
		JsonObject->SetArrayField(TEXT("rotations"), RotationArray);
		JsonObject->SetArrayField(TEXT("latents"), LatentArray);
		FString InputString = USIOJConvert::ToJsonString(JsonObject);

		FString FunctionName = TEXT("on_json_input");

		// Send data to server and handle response
		FEvent *ReceiveTileEvent = FGenericPlatformProcess::GetSynchEventFromPool(false);
		MachineLearningRemoteComponent->SendStringInput(
			InputString, [ReceiveTileEvent, this](const FString &ResultData)
			{
				TSharedPtr<FJsonObject> JsonObject = USIOJConvert::ToJsonObject(ResultData);
				TArray<TSharedPtr<FJsonValue>> TileOut = JsonObject->GetArrayField("tile_out");

				for (int i = 0; i < TileResolution; i++)
				{
					for (int j = 0; j < TileResolution; j++)
					{
						// Tile out goes left to right, top to bottom so do awkward 90 degree rotation
						Terrain[i][j] = TileOut[i + (TileResolution - j - 1) * TileResolution]->AsNumber();
					}
				}

				UE_LOG(LogTemp, Log, TEXT("Generated tile"));

				ReceiveTileEvent->Trigger();
			},
			FunctionName);

		UE_LOG(LogTemp, Log, TEXT("Tile waiting for generation %d %d %d"), TileCoord.Face, TileCoord.FaceX, TileCoord.FaceY);
		ReceiveTileEvent->Wait();
		FGenericPlatformProcess::ReturnSynchEventToPool(ReceiveTileEvent);

	}
	// Flag tile as generated
	bIsGenerated = true;
}

float FTerraGANTile::GetValueAt(FTileCoord TileCoord, unsigned int SphereSeed)
{
	if (!bIsGenerated)
	{
		Generate(TileCoord, SphereSeed);
	}
	return Terrain[TileCoord.TileX][TileCoord.TileY];
}
