// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile/TileSphere.h"
#include "VoxelGenerators/VoxelGeneratorHelpers.h"
#include "SphericalWorldGenerator.generated.h"


/**
 *
 */
UCLASS(Blueprintable)
class USphericalWorldGenerator : public UVoxelGenerator
{
	GENERATED_BODY()

public:

	//~ Begin UVoxelGenerator Interface
	virtual TVoxelSharedRef<FVoxelGeneratorInstance> GetInstance() override;
	//~ End UVoxelGenerator Interface

};

class FSphericalWorldGeneratorInstance : public TVoxelGeneratorInstanceHelper<FSphericalWorldGeneratorInstance, USphericalWorldGenerator>
{
public:
	using Super = TVoxelGeneratorInstanceHelper<FSphericalWorldGeneratorInstance, USphericalWorldGenerator>;

	explicit FSphericalWorldGeneratorInstance(const USphericalWorldGenerator& MyGenerator);

	//~ Begin FVoxelGeneratorInstance Interface
	virtual void Init(const FVoxelGeneratorInit& InitStruct) override;

	v_flt GetValueImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const;
	FVoxelMaterial GetMaterialImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const;

	TVoxelRange<v_flt> GetValueRangeImpl(const FVoxelIntBox& Bounds, int32 LOD, const FVoxelItemStack& Items) const;

	virtual FVector GetUpVector(v_flt X, v_flt Y, v_flt Z) const override final;
	//~ End FVoxelGeneratorInstance Interface

private:
	FTileSphere Sphere;
};