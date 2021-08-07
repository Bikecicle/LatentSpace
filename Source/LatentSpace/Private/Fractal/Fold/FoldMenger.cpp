// Fill out your copyright notice in the Description page of Project Settings.


#include "Fractal/Fold/FoldMenger.h"

FFoldMenger::FFoldMenger()
{
}

void FFoldMenger::FoldPosition(FVector4 & Position, FVector Origin)
{
	if (Position.X < Position.Y)
	{
		float Temp = Position.X;
		Position.X = Position.Y;
		Position.Y = Temp;
	}
	if (Position.X < Position.Z)
	{
		float Temp = Position.X;
		Position.X = Position.Y;
		Position.Y = Temp;
	}
	if (Position.Y < Position.Z)
	{
		float Temp = Position.Y;
		Position.Y = Position.Z;
		Position.Z = Temp;
	}
}
