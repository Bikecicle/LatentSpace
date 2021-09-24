// Copyright 2021 Griffin Page

#pragma once

#include "CoreMinimal.h"
#include "Fractal/Fractal.h"
#include "VoxelGenerators/VoxelGeneratorHelpers.h"
#include "FractalWorldGenerator.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UFractalWorldGenerator : public UVoxelGenerator
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
	float Scale = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
	int Iterations = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
	float DistanceOffset = 0.0f;

	//~ Begin UVoxelGenerator Interface
	virtual TVoxelSharedRef<FVoxelGeneratorInstance> GetInstance() override;
	//~ End UVoxelGenerator Interface

};

class FFractalWorldGeneratorInstance : public TVoxelGeneratorInstanceHelper<FFractalWorldGeneratorInstance, UFractalWorldGenerator>
{
public:
	using Super = TVoxelGeneratorInstanceHelper<FFractalWorldGeneratorInstance, UFractalWorldGenerator>;

	explicit FFractalWorldGeneratorInstance(const UFractalWorldGenerator& MyGenerator);

	//~ Begin FVoxelGeneratorInstance Interface
	virtual void Init(const FVoxelGeneratorInit& InitStruct) override;

	v_flt GetValueImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const;
	FVoxelMaterial GetMaterialImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const;

	TVoxelRange<v_flt> GetValueRangeImpl(const FVoxelIntBox& Bounds, int32 LOD, const FVoxelItemStack& Items) const;

	virtual FVector GetUpVector(v_flt X, v_flt Y, v_flt Z) const override final;
	//~ End FVoxelGeneratorInstance Interface

private:
	FFractal Fractal;
};