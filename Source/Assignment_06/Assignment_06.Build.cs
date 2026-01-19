// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Assignment_06 : ModuleRules
{
	public Assignment_06(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Assignment_06",
			"Assignment_06/Variant_Platforming",
			"Assignment_06/Variant_Platforming/Animation",
			"Assignment_06/Variant_Combat",
			"Assignment_06/Variant_Combat/AI",
			"Assignment_06/Variant_Combat/Animation",
			"Assignment_06/Variant_Combat/Gameplay",
			"Assignment_06/Variant_Combat/Interfaces",
			"Assignment_06/Variant_Combat/UI",
			"Assignment_06/Variant_SideScrolling",
			"Assignment_06/Variant_SideScrolling/AI",
			"Assignment_06/Variant_SideScrolling/Gameplay",
			"Assignment_06/Variant_SideScrolling/Interfaces",
			"Assignment_06/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
