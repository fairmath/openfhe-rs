#pragma once

#include "bits/stringfwd.h"

#include "SerialMode.h"

namespace openfhe
{

class CiphertextDCRTPoly;
class CryptoContextDCRTPoly;
class PublicKeyDCRTPoly;

// Ciphertext
[[nodiscard]] bool DeserializeCiphertextFromFile(const std::string& ciphertextLocation,
    CiphertextDCRTPoly& ciphertext, const SerialMode serialMode);
[[nodiscard]] bool SerializeCiphertextToFile(const std::string& ciphertextLocation,
    const CiphertextDCRTPoly& ciphertext, const SerialMode serialMode);

// CryptoContextDCRTPoly
[[nodiscard]] bool DeserializeCryptoContextFromFile(const std::string& ccLocation,
    CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);
[[nodiscard]] bool SerializeCryptoContextToFile(const std::string& ccLocation,
    const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);

// EvalAutomorphismKey
[[nodiscard]] bool DeserializeEvalMultKeyFromFile(const std::string& multKeyLocation,
    const SerialMode serialMode);
[[nodiscard]] bool SerializeEvalMultKeyByIdToFile(const std::string& multKeyLocation,
    const SerialMode serialMode, const std::string& id);
[[nodiscard]] bool SerializeEvalMultKeyToFile(const std::string& multKeyLocation,
    const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);

// EvalMultKey
[[nodiscard]] bool DeserializeEvalAutomorphismKeyFromFile(
    const std::string& automorphismKeyLocation, const SerialMode serialMode);
[[nodiscard]] bool SerializeEvalAutomorphismKeyByIdToFile(
    const std::string& automorphismKeyLocation, const SerialMode serialMode,
    const std::string& id);
[[nodiscard]] bool SerializeEvalAutomorphismKeyToFile(const std::string& automorphismKeyLocation,
    const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);

// EvalSumKey
[[nodiscard]] bool DeserializeEvalSumKeyFromFile(const std::string& sumKeyLocation,
    const SerialMode serialMode);
[[nodiscard]] bool SerializeEvalSumKeyByIdToFile(const std::string& sumKeyLocation,
    const SerialMode serialMode, const std::string& id);
[[nodiscard]] bool SerializeEvalSumKeyToFile(const std::string& sumKeyLocation,
    const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);

// PublicKey
[[nodiscard]] bool DeserializePublicKeyFromFile(const std::string& publicKeyLocation,
    PublicKeyDCRTPoly& publicKey, const SerialMode serialMode);
[[nodiscard]] bool SerializePublicKeyToFile(const std::string& publicKeyLocation,
    const PublicKeyDCRTPoly& publicKey, const SerialMode serialMode);

} // openfhe
