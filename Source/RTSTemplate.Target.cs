// Real Time Strategy C++ template by matvig.

using UnrealBuildTool;
using System.Collections.Generic;

public class RTSTemplateTarget : TargetRules
{
	public RTSTemplateTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "RTSTemplate" } );
	}
}
