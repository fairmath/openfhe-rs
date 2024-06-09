#pragma once

#include "bits/stringfwd.h"

#include "SerialMode.h"

namespace openfhe
{

class CiphertextDCRTPoly;
class CryptoContextDCRTPoly;
class PublicKeyDCRTPoly;

// Ciphertext
[[nodiscard]] bool DCRTPolyDeserializeCiphertextFromFile(const std::string& ciphertextLocation,
    CiphertextDCRTPoly& ciphertext, const SerialMode serialMode);
[[nodiscard]] bool DCRTPolySerializeCiphertextToFile(const std::string& ciphertextLocation,
    const CiphertextDCRTPoly& ciphertext, const SerialMode serialMode);

// CryptoContext
[[nodiscard]] bool DCRTPolyDeserializeCryptoContextFromFile(const std::string& ccLocation,
    CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);
[[nodiscard]] bool DCRTPolySerializeCryptoContextToFile(const std::string& ccLocation,
    const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);

// EvalAutomorphismKey
[[nodiscard]] bool DCRTPolyDeserializeEvalMultKeyFromFile(const std::string& multKeyLocation,
    const SerialMode serialMode);
[[nodiscard]] bool DCRTPolySerializeEvalMultKeyByIdToFile(const std::string& multKeyLocation,
    const SerialMode serialMode, const std::string& id);
[[nodiscard]] bool DCRTPolySerializeEvalMultKeyToFile(const std::string& multKeyLocation,
    const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);

// EvalMultKey
[[nodiscard]] bool DCRTPolyDeserializeEvalAutomorphismKeyFromFile(
    const std::string& automorphismKeyLocation, const SerialMode serialMode);
[[nodiscard]] bool DCRTPolySerializeEvalAutomorphismKeyByIdToFile(
    const std::string& automorphismKeyLocation, const SerialMode serialMode,
    const std::string& id);
[[nodiscard]] bool DCRTPolySerializeEvalAutomorphismKeyToFile(
    const std::string& automorphismKeyLocation, const CryptoContextDCRTPoly& cryptoContext,
    const SerialMode serialMode);

// EvalSumKey
[[nodiscard]] bool DCRTPolyDeserializeEvalSumKeyFromFile(const std::string& sumKeyLocation,
    const SerialMode serialMode);
[[nodiscard]] bool DCRTPolySerializeEvalSumKeyByIdToFile(const std::string& sumKeyLocation,
    const SerialMode serialMode, const std::string& id);
[[nodiscard]] bool DCRTPolySerializeEvalSumKeyToFile(const std::string& sumKeyLocation,
    const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);

// PublicKey
[[nodiscard]] bool DCRTPolyDeserializePublicKeyFromFile(const std::string& publicKeyLocation,
    PublicKeyDCRTPoly& publicKey, const SerialMode serialMode);
[[nodiscard]] bool DCRTPolySerializePublicKeyToFile(const std::string& publicKeyLocation,
    const PublicKeyDCRTPoly& publicKey, const SerialMode serialMode);

} // openfhe
