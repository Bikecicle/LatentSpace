// Copyright 2021 Griffin Page


#include "Kismet/GameplayStatics.h"
#include "Tools/LSToolExcavator.h"

ALSToolExcavator::ALSToolExcavator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	VoxelSphereTool = CreateDefaultSubobject<UVoxelSphereTool>(TEXT("VoxelSphereTool"));
	VoxelSphereTool->Alignment = EVoxelToolAlignment::Surface;
}

void ALSToolExcavator::TickTool(bool bUse)
{
	APlayerController* PlayerController = GetPawnOwner()->GetController<APlayerController>();
	TMap<FName, bool> Keys = UVoxelTool::MakeToolKeys(true);
	TMap<FName, float> Axes = UVoxelTool::MakeToolAxes(0.0f, 0.0f, 0.0f);

	ULocalPlayer* const LocalPlayer = PlayerController->GetLocalPlayer();
	auto* ViewportClient = LocalPlayer->ViewportClient;

	FVector2D Size;
	ViewportClient->GetViewportSize(Size);
	FVector2D ScreenPosition = Size / 2;
	
	APlayerCameraManager* PlayerCameraManager = PlayerController->PlayerCameraManager;

	FVoxelToolTickData TickData;
	TickData.MousePosition = ScreenPosition;
	TickData.CameraViewDirection = PlayerCameraManager->GetCameraRotation().Vector();
	TickData.bEdit = bUse;
	TickData.Keys = Keys;
	TickData.Axes = Axes;
	TickData.CollisionChannel = ECC_Visibility;

	const auto Deproject = [PlayerController = MakeWeakObjectPtr(PlayerController)](
		const FVector2D& InScreenPosition,
		FVector& OutWorldPosition,
		FVector& OutWorldDirection)
	{
		return UGameplayStatics::DeprojectScreenToWorld(PlayerController.Get(), InScreenPosition, OutWorldPosition, OutWorldDirection);
	};
	TickData.Init(Deproject);

	VoxelSphereTool->AdvancedTick(PlayerController->GetWorld(), TickData, {});
}
