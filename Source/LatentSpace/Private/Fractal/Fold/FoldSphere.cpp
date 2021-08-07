// Fill out your copyright notice in the Description page of Project Settings.


#include "Fractal/Fold/FoldSphere.h"

FFoldSphere::FFoldSphere(float RMin, float RMax)
{
	this->RMin = RMin;
	this->RMax = RMax;
}

void FFoldSphere::FoldPosition(FVector4 & Position, FVector Origin)
{
	FVector Position3D = FVector(Position);
	float R2 = FVector::DotProduct(Position3D, Position3D);
	Position *= fmax(RMax / fmax(RMin, R2), 1.0);
}