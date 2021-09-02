// Fill out your copyright notice in the Description page of Project Settings.

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
	, TileSphere(MyGenerator.Center, MyGenerator.Radius, MyGenerator.ElevationAmplitude, MyGenerator.Seed)
{
}

void FSphericalWorldGeneratorInstance::Init(const FVoxelGeneratorInit &InitStruct)
{
	if (InitStruct.World != nullptr)
	{
		UMachineLearningRemoteComponent *MachineLearningRemoteComponent = InitStruct.World->FindComponentByClass<UMachineLearningRemoteComponent>();
		TileSphere.Init(MachineLearningRemoteComponent);
	}
}

v_flt FSphericalWorldGeneratorInstance::GetValueImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack &Items) const
{
	return TileSphere.GetSignedDistance(FVector4(X, Y, Z, 1.0));
}

FVoxelMaterial FSphericalWorldGeneratorInstance::GetMaterialImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack &Items) const
{
	FVoxelMaterialBuilder Builder;

	// RGB
	Builder.SetMaterialConfig(EVoxelMaterialConfig::RGB);
	Builder.SetColor(TileSphere.ColorCode(FVector4(X, Y, Z, 1.0)));

	// Single index
	//Builder.SetMaterialConfig(EVoxelMaterialConfig::SingleIndex);
	//Builder.SetSingleIndex(0);

	// Multi index
	//Builder.SetMaterialConfig(EVoxelMaterialConfig::MultiIndex);
	//Builder.AddMultiIndex(0, 0.5f);
	//Builder.AddMultiIndex(1, 0.5f);

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