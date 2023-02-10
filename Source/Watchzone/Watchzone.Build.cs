// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Watchzone : ModuleRules
{
	public Watchzone(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput","AIModule", "GameplayTasks","UMG" });
		PrivateDependencyModuleNames.AddRange(new string[] {"Slate","SlateCore"});
	}
}
