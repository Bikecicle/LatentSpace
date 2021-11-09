// Copyright 2021 Griffin Page

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LSTool.generated.h"

UCLASS(Abstract)
class LATENTSPACE_API ALSTool : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ALSTool();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void DoAction();

};
