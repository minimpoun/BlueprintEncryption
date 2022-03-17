// Copyright 2022 Chris Ringenberg https://www.ringenberg.dev/

#pragma once

#include "Modules/ModuleManager.h"

class FBlueprintEncryptionModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
};
