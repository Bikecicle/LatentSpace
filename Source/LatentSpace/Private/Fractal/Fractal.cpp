// Fill out your copyright notice in the Description page of Project Settings.


#include "Fractal/Fractal.h"

FFractal::FFractal()
{
}

void FFractal::AddFold(IFold* Fold)
{
	Folds.push_back(Fold);
}

void FFractal::SetBase(IBaseShape* Base)
{
	this->BaseShape = Base;
}

float FFractal::GetSignedDistance(FVector Origin, int Iterations) const
{
	FVector4 Position = FVector4(Origin, 1.0);
	float d = INFINITY;
	for (int i = 0; i < Iterations; i++)
	{
		for (IFold* Fold : Folds)
		{
			Fold->FoldPosition(Position, Origin);
		}
	}
	return BaseShape->GetSignedDistance(Position);
}
