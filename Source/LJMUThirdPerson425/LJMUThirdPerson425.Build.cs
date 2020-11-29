// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LJMUThirdPerson425 : ModuleRules
{
	public LJMUThirdPerson425(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule" });
	}
}
