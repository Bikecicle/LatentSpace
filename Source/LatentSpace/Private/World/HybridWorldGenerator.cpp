// Copyright 2021 Griffin Page

#include "World/HybridWorldGenerator.h"
#include "FastNoise/VoxelFastNoise.inl"
#include "VoxelMaterialBuilder.h"
#include "VoxelWorld.h"

#include "Fractal/Fold/FoldBox.h"
#include "Fractal/Fold/FoldSphere.h"
#include "Fractal/Fold/FoldScaleOrigin.h"
#include "Fractal/Base/BaseBox.h"


TVoxelSharedRef<FVoxelGeneratorInstance> UHybridWorldGenerator::GetInstance()
{
	return MakeVoxelShared<FHybridWorldGeneratorInstance>(*this);
}

////////////////////////////////////////////////////////////////////////////s///

FHybridWorldGeneratorInstance::FHybridWorldGeneratorInstance(const UHybridWorldGenerator &MyGenerator)
	: Super(&MyGenerator)
	, TileSphere(MyGenerator.Center, MyGenerator.Radius, MyGenerator.ElevationAmplitude)
    , Fractal(MyGenerator.Scale, MyGenerator.DistanceOffset, MyGenerator.Iterations)
    , WorldSeed(MyGenerator.WorldSeed)
{
}

void FHybridWorldGeneratorInstance::Init(const FVoxelGeneratorInit &InitStruct)
{
	// Assign UMachineLearningComponent to tiles for querying server
	if (InitStruct.World != nullptr)
	{
		UMachineLearningRemoteComponent *MachineLearningRemoteComponent = InitStruct.World->FindComponentByClass<UMachineLearningRemoteComponent>();
		TileSphere.Init(MachineLearningRemoteComponent, FNoiseManager::GetValueNoise1D(1, WorldSeed));
	}
	
    // Set material index positions for tiles
	TArray<float> MaterialIndexPositions;
	MaterialIndexPositions.Add(0.3f); // Set index 0 position
	MaterialIndexPositions.Add(0.7f); // Set index 1 position
	TileSphere.SetMaterialIndexPositions(MaterialIndexPositions);

    // Build fractal
    Fractal.AddFold(new FFoldBox(FVector(1.0, 1.0, 1.0)));
	Fractal.AddFold(new FFoldSphere(0.5, 1.0));
	Fractal.AddFold(new FFoldScaleOrigin(2.0));
	Fractal.SetBase(new FBaseBox(FVector(6, 6, 6), FVector(0, 0, 0), FVector(0, 0, 0)));

    // Assign morph noise seed from world seed

    MorphNoise.SetSeed(FNoiseManager::GetValueNoise1D(0, WorldSeed));
}

v_flt FHybridWorldGeneratorInstance::GetValueImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack &Items) const
{
	float Morph = MorphNoise.GetPerlin_3D(X / 100.0, Y / 100.0, Z / 100.0, 0.01);
	float Distance = 0.0f;
    if (Morph >= 0)
    {
        Distance = TileSphere.GetSignedDistance(FVector(X, Y, Z));
    }
    else
    {

        Distance = Fractal.GetSignedDistance(FVector(X, Y, Z));
    }
    return Distance;
}

FVoxelMaterial FHybridWorldGeneratorInstance::GetMaterialImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack &Items) const
{
	FVoxelMaterialBuilder Builder;

	// RGB
	//Builder.SetMaterialConfig(EVoxelMaterialConfig::RGB);
	//Builder.SetColor(TileSphere.ColorCode(FVector4(X, Y, Z, 1.0)));

	// Single index
	//Builder.SetMaterialConfig(EVoxelMaterialConfig::SingleIndex);
	//Builder.SetSingleIndex(0);

	// Multi index
	Builder.SetMaterialConfig(EVoxelMaterialConfig::MultiIndex);
	float Morph = MorphNoise.GetPerlin_3D(X / 100.0, Y / 100.0, Z / 100.0, 0.01);
    if (Morph >= 0)
    {
		TArray<float> MaterialIndexValues = TileSphere.GetMaterialIndexValues(FVector(X, Y, Z));
        Builder.AddMultiIndex(0, MaterialIndexValues[0]);
	    Builder.AddMultiIndex(1, MaterialIndexValues[1]);
		Builder.AddMultiIndex(2, 0.0f);
    }
    else
    {
	    Builder.AddMultiIndex(0, 0.0f);
        Builder.AddMultiIndex(1, 0.0f);
		Builder.AddMultiIndex(2, 1.0f);
    }
	return Builder.Build();
}

TVoxelRange<v_flt> FHybridWorldGeneratorInstance::GetValueRangeImpl(const FVoxelIntBox &Bounds, int32 LOD, const FVoxelItemStack &Items) const
{
	// Return the values that GetValueImpl can return in Bounds
	// Used to skip chunks where the value does not change
	// Be careful, if wrong your world will have holes!
	// By default return infinite range to be safe
	return TVoxelRange<v_flt>::Infinite();

	// Example for the GetValueImpl above

	// Noise is between -1 and 1
	//const TVoxelRange<v_flt> Height = TVoxelRange<v_flt>(-1, 1) * NoiseHeight;

	// Z can go from min to max
	//TVoxelRange<v_flt> Value = TVoxelRange<v_flt>(Bounds.Min.Z, Bounds.Max.Z) - Height;

	//Value /= 5;

	//return Value;
}

FVector FHybridWorldGeneratorInstance::GetUpVector(v_flt X, v_flt Y, v_flt Z) const
{
	// Used by spawners
	return FVector::UpVector;
}