// Copyright 2021 Griffin Page

#include "SphericalWorldGenerator.h"
#include "FastNoise/VoxelFastNoise.inl"
#include "VoxelMaterialBuilder.h"
#include "VoxelWorld.h"

TVoxelSharedRef<FVoxelGeneratorInstance> USphericalWorldGenerator::GetInstance()
{
	return MakeVoxelShared<FSphericalWorldGeneratorInstance>(*this);
}

////////////////////////////////////////////////////////////////////////////s///

FSphericalWorldGeneratorInstance::FSphericalWorldGeneratorInstance(const USphericalWorldGenerator &MyGenerator)
	: Super(&MyGenerator)
	, TileSphere(MyGenerator.Center, MyGenerator.Radius, MyGenerator.ElevationAmplitude)
	, WorldSeed(MyGenerator.WorldSeed)
{
}

void FSphericalWorldGeneratorInstance::Init(const FVoxelGeneratorInit &InitStruct)
{
	// Assign UMachineLearningComponent to tiles for querying server
	if (InitStruct.World != nullptr)
	{
		UMachineLearningRemoteComponent *MachineLearningRemoteComponent = InitStruct.World->FindComponentByClass<UMachineLearningRemoteComponent>();
		TileSphere.Init(MachineLearningRemoteComponent, FNoiseManager::GetValueNoise1D(1, WorldSeed));
	}
	
	TArray<float> MaterialIndexPositions;
	MaterialIndexPositions.Add(0.3f); // Set index 0 position
	MaterialIndexPositions.Add(0.7f); // Set index 1 position
	TileSphere.SetMaterialIndexPositions(MaterialIndexPositions);
}

v_flt FSphericalWorldGeneratorInstance::GetValueImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack &Items) const
{
	return TileSphere.GetSignedDistance(FVector(X, Y, Z));
}

FVoxelMaterial FSphericalWorldGeneratorInstance::GetMaterialImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack &Items) const
{
	FVoxelMaterialBuilder Builder;

	// RGB
	//Builder.SetMaterialConfig(EVoxelMaterialConfig::RGB);
	//Builder.SetColor(TileSphere.ColorCode(FVector(X, Y, Z)));

	// Single index
	//Builder.SetMaterialConfig(EVoxelMaterialConfig::SingleIndex);
	//Builder.SetSingleIndex(0);



	// Multi index
	TArray<float> MaterialIndexValues = TileSphere.GetMaterialIndexValues(FVector(X, Y, Z));
	Builder.SetMaterialConfig(EVoxelMaterialConfig::MultiIndex);
	Builder.AddMultiIndex(0, MaterialIndexValues[0]);
	Builder.AddMultiIndex(1, MaterialIndexValues[1]);
	

	return Builder.Build();
}

TVoxelRange<v_flt> FSphericalWorldGeneratorInstance::GetValueRangeImpl(const FVoxelIntBox &Bounds, int32 LOD, const FVoxelItemStack &Items) const
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

FVector FSphericalWorldGeneratorInstance::GetUpVector(v_flt X, v_flt Y, v_flt Z) const
{
	// Used by spawners
	return FVector::UpVector;
}