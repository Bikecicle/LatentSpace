// Copyright 2021 Griffin Page


#include "Fractal/Fold/FoldScaleOrigin.h"

FFoldScaleOrigin::FFoldScaleOrigin(float Scale)
{
	this->Scale = Scale;
}

void FFoldScaleOrigin::FoldPosition(FVector4 & Position, FVector Origin)
{
	Position *= Scale;
	FVector Position3D = FVector(Position);
	Position3D += Origin;
	Position = FVector4(Position3D, Position.W);
}