// Copyright 2021 Griffin Page


#include "Tools/LSToolExcavator.h"

// Sets default values
ALSToolExcavator::ALSToolExcavator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALSToolExcavator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALSToolExcavator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALSToolExcavator::DoAction()
{
	SphereTool->DoEdit();
}
