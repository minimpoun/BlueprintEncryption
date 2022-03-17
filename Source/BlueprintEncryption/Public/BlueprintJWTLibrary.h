// Copyright 2022 Chris Ringenberg https://www.ringenberg.dev/

#pragma once

#include "CoreMinimal.h"
#include "BlueprintEncryptionTypes.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include <string>

#include "jwt.h"
#include "BlueprintJWTLibrary.generated.h"

/**
 * Blueprint Library for handling JWTs
 */
UCLASS(BlueprintType)
class BLUEPRINTENCRYPTION_API UBlueprintJwtLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// Encodes a JWT using a asymmetric algorithm. Meaning it uses both a public and private key
	UFUNCTION(BlueprintCallable, Category = "Blueprint Encryption | JWT", meta = (DisplayName = "Encode JWT using sha"))
	static FString K2_EncodeToken_RS(FString Audience, FString Issuer, FString Subject, FString PayloadClaimType = TEXT("scope"),
	                                 FString PayloadClaim = TEXT(""), FString PublicKey = TEXT(""), FString PublicKeyPassword = TEXT(""),
	                                 FString PrivateKey = TEXT(""), FString PrivateKeyPassword = TEXT(""),
	                                 ERSAlgorithm Algorithm = ERSAlgorithm::rs256, int32 ExpiresAt = 3600);

	// Encodes a JWT using a symmetric algorithm. Meaning it uses a shared secret 
	UFUNCTION(BlueprintCallable, Category = "Blueprint Encryption | JWT", meta = (DisplayName = "Encode JWT using HMAC sha"))
	static FString K2_EncodeToken_HS(FString Audience, FString Issuer, FString Subject, FString PayloadClaimType = TEXT("scope"),
	                                 FString PayloadClaim = TEXT(""), FString Secret = TEXT(""),
	                                 EHSAlgorithm Algorithm = EHSAlgorithm::hs256,
	                                 int32 ExpiresAt = 3600);

	UFUNCTION(BlueprintCallable, Category = "Blueprint Encryption | JWT", meta = (DisplayName = "Decode JWT"))
	static TMap<FString, FString> K2_DecodeToken(const FString& JWT);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, CustomThunk, Category = "Blueprint Encryption | Utils", meta = (CustomStructureParam = "Struct", AutoCreateRefTerm = "Struct"))
	static bool SerializeStructToString(const int32& Struct, FString& OutJsonString);
	DECLARE_FUNCTION(execSerializeStructToString);

private:

	static UE_NODISCARD jwt::algorithm::hs256 SignHS256(const FString& InKey);
	static UE_NODISCARD jwt::algorithm::hs384 SignHS384(const FString& InKey);
	static UE_NODISCARD jwt::algorithm::hs512 SignHS512(const FString& InKey);

	static UE_NODISCARD jwt::algorithm::rs256 SignRS256(const FString& InPublicKey, const FString& InPrivateKey,
	                                                    const FString& InPublicKeyPassword,
	                                                    const FString& InPrivateKeyPassword);
	static UE_NODISCARD jwt::algorithm::rs384 SignRS384(const FString& InPublicKey, const FString& InPrivateKey,
	                                                    const FString& InPublicKeyPassword,
	                                                    const FString& InPrivateKeyPassword);
	static UE_NODISCARD jwt::algorithm::rs512 SignRS512(const FString& InPublicKey, const FString& InPrivateKey,
	                                                    const FString& InPublicKeyPassword,
	                                                    const FString& InPrivateKeyPassword);

	static UE_NODISCARD std::string ConvertFromFString(const FString& InS,
	                                                   const EStringEncoding& InEncoding = EStringEncoding::UTF8);

	/**
 	* @brief 
 	* @tparam AlgoType the algo we use. Can be rs256, rs384, rs512 
 	* @param Audience 
 	* @param Issuer 
 	* @param Subject 
 	* @param PayloadClaimType 
 	* @param PayloadClaim 
 	* @param PublicKey 
 	* @param PublicKeyPassword 
 	* @param PrivateKey 
 	* @param PrivateKeyPassword 
 	* @param ExpiresAt 
 	* @return 
 	*/
	template <typename AlgoType>
	static UE_NODISCARD FString EncodeToken(FString Audience, FString Issuer, FString Subject, FString PayloadClaimType,
	                                        FString PayloadClaim, FString PublicKey, FString PublicKeyPassword,
	                                        FString PrivateKey, FString PrivateKeyPassword, int32 ExpiresAt = 3600);
	/**
	 * @brief 
	 * @tparam 
	 * @param Audience 
	 * @param Issuer 
	 * @param Subject 
	 * @param PayloadClaimType 
	 * @param PayloadClaim 
	 * @param Signature 
	 * @param ExpiresAt 
	 * @return 
	 */
	template <typename AlgoType>
	static UE_NODISCARD FString EncodeToken(FString Audience, FString Issuer, FString Subject, FString PayloadClaimType,
	                                        FString PayloadClaim, FString Signature, int32 ExpiresAt = 3600);
};


template <typename AlgoType>
auto UBlueprintJwtLibrary::EncodeToken(FString Audience, FString Issuer, FString Subject,
                                       FString PayloadClaimType, FString PayloadClaim, FString PublicKey,
                                       FString PublicKeyPassword, FString PrivateKey, FString
                                       PrivateKeyPassword, int32 ExpiresAt) -> FString
{
	checkNoEntry();
	return {};
}

template <>
inline auto UBlueprintJwtLibrary::EncodeToken<jwt::algorithm::rs256>(const FString Audience, const FString Issuer,
                                                                     const FString Subject,
                                                                     const FString PayloadClaimType,
                                                                     const FString PayloadClaim,
                                                                     const FString PublicKey,
                                                                     const FString PublicKeyPassword,
                                                                     const FString PrivateKey,
                                                                     const FString PrivateKeyPassword,
                                                                     const int32 ExpiresAt) -> FString
{
	const auto Now = std::chrono::system_clock::now();

	const auto Token = jwt::create()
	                   .set_type(ConvertFromFString(TEXT("JWT")))
	                   .set_audience(ConvertFromFString(Audience))
	                   .set_algorithm(ConvertFromFString(TEXT("RS256")))
	                   .set_issued_at(Now)
	                   .set_expires_at(Now + std::chrono::seconds{ExpiresAt})
	                   .set_issuer(ConvertFromFString(Issuer))
	                   .set_subject(ConvertFromFString(Subject))
	                   .set_payload_claim(ConvertFromFString(PayloadClaimType),
	                                      jwt::claim(std::string(ConvertFromFString(PayloadClaim))))
	                   .sign(SignRS256(PublicKey, PrivateKey, PublicKeyPassword, PrivateKeyPassword));

	return Token.c_str();
}

template <>
inline auto UBlueprintJwtLibrary::EncodeToken<jwt::algorithm::rs384>(const FString Audience, const FString Issuer,
                                                                     const FString Subject,
                                                                     const FString PayloadClaimType,
                                                                     const FString PayloadClaim,
                                                                     const FString PublicKey,
                                                                     const FString PublicKeyPassword,
                                                                     const FString PrivateKey,
                                                                     const FString PrivateKeyPassword,
                                                                     const int32 ExpiresAt) -> FString
{
	const auto Now = std::chrono::system_clock::now();

	const auto Token = jwt::create()
	                   .set_type(ConvertFromFString(TEXT("JWT")))
	                   .set_audience(ConvertFromFString(Audience))
	                   .set_algorithm(ConvertFromFString(TEXT("RS384")))
	                   .set_issued_at(Now)
	                   .set_expires_at(Now + std::chrono::seconds{ExpiresAt})
	                   .set_issuer(ConvertFromFString(Issuer))
	                   .set_subject(ConvertFromFString(Subject))
	                   .set_payload_claim(ConvertFromFString(PayloadClaimType),
	                                      jwt::claim(std::string(ConvertFromFString(PayloadClaim))))
	                   .sign(SignRS384(PublicKey, PrivateKey, PublicKeyPassword, PrivateKeyPassword));

	return Token.c_str();
}

template <>
inline auto UBlueprintJwtLibrary::EncodeToken<jwt::algorithm::rs512>(const FString Audience, const FString Issuer,
                                                                     const FString Subject,
                                                                     const FString PayloadClaimType,
                                                                     const FString PayloadClaim,
                                                                     const FString PublicKey,
                                                                     const FString PublicKeyPassword,
                                                                     const FString PrivateKey,
                                                                     const FString PrivateKeyPassword,
                                                                     const int32 ExpiresAt) -> FString
{
	const auto Now = std::chrono::system_clock::now();

	const auto Token = jwt::create()
	                   .set_type(ConvertFromFString(TEXT("JWT")))
	                   .set_audience(ConvertFromFString(Audience))
	                   .set_algorithm(ConvertFromFString(TEXT("RS512")))
	                   .set_issued_at(Now)
	                   .set_expires_at(Now + std::chrono::seconds{ExpiresAt})
	                   .set_issuer(ConvertFromFString(Issuer))
	                   .set_subject(ConvertFromFString(Subject))
	                   .set_payload_claim(ConvertFromFString(PayloadClaimType),
	                                      jwt::claim(std::string(ConvertFromFString(PayloadClaim))))
	                   .sign(SignRS512(PublicKey, PrivateKey, PublicKeyPassword, PrivateKeyPassword));

	return Token.c_str();
}


template <typename AlgoType>
FString UBlueprintJwtLibrary::EncodeToken(const FString Audience, const FString Issuer,
                                          const FString Subject, const FString PayloadClaimType,
                                          const FString PayloadClaim, FString Signature,
                                          const int32 ExpiresAt)
{
	checkNoEntry();
	return {};
}

template <>
inline auto UBlueprintJwtLibrary::EncodeToken<jwt::algorithm::hs256>(const FString Audience, const FString Issuer,
                                                                     const FString Subject,
                                                                     const FString PayloadClaimType,
                                                                     const FString PayloadClaim, FString Signature,
                                                                     const int32 ExpiresAt) -> FString
{
	const auto Now = std::chrono::system_clock::now();

	const auto Token = jwt::create()
	                   .set_type(ConvertFromFString(TEXT("JWT")))
	                   .set_audience(ConvertFromFString(Audience))
	                   .set_algorithm(ConvertFromFString(TEXT("HS256")))
	                   .set_issued_at(Now)
	                   .set_expires_at(Now + std::chrono::seconds{ExpiresAt})
	                   .set_issuer(ConvertFromFString(Issuer))
	                   .set_subject(ConvertFromFString(Subject))
	                   .set_payload_claim(ConvertFromFString(PayloadClaimType),
	                                      jwt::claim(std::string(ConvertFromFString(PayloadClaim))))
	                   .sign(SignHS256(Signature));

	return Token.c_str();
}

template <>
inline auto UBlueprintJwtLibrary::EncodeToken<jwt::algorithm::hs384>(const FString Audience, const FString Issuer,
																	 const FString Subject,
																	 const FString PayloadClaimType,
																	 const FString PayloadClaim, FString Signature,
																	 const int32 ExpiresAt) -> FString
{
	const auto Now = std::chrono::system_clock::now();

	const auto Token = jwt::create()
					   .set_type(ConvertFromFString(TEXT("JWT")))
					   .set_audience(ConvertFromFString(Audience))
					   .set_algorithm(ConvertFromFString(TEXT("HS384")))
					   .set_issued_at(Now)
					   .set_expires_at(Now + std::chrono::seconds{ExpiresAt})
					   .set_issuer(ConvertFromFString(Issuer))
					   .set_subject(ConvertFromFString(Subject))
					   .set_payload_claim(ConvertFromFString(PayloadClaimType),
										  jwt::claim(std::string(ConvertFromFString(PayloadClaim))))
					   .sign(SignHS384(Signature));

	return Token.c_str();
}

template <>
inline auto UBlueprintJwtLibrary::EncodeToken<jwt::algorithm::hs512>(const FString Audience, const FString Issuer,
																	 const FString Subject,
																	 const FString PayloadClaimType,
																	 const FString PayloadClaim, FString Signature,
																	 const int32 ExpiresAt) -> FString
{
	const auto Now = std::chrono::system_clock::now();

	const auto Token = jwt::create()
					   .set_type(ConvertFromFString(TEXT("JWT")))
					   .set_audience(ConvertFromFString(Audience))
					   .set_algorithm(ConvertFromFString(TEXT("HS512")))
					   .set_issued_at(Now)
					   .set_expires_at(Now + std::chrono::seconds{ExpiresAt})
					   .set_issuer(ConvertFromFString(Issuer))
					   .set_subject(ConvertFromFString(Subject))
					   .set_payload_claim(ConvertFromFString(PayloadClaimType),
										  jwt::claim(std::string(ConvertFromFString(PayloadClaim))))
					   .sign(SignHS512(Signature));

	return Token.c_str();
}
