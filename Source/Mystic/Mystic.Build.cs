// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Mystic : ModuleRules
{
	public Mystic(ReadOnlyTargetRules Target) : base(Target)
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
			"Mystic",
			"Mystic/Variant_Platforming",
			"Mystic/Variant_Platforming/Animation",
			"Mystic/Variant_Combat",
			"Mystic/Variant_Combat/AI",
			"Mystic/Variant_Combat/Animation",
			"Mystic/Variant_Combat/Gameplay",
			"Mystic/Variant_Combat/Interfaces",
			"Mystic/Variant_Combat/UI",
			"Mystic/Variant_SideScrolling",
			"Mystic/Variant_SideScrolling/AI",
			"Mystic/Variant_SideScrolling/Gameplay",
			"Mystic/Variant_SideScrolling/Interfaces",
			"Mystic/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
