// Copyright 2021 Griffin Page


#include "Fractal/Fold/FoldPlane.h"


FFoldPlane::FFoldPlane(FVector Normal)
{
	this->Normal = Normal;
}

void FFoldPlane::FoldPosition(FVector4 & Position, FVector Origin)
{
	FVector Position3D = FVector(Position);
	Position3D -= 2.0 * fmin(0.0, FVector::DotProduct(Position3D, Normal)) * Normal;
	Position = FVector4(Position3D, Position.W);
}
