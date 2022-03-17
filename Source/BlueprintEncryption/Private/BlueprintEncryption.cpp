// Copyright 2022 Chris Ringenberg https://www.ringenberg.dev/

#include "BlueprintEncryption.h"
#include "Modules/ModuleManager.h"


#define LOCTEXT_NAMESPACE "FBlueprintEncryptionModule"

void FBlueprintEncryptionModule::StartupModule()
{
}

void FBlueprintEncryptionModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBlueprintEncryptionModule, BlueprintEncryption)
