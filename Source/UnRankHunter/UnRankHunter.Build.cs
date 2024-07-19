// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class UnRankHunter : ModuleRules
{
	public UnRankHunter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "UnRankHunter/Public/AJH", "UnRankHunter/Public/JSH", "UnRankHunter/Public/KBH", "UnRankHunter/Public/KYG", "UnRankHunter/Public/YYJ" });

		// AJH
		PublicIncludePaths.AddRange(new string[] {
			"UnRankHunter/Public/AJH/Interface", "UnRankHunter/Public/AJH/Subsystem", "UnRankHunter/Public/AJH/Enemy_Common",
			"UnRankHunter/Public/AJH/Enemy_Common/Robot", "UnRankHunter/Public/AJH/Enemy_Common/Robot/Melee", "UnRankHunter/Public/AJH/Enemy_Common/Robot/Range", "UnRankHunter/Public/AJH/Enemy_Common/Robot/Elite" });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AnimGraphRuntime", "AIModule" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
