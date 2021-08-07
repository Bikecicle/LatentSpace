// Fill out your copyright notice in the Description page of Project Settings.


#include "Fractal/Fold/FoldSierpinski.h"

FFoldSierpinski::FFoldSierpinski()
{
}

void FFoldSierpinski::FoldPosition(FVector4 & Position, FVector Origin)
{
	if (Position.X + Position.Y < 0.0)
	{
		float Temp = Position.X;
		Position.X = -Position.Y;
		Position.Y = -Temp;
	}
	if (Position.X + Position.Z < 0.0)
	{
		float Temp = Position.X;
		Position.X = -Position.Z;
		Position.Z = -Temp;
	}
	if (Position.Y + Position.Z < 0.0)
	{
		float Temp = Position.Y;
		Position.Y = -Position.Z;
		Position.Z = -Temp;
	}
}
