// Copyright 2021 Griffin Page


#include "Fractal/Fold/FoldScaleTranslate.h"

FFoldScaleTranslate::FFoldScaleTranslate(float Scale, FVector Translation)
{
	this->Scale = Scale;
	this->Translation = Translation;
}

void FFoldScaleTranslate::FoldPosition(FVector4 & Position, FVector Origin)
{
	Position *= Scale;
	FVector Position3D = FVector(Position);
	Position3D += Translation;
	Position = FVector4(Position3D, Position.W);
}
