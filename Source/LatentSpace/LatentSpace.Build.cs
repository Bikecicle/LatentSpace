// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LatentSpace : ModuleRules
{
	public LatentSpace(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"Voxel",
				"HeadMountedDisplay",
				"MachineLearningRemote",
				"SocketIOClient",
				"SocketIOLib",
				"Json",
				"SIOJson",
				"CoreUtility",
				"MachineLearningBase",
				"MLProcess"
			}
			);
	}
}
