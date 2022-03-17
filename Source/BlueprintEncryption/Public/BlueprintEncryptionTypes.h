// Copyright 2022 Chris Ringenberg https://www.ringenberg.dev/

#pragma once

#include "CoreMinimal.h"

#include "BlueprintEncryptionTypes.generated.h"

UENUM(BlueprintType)
enum class ERSAlgorithm : uint8
{
	rs256,
	rs384,
	rs512
};

UENUM(BlueprintType)
enum class EHSAlgorithm : uint8
{
	hs256,
	hs384,
	hs512
};

UENUM(BlueprintType)
enum class EStringEncoding : uint8
{
	UTF8 UMETA(DisplayName="UTF-8"),
	UTF16 UMETA(DisplayName="UTF-16"),
	UTF32 UMETA(DisplayName="UTF-32"),
};