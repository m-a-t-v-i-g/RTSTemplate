// Real Time Strategy C++ template by matvig.

using UnrealBuildTool;

public class RTSTemplate : ModuleRules
{
	public RTSTemplate(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "EnhancedInput"});
		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		PublicIncludePaths.AddRange(new string[] { "RTSTemplate/Public/" });
		PrivateIncludePaths.AddRange(new string[] { "RTSTemplate/Private/" });
	}
}
