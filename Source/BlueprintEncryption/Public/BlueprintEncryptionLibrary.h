// Copyright 2022 Chris Ringenberg https://www.ringenberg.dev/

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <string>

#include "BlueprintEncryptionLibrary.generated.h"

/**
 * Blueprint Library that allows you to create hashes in blueprint
 */
UCLASS(BlueprintType)
class BLUEPRINTENCRYPTION_API UBlueprintEncryptionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Βlueprint Encryption | Hashing")
	static FString SHA256StringHash(const FString& Data);

	UFUNCTION(BlueprintCallable, Category = "Βlueprint Encryption | Hashing")
	static FString SHA256BinaryHash(const TArray<uint8>& BinaryData);

	UFUNCTION(BlueprintCallable, Category = "Βlueprint Encryption | Hashing")
	static FString SHA3StringHash(const FString& Data);

	UFUNCTION(BlueprintCallable, Category = "Βlueprint Encryption | Hashing")
	static FString SHA3BinaryHash(const TArray<uint8>& BinaryData);

	UFUNCTION(BlueprintCallable, Category = "Βlueprint Encryption | Hashing")
	static FString SHA1StringHash(const FString& Data);

	UFUNCTION(BlueprintCallable, Category = "Βlueprint Encryption | Hashing")
	static FString SHA1BinaryHash(const TArray<uint8>& BinaryData);

	UFUNCTION(BlueprintCallable, Category = "Βlueprint Encryption | Hashing")
	static FString MD5StringHash(const FString& Data);

	UFUNCTION(BlueprintCallable, Category = "Βlueprint Encryption | Hashing")
	static FString MD5BinaryHash(const TArray<uint8>& BinaryData);

	UFUNCTION(BlueprintCallable, Category = "Βlueprint Encryption | Hashing")
	static FString KeccakStringHash(const FString& Data);

	UFUNCTION(BlueprintCallable, Category = "Βlueprint Encryption | Hashing")
	static FString CRC32StringHash(const FString& Data);

private:

	static UE_NODISCARD std::string ConvertFromFString(const FString& InS);
};
