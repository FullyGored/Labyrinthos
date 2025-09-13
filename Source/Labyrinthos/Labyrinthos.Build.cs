// Copyright PixelWarriors Inc.

using UnrealBuildTool;

public class Labyrinthos : ModuleRules
{
    public Labyrinthos(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // Core modules required for basic functionality
        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",  // For modern input system
            "HeadMountedDisplay",  // VR support if needed
            "UMG",  // For UI widgets
            "Slate",  // For UI framework
            "SlateCore"  // Core UI functionality
        });

        // Private modules - used internally by your code
        PrivateDependencyModuleNames.AddRange(new string[]
        {
            // Add modules here that you use internally but don't expose in headers
            "GameplayTags",  // For gameplay tag system
            "AIModule",  // If you plan to add AI enemies
            "NavigationSystem",  // For pathfinding/navigation
            "CommonUI"  // For Lyra-style UI system (mentioned in your roadmap)
        });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your .uproject file with the Enabled attribute set to true

        // If you're using the PCG (Procedural Content Generation) system mentioned in your V2 plans
        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(new string[]
            {
                "UnrealEd",
                "ToolMenus",
                "EditorStyle",
                "EditorWidgets",
                "PCG"  // For your V2 procedural generation system
            });
        }
    }
}
