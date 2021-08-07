// Fill out your copyright notice in the Description page of Project Settings.


#include "FractalWorldGenerator.h"
#include "FastNoise/VoxelFastNoise.inl"
#include "VoxelMaterialBuilder.h"

#include "Fractal/Fold/FoldBox.h"
#include "Fractal/Fold/FoldSphere.h"
#include "Fractal/Fold/FoldScaleOrigin.h"
#include "Fractal/Base/BaseBox.h"

TVoxelSharedRef<FVoxelGeneratorInstance> UFractalWorldGenerator::GetInstance()
{
	return MakeVoxelShared<FFractalWorldGeneratorInstance>(*this);
}

///////////////////////////////////////////////////////////////////////////////

FFractalWorldGeneratorInstance::FFractalWorldGeneratorInstance(const UFractalWorldGenerator& MyGenerator)
	: Super(&MyGenerator)
	, Scale(MyGenerator.Scale)
	, Iterations(MyGenerator.Iterations)
	, DistanceOffset(MyGenerator.DistanceOffset)
{
}

void FFractalWorldGeneratorInstance::Init(const FVoxelGeneratorInit& InitStruct)
{
	Fractal.AddFold(new FFoldBox(FVector(1.0, 1.0, 1.0)));
	Fractal.AddFold(new FFoldSphere(0.5, 1.0));
	Fractal.AddFold(new FFoldScaleOrigin(2.0));
	Fractal.SetBase(new FBaseBox(FVector(6, 6, 6), FVector(0, 0, 0), FVector(0, 0, 0)));
}

v_flt FFractalWorldGeneratorInstance::GetValueImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const
{
	X /= Scale;
	Y /= Scale;
	Z /= Scale;
	return Fractal.GetSignedDistance(FVector4(X, Y, Z, 1.0), 12) + (DistanceOffset / Scale);
}

FVoxelMaterial FFractalWorldGeneratorInstance::GetMaterialImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const
{
	FVoxelMaterialBuilder Builder;

	// RGB
	Builder.SetMaterialConfig(EVoxelMaterialConfig::RGB);
	Builder.SetColor(FColor::Red);

	// Single index
	//Builder.SetMaterialConfig(EVoxelMaterialConfig::SingleIndex);
	//Builder.SetSingleIndex(0); 

	// Multi index
	//Builder.SetMaterialConfig(EVoxelMaterialConfig::MultiIndex);
	//Builder.AddMultiIndex(0, 0.5f);
	//Builder.AddMultiIndex(1, 0.5f);

	return Builder.Build();
}

TVoxelRange<v_flt> FFractalWorldGeneratorInstance::GetValueRangeImpl(const FVoxelIntBox& Bounds, int32 LOD, const FVoxelItemStack& Items) const
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

FVector FFractalWorldGeneratorInstance::GetUpVector(v_flt X, v_flt Y, v_flt Z) const
{
	// Used by spawners
	return FVector::UpVector;
}