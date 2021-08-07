// Fill out your copyright notice in the Description page of Project Settings.


#include "Fractal/Fold/FoldBox.h"

FFoldBox::FFoldBox(FVector Radius)
{
	this->Radius = Radius;
}

void FFoldBox::FoldPosition(FVector4 & Position, FVector Origin)
{
	FVector Position3D = FVector(Position);
	FVector Position3DTemp = Position3D;
	if (Position3D.X < -Radius.X) Position3D.X = -Radius.X;
	if (Position3D.X > Radius.X) Position3D.X = Radius.X;
	if (Position3D.Y < -Radius.Y) Position3D.Y = -Radius.Y;
	if (Position3D.Y > Radius.Y) Position3D.Y = Radius.Y;
	if (Position3D.Z < -Radius.Z) Position3D.Z = -Radius.Z;
	if (Position3D.Z > Radius.Z) Position3D.Z = Radius.Z;
	Position3D *= 2.0;
	Position3D -= Position3DTemp;
	Position = FVector4(Position3D, Position.W);
}
