// Copyright 2022 Chris Ringenberg https://www.ringenberg.dev/

#include "BlueprintEncryptionLibrary.h"

#include "Public/crc32.h"
#include "Public/keccak.h"
#include "Public/sha1.h"
#include "Public/sha3.h"
#include "Public/sha256.h"
#include "Public/md5.h"

FString UBlueprintEncryptionLibrary::SHA256StringHash(const FString& Data)
{
	SHA256 SHA256;
	return SHA256(ConvertFromFString(Data)).c_str();
}


FString UBlueprintEncryptionLibrary::SHA256BinaryHash(const TArray<uint8>& BinaryData)
{
	SHA256 SHA256;
	return SHA256(BinaryData.GetData(), BinaryData.Num()).c_str();
}


FString UBlueprintEncryptionLibrary::SHA3StringHash(const FString& Data)
{
	SHA3 SHA3;
	return SHA3(ConvertFromFString(Data)).c_str();
}

FString UBlueprintEncryptionLibrary::SHA3BinaryHash(const TArray<uint8>& BinaryData)
{
	SHA3 SHA3;
	return SHA3(BinaryData.GetData(), BinaryData.Num()).c_str();
}

FString UBlueprintEncryptionLibrary::SHA1StringHash(const FString& Data)
{
	SHA1 SHA1;
	return SHA1(ConvertFromFString(Data)).c_str();
}

FString UBlueprintEncryptionLibrary::SHA1BinaryHash(const TArray<uint8>& BinaryData)
{
	SHA1 SHA1;
	return SHA1(BinaryData.GetData(), BinaryData.Num()).c_str();
}

FString UBlueprintEncryptionLibrary::MD5StringHash(const FString& Data)
{
	MD5 MD5;
	return MD5(ConvertFromFString(Data)).c_str();
}

FString UBlueprintEncryptionLibrary::MD5BinaryHash(const TArray<uint8>& BinaryData)
{
	MD5 MD5;
	return MD5(BinaryData.GetData(), BinaryData.Num()).c_str();
}

FString UBlueprintEncryptionLibrary::KeccakStringHash(const FString& Data)
{
	Keccak Keccak;
	return Keccak(ConvertFromFString(Data)).c_str();
}

FString UBlueprintEncryptionLibrary::CRC32StringHash(const FString& Data)
{
	CRC32 CRC32;
	return CRC32(ConvertFromFString(Data)).c_str();
}

std::string UBlueprintEncryptionLibrary::ConvertFromFString(const FString& InS)
{
	return TCHAR_TO_UTF8(*InS);
}
