// Fill out your copyright notice in the Description page of Project Settings.


#include "Fractal/Base/BaseSphere.h"

FBaseSphere::FBaseSphere(float Radius, FVector Center, FVector Color)
{
	this->Radius = Radius;
	this->Center = Center;
	this->Color = Color;
}

float FBaseSphere::GetSignedDistance(FVector4 Position)
{
	FVector Position3D = FVector(Position);
	Position3D -= Center;
	return (Position3D.Size() - Radius) / Position.W;
}
