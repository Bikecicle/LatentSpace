// Copyright 2021 Griffin Page


#include "Fractal/Fold/FoldAbs.h"

FFoldAbs::FFoldAbs(FVector Center)
{
	this->Center = Center;
}

void FFoldAbs::FoldPosition(FVector4 & Position, FVector Origin)
{
	FVector Position3D = FVector(Position);
	Position3D -= Center;
	Position3D = Position3D.GetAbs();
	Position3D += Center;
	Position = FVector4(Position3D, Position.W);
}
