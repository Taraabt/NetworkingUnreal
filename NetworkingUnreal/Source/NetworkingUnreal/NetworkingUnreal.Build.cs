// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NetworkingUnreal : ModuleRules
{
	public NetworkingUnreal(ReadOnlyTargetRules Target) : base(Target)
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
			"NetworkingUnreal",
			"NetworkingUnreal/Variant_Platforming",
			"NetworkingUnreal/Variant_Platforming/Animation",
			"NetworkingUnreal/Variant_Coop",
			"NetworkingUnreal/Variant_Combat",
			"NetworkingUnreal/Variant_Combat/AI",
			"NetworkingUnreal/Variant_Combat/Animation",
			"NetworkingUnreal/Variant_Combat/Gameplay",
			"NetworkingUnreal/Variant_Combat/Interfaces",
			"NetworkingUnreal/Variant_Combat/UI",
			"NetworkingUnreal/Variant_SideScrolling",
			"NetworkingUnreal/Variant_SideScrolling/AI",
			"NetworkingUnreal/Variant_SideScrolling/Gameplay",
			"NetworkingUnreal/Variant_SideScrolling/Interfaces",
			"NetworkingUnreal/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
