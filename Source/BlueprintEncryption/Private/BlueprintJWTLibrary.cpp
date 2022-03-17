// Copyright 2022 Chris Ringenberg https://www.ringenberg.dev/

#include "BlueprintJWTLibrary.h"

#include "JsonObjectConverter.h"

#include "Kismet/KismetMathLibrary.h"

#include "ThirdParty/jwt-cpp/jwt.h"

FString UBlueprintJwtLibrary::K2_EncodeToken_RS(FString Audience, FString Issuer, FString Subject,
                                                FString PayloadClaimType, FString PayloadClaim, FString PublicKey,
                                                FString PublicKeyPassword,
                                                FString PrivateKey, FString PrivateKeyPassword, ERSAlgorithm Algorithm,
                                                int32 ExpiresAt)
{
	switch (Algorithm)
	{
		case ERSAlgorithm::rs256: return EncodeToken<jwt::algorithm::rs256>(Audience, Issuer, Subject, PayloadClaimType,
		                                                             PayloadClaim, PublicKey, PublicKeyPassword, PrivateKey,
		                                                             PrivateKeyPassword, ExpiresAt);
		case ERSAlgorithm::rs384: return EncodeToken<jwt::algorithm::rs384>(Audience, Issuer, Subject, PayloadClaimType,
		                                                             PayloadClaim, PublicKey, PublicKeyPassword, PrivateKey,
		                                                             PrivateKeyPassword, ExpiresAt);
		case ERSAlgorithm::rs512: return EncodeToken<jwt::algorithm::rs512>(Audience, Issuer, Subject, PayloadClaimType,
		                                                             PayloadClaim, PublicKey, PublicKeyPassword, PrivateKey,
		                                                             PrivateKeyPassword, ExpiresAt);
		default: return TEXT("ERROR");
	}
}


FString UBlueprintJwtLibrary::K2_EncodeToken_HS(FString Audience, FString Issuer, FString Subject,
                                                FString PayloadClaimType, FString PayloadClaim, FString Secret,
                                                EHSAlgorithm Algorithm, int32 ExpiresAt)
{
	switch (Algorithm)
	{
		case EHSAlgorithm::hs256: return EncodeToken<jwt::algorithm::hs256>(Audience, Issuer, Subject, PayloadClaimType, PayloadClaim, Secret, ExpiresAt);
		case EHSAlgorithm::hs384: return EncodeToken<jwt::algorithm::hs384>(Audience, Issuer, Subject, PayloadClaimType, PayloadClaim, Secret, ExpiresAt);;
		case EHSAlgorithm::hs512: return EncodeToken<jwt::algorithm::hs512>(Audience, Issuer, Subject, PayloadClaimType, PayloadClaim, Secret, ExpiresAt);;
		default: return TEXT("ERROR");
	}

}

TMap<FString, FString> UBlueprintJwtLibrary::K2_DecodeToken(const FString& JWT)
{
	if (JWT.IsEmpty())
	{
		return {};
	}

	const auto DecodedJWT = jwt::decode(ConvertFromFString(JWT));
	TMap<FString, FString> OutMap;
	OutMap.Reserve(DecodedJWT.get_payload_claims().size());
	
	for (const auto& Item : DecodedJWT.get_payload_claims())
	{
		OutMap.Add(Item.first.c_str(), Item.second.to_json().serialize().c_str());
	}

	return OutMap;
}

DEFINE_FUNCTION(UBlueprintJwtLibrary::execSerializeStructToString)
{
	Stack.StepCompiledIn<FProperty>(nullptr);
	FProperty* ValueProperty = Stack.MostRecentProperty;
	void* ValuePtr = Stack.MostRecentPropertyAddress;

	PARAM_PASSED_BY_REF(OutJsonString, FStrProperty, FString);

	P_FINISH;

	if (!ValueProperty || !ValuePtr)
	{
		const FBlueprintExceptionInfo ExceptionInfo(
			EBlueprintExceptionType::AccessViolation,
			NSLOCTEXT("BlueprintJWT", "SerializeStructToString_MissingInputProperty", "Failed to resolve the input parameter for SerializeStructToString.")
		);
		FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
	}

	bool bResult;
	FStructProperty* const StructProperty = CastField<FStructProperty>(ValueProperty);
	if (!StructProperty)
	{
		bResult = false;
		*StaticCast<bool*>(RESULT_PARAM) = bResult;
		return;
	}
	
	P_NATIVE_BEGIN
	bResult = FJsonObjectConverter::UStructToJsonObjectString(StructProperty->Struct, ValuePtr, OutJsonString);
	P_NATIVE_END

	*StaticCast<bool*>(RESULT_PARAM) = bResult;
}

jwt::algorithm::hs256 UBlueprintJwtLibrary::SignHS256(const FString& InKey)
{
	return jwt::algorithm::hs256(ConvertFromFString(InKey));
}

jwt::algorithm::hs384 UBlueprintJwtLibrary::SignHS384(const FString& InKey)
{
	return jwt::algorithm::hs384(ConvertFromFString(InKey));
}

jwt::algorithm::hs512 UBlueprintJwtLibrary::SignHS512(const FString& InKey)
{
	return jwt::algorithm::hs512(ConvertFromFString(InKey));
}

jwt::algorithm::rs256 UBlueprintJwtLibrary::SignRS256(const FString& InPublicKey, const FString& InPrivateKey,
                                                      const FString& InPublicKeyPassword,
                                                      const FString& InPrivateKeyPassword)
{
	return jwt::algorithm::rs256(ConvertFromFString(InPublicKey), ConvertFromFString(InPrivateKey),
	                             ConvertFromFString(InPublicKeyPassword), ConvertFromFString(InPrivateKeyPassword));
}

jwt::algorithm::rs384 UBlueprintJwtLibrary::SignRS384(const FString& InPublicKey, const FString& InPrivateKey,
                                                      const FString& InPublicKeyPassword,
                                                      const FString& InPrivateKeyPassword)
{
	return jwt::algorithm::rs384(ConvertFromFString(InPublicKey), ConvertFromFString(InPrivateKey),
	                             ConvertFromFString(InPublicKeyPassword), ConvertFromFString(InPrivateKeyPassword));
}

jwt::algorithm::rs512 UBlueprintJwtLibrary::SignRS512(const FString& InPublicKey, const FString& InPrivateKey,
                                                      const FString& InPublicKeyPassword,
                                                      const FString& InPrivateKeyPassword)
{
	return jwt::algorithm::rs512(ConvertFromFString(InPublicKey), ConvertFromFString(InPrivateKey),
	                             ConvertFromFString(InPublicKeyPassword), ConvertFromFString(InPrivateKeyPassword));
}

std::string UBlueprintJwtLibrary::ConvertFromFString(const FString& InS, const EStringEncoding& InEncoding)
{
	switch (InEncoding)
	{
	case EStringEncoding::UTF8: return TCHAR_TO_UTF8(*InS);
	case EStringEncoding::UTF16: break;
	case EStringEncoding::UTF32: break;
	default: ;
	}

	return {};
}
