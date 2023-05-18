// Real Time Strategy C++ template by matvig.

using UnrealBuildTool;
using System.Collections.Generic;

public class RTSTemplateEditorTarget : TargetRules
{
	public RTSTemplateEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "RTSTemplate" } );
	}
}
