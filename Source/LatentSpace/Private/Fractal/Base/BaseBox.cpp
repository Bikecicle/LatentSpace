// Fill out your copyright notice in the Description page of Project Settings.


#include "Fractal/Base/BaseBox.h"

FBaseBox::FBaseBox(FVector Shape, FVector Center, FVector Color)
{
	this->Shape = Shape;
	this->Center = Center;
	this->Color = Color;
}

float FBaseBox::GetSignedDistance(FVector4 Position)
{
	FVector Position3D = FVector(Position);
	Position3D -= Center;
	Position3D = Position3D.GetAbs() - Shape;
	return (fmin(Position3D.GetMax(), 0.0) + Position3D.ComponentMax(FVector(0, 0, 0)).Size()) / Position.W;
}