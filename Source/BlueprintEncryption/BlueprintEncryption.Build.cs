// Copyright 2022 Chris Ringenberg https://www.ringenberg.dev/

using UnrealBuildTool;
using System.IO;

public class BlueprintEncryption : ModuleRules
{
	private string ThirdPartyPath
	{
		get { return Path.Combine(PluginDirectory,"Source/ThirdParty"); }
	}

	public BlueprintEncryption(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnableUndefinedIdentifierWarnings = false;
		bEnableExceptions = true;
		bEnableObjCExceptions = true;
		OptimizeCode = CodeOptimization.InShippingBuildsOnly;

		PublicIncludePaths.AddRange(
			new string[]
			{
				Path.Combine(ThirdPartyPath),
				Path.Combine(ThirdPartyPath, "jwt-cpp"),
				Path.Combine(ThirdPartyPath, "hash-library")
			}
		);
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Engine",
				"Core",
				"CoreUObject",
				"Slate",
				"OpenSSL"
			}
		);
		
		PrivateDependencyModuleNames.AddRange(new string[] { "JsonUtilities" });
		PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "hash-library", "HashLibrary.lib"));
	}
}
