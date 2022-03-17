// Copyright 2022 Chris Ringenberg https://www.ringenberg.dev/

using UnrealBuildTool;

public class BlueprintEncryptionGraph : ModuleRules
{
	public BlueprintEncryptionGraph(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"BlueprintEncryption",
				"BlueprintGraph",
				"Core",
				"CoreUObject",
				"Engine",
				"GraphEditor",
				"Kismet",
				"KismetCompiler",
				"KismetWidgets",
				"Slate",
				"SlateCore",
			}
		);

		if (Target.bBuildEditor == true)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"AssetTools",
					"EditorStyle",
					"Projects",
					"PropertyEditor",
					"UnrealEd",
				}
			);
		}
	}
}