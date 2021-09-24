// Copyright 2021 Griffin Page

#pragma once

#include "CoreMinimal.h"
#include "Tile/TileSphere.h"
#include "Fractal/Fractal.h"

#include "FastNoise/VoxelFastNoise.h"
#include "Utils/NoiseManager.h"

#include "VoxelGenerators/VoxelGeneratorHelpers.h"
#include "MachineLearningRemoteComponent.h"
#include "HybridWorldGenerator.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class UHybridWorldGenerator : public UVoxelGenerator
{
	GENERATED_BODY()

public:

	// World properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World")
	int WorldSeed = 0;

	// TileSphere properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSphere")
	FVector Center = FVector(0, 0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSphere")
	float Radius = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileSphere")
	float ElevationAmplitude = 1.0f;


	// Fractal properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fractal")
	float Scale = 1.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fractal")
	int Iterations = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fractal")
	float DistanceOffset = 0.0;

	//~ Begin UVoxelGenerator Interface
	virtual TVoxelSharedRef<FVoxelGeneratorInstance> GetInstance() override;
	//~ End UVoxelGenerator Interface

};

class FHybridWorldGeneratorInstance : public TVoxelGeneratorInstanceHelper<FHybridWorldGeneratorInstance, UHybridWorldGenerator>
{
public:
	using Super = TVoxelGeneratorInstanceHelper<FHybridWorldGeneratorInstance, UHybridWorldGenerator>;

	explicit FHybridWorldGeneratorInstance(const UHybridWorldGenerator& MyGenerator);

	//~ Begin FVoxelGeneratorInstance Interface
	virtual void Init(const FVoxelGeneratorInit& InitStruct) override;

	v_flt GetValueImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const;
	FVoxelMaterial GetMaterialImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const;

	TVoxelRange<v_flt> GetValueRangeImpl(const FVoxelIntBox& Bounds, int32 LOD, const FVoxelItemStack& Items) const;

	virtual FVector GetUpVector(v_flt X, v_flt Y, v_flt Z) const override final;
	//~ End FVoxelGeneratorInstance Interface

private:
	FTileSphere TileSphere;
	FFractal Fractal;
	int WorldSeed;
	FVoxelFastNoise MorphNoise;
};