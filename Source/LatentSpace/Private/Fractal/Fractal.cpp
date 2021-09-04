// Fill out your copyright notice in the Description page of Project Settings.


#include "Fractal/Fractal.h"

FFractal::FFractal(float pScale, float pDistanceOffset, int pIterations)
	: Scale(pScale)
	, DistanceOffset(pDistanceOffset)
	, Iterations(pIterations)
{
}

void FFractal::AddFold(IFold* Fold)
{
	Folds.Add(Fold);
}

void FFractal::SetBase(IBaseShape* Base)
{
	this->BaseShape = Base;
}

float FFractal::GetSignedDistance(FVector Origin) const
{
	Origin /= Scale;
	FVector4 Position = FVector4(Origin, 1.0);
	float d = INFINITY;
	for (int i = 0; i < Iterations; i++)
	{
		for (IFold* Fold : Folds)
		{
			Fold->FoldPosition(Position, Origin);
		}
	}
	float Distance = BaseShape->GetSignedDistance(Position);
	Distance -= DistanceOffset / Scale;

	return Distance;
}
