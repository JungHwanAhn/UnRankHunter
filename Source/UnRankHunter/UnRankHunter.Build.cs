// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class UnRankHunter : ModuleRules
{
	public UnRankHunter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "UnRankHunter/Public/AJH", "UnRankHunter/Public/JSH", "UnRankHunter/Public/KBH", "UnRankHunter/Public/KYG", "UnRankHunter/Public/YYJ" });

		// AJH_Common
		PublicIncludePaths.AddRange(new string[] {
			"UnRankHunter/Public/AJH/Interface", "UnRankHunter/Public/AJH/Subsystem", "UnRankHunter/Public/AJH/Enemy_Common", "UnRankHunter/Public/AJH/Enemy_Common/AIController",
            "UnRankHunter/Public/AJH/Enemy_Common/Robot", "UnRankHunter/Public/AJH/Enemy_Common/Robot/Melee", "UnRankHunter/Public/AJH/Enemy_Common/Robot/Range", "UnRankHunter/Public/AJH/Enemy_Common/Robot/Elite",
            "UnRankHunter/Public/AJH/Enemy_Common/Skeleton", "UnRankHunter/Public/AJH/Enemy_Common/Skeleton/Melee", "UnRankHunter/Public/AJH/Enemy_Common/Skeleton/Range", "UnRankHunter/Public/AJH/Enemy_Common/Skeleton/Elite" });

        // AJH_Boss
        PublicIncludePaths.AddRange(new string[] {
            "UnRankHunter/Public/AJH/Enemy_Boss", "UnRankHunter/Public/AJH/Enemy_Boss/PublicBehaviorTree", "UnRankHunter/Public/AJH/Enemy_Boss/Robot", "UnRankHunter/Public/AJH/Enemy_Boss/AIController",
            "UnRankHunter/Public/AJH/Enemy_Boss/PublicBehaviorTree/BTTask",
            "UnRankHunter/Public/AJH/Enemy_Boss/Robot/BehaviorTree", "UnRankHunter/Public/AJH/Enemy_Boss/Robot/BehaviorTree/BTTask", "UnRankHunter/Public/AJH/Enemy_Boss/Robot/BehaviorTree/BTService" });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AnimGraphRuntime", "AIModule", "NavigationSystem", "Niagara", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
