#include "SerialDeserial.h"

#include "openfhe/pke/cryptocontext-ser.h"

#include "Ciphertext.h"
#include "CryptoContext.h"
#include "PrivateKey.h"
#include "PublicKey.h"

namespace openfhe
{

template <typename ST, typename Object>
[[nodiscard]] bool SerialDeserial(const std::string& location,
    bool (* const funcPtr) (const std::string&, Object&, const ST&), Object& object)
{
    return funcPtr(location, object, ST{});
}
template <typename Object>
[[nodiscard]] bool Deserial(const std::string& location, Object& object,
    const SerialMode serialMode)
{
    if (serialMode == SerialMode::BINARY)
    {
        return SerialDeserial<lbcrypto::SerType::SERBINARY, decltype(object.GetRef())>(location,
            lbcrypto::Serial::DeserializeFromFile, object.GetRef());
    }
    if (serialMode == SerialMode::JSON)
    {
        return SerialDeserial<lbcrypto::SerType::SERJSON, decltype(object.GetRef())>(location,
            lbcrypto::Serial::DeserializeFromFile, object.GetRef());
    }
    return false;
}
template <typename Object>
[[nodiscard]] bool Serial(const std::string& location, Object& object, const SerialMode serialMode)
{
    if (serialMode == SerialMode::BINARY)
    {
        return SerialDeserial<lbcrypto::SerType::SERBINARY, decltype(object.GetRef())>(location,
            lbcrypto::Serial::SerializeToFile, object.GetRef());
    }
    if (serialMode == SerialMode::JSON)
    {
        return SerialDeserial<lbcrypto::SerType::SERJSON, decltype(object.GetRef())>(location,
            lbcrypto::Serial::SerializeToFile, object.GetRef());
    }
    return false;
}

template <typename ST, typename Stream, typename FStream, typename... Types>
[[nodiscard]] bool SerialDeserial(const std::string& location,
    bool (* const funcPtr) (Stream&, const ST&, Types... args), Types... args)
{
    const auto close = [](FStream* const fs){ if (fs->is_open()) { fs->close(); } };
    const std::unique_ptr<FStream, decltype(close)> fs(
        new FStream(location, std::ios::binary), close);
    return fs->is_open() ? funcPtr(*fs, ST{}, args...) : false;
}

// Ciphertext
bool DCRTPolyDeserializeCiphertextFromFile(const std::string& ciphertextLocation,
    CiphertextDCRTPoly& ciphertext, const SerialMode serialMode)
{
    return Deserial(ciphertextLocation, ciphertext, serialMode);
}
bool DCRTPolySerializeCiphertextToFile(const std::string& ciphertextLocation,
    const CiphertextDCRTPoly& ciphertext, const SerialMode serialMode)
{
    return Serial(ciphertextLocation, ciphertext, serialMode);
}

// CryptoContext
bool DCRTPolyDeserializeCryptoContextFromFile(const std::string& ccLocation,
    CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode)
{
    return Deserial(ccLocation, cryptoContext, serialMode);
}
bool DCRTPolySerializeCryptoContextToFile(const std::string& ccLocation,
    const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode)
{
    return Serial(ccLocation, cryptoContext, serialMode);
}

// EvalAutomorphismKey
bool DCRTPolyDeserializeEvalAutomorphismKeyFromFile(const std::string& automorphismKeyLocation,
    const SerialMode serialMode)
{
    if (serialMode == SerialMode::BINARY)
    {
        return SerialDeserial<lbcrypto::SerType::SERBINARY, std::istream, std::ifstream>(
            automorphismKeyLocation, CryptoContextImpl::DeserializeEvalAutomorphismKey);
    }
    if (serialMode == SerialMode::JSON)
    {
        return SerialDeserial<lbcrypto::SerType::SERJSON, std::istream, std::ifstream>(
            automorphismKeyLocation, CryptoContextImpl::DeserializeEvalAutomorphismKey);
    }
    return false;
}
bool DCRTPolySerializeEvalAutomorphismKeyByIdToFile(const std::string& automorphismKeyLocation,
    const SerialMode serialMode, const std::string& id)
{
    if (serialMode == SerialMode::BINARY)
    {
        return SerialDeserial<lbcrypto::SerType::SERBINARY, std::ostream, std::ofstream>(
            automorphismKeyLocation, CryptoContextImpl::SerializeEvalAutomorphismKey, id);
    }
    if (serialMode == SerialMode::JSON)
    {
        return SerialDeserial<lbcrypto::SerType::SERJSON, std::ostream, std::ofstream>(
            automorphismKeyLocation, CryptoContextImpl::SerializeEvalAutomorphismKey, id);
    }
    return false;
}
bool DCRTPolySerializeEvalAutomorphismKeyToFile(const std::string& automorphismKeyLocation,
    const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode)
{
    if (serialMode == SerialMode::BINARY)
    {
        return SerialDeserial<lbcrypto::SerType::SERBINARY, std::ostream, std::ofstream>(
            automorphismKeyLocation, CryptoContextImpl::SerializeEvalAutomorphismKey,
            cryptoContext.GetRef());
    }
    if (serialMode == SerialMode::JSON)
    {
        return SerialDeserial<lbcrypto::SerType::SERJSON, std::ostream, std::ofstream>(
            automorphismKeyLocation, CryptoContextImpl::SerializeEvalAutomorphismKey,
            cryptoContext.GetRef());
    }
    return false;
}

// EvalMultKey
bool DCRTPolyDeserializeEvalMultKeyFromFile(const std::string& multKeyLocation,
    const SerialMode serialMode)
{
    if (serialMode == SerialMode::BINARY)
    {
        return SerialDeserial<lbcrypto::SerType::SERBINARY, std::istream, std::ifstream>(
            multKeyLocation, CryptoContextImpl::DeserializeEvalMultKey);
    }
    if (serialMode == SerialMode::JSON)
    {
        return SerialDeserial<lbcrypto::SerType::SERJSON, std::istream, std::ifstream>(
            multKeyLocation, CryptoContextImpl::DeserializeEvalMultKey);
    }
    return false;
}
bool SerializeEvalMultKeyDCRTPolyByIdToFile(const std::string& multKeyLocation,
    const SerialMode serialMode, const std::string& id)
{
    if (serialMode == SerialMode::BINARY)
    {
        return SerialDeserial<lbcrypto::SerType::SERBINARY, std::ostream, std::ofstream>(
            multKeyLocation, CryptoContextImpl::SerializeEvalMultKey, id);
    }
    if (serialMode == SerialMode::JSON)
    {
        return SerialDeserial<lbcrypto::SerType::SERJSON, std::ostream, std::ofstream>(
            multKeyLocation, CryptoContextImpl::SerializeEvalMultKey, id);
    }
    return false;
}
bool DCRTPolySerializeEvalMultKeyToFile(const std::string& multKeyLocation,
    const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode)
{
    if (serialMode == SerialMode::BINARY)
    {
        return SerialDeserial<lbcrypto::SerType::SERBINARY, std::ostream, std::ofstream>(
            multKeyLocation, CryptoContextImpl::SerializeEvalMultKey, cryptoContext.GetRef());
    }
    if (serialMode == SerialMode::JSON)
    {
        return SerialDeserial<lbcrypto::SerType::SERJSON, std::ostream, std::ofstream>(
            multKeyLocation, CryptoContextImpl::SerializeEvalMultKey, cryptoContext.GetRef());
    }
    return false;
}

// EvalSumKey
bool DCRTPolyDeserializeEvalSumKeyFromFile(const std::string& sumKeyLocation, const SerialMode serialMode)
{
    if (serialMode == SerialMode::BINARY)
    {
        return SerialDeserial<lbcrypto::SerType::SERBINARY, std::istream, std::ifstream>(
            sumKeyLocation, CryptoContextImpl::DeserializeEvalAutomorphismKey);
    }
    if (serialMode == SerialMode::JSON)
    {
        return SerialDeserial<lbcrypto::SerType::SERJSON, std::istream, std::ifstream>(
            sumKeyLocation, CryptoContextImpl::DeserializeEvalAutomorphismKey);
    }
    return false;
}
bool DCRTPolySerializeEvalSumKeyByIdToFile(const std::string& sumKeyLocation,
    const SerialMode serialMode, const std::string& id)
{
    if (serialMode == SerialMode::BINARY)
    {
        return SerialDeserial<lbcrypto::SerType::SERBINARY, std::ostream, std::ofstream>(
            sumKeyLocation, CryptoContextImpl::SerializeEvalSumKey, id);
    }
    if (serialMode == SerialMode::JSON)
    {
        return SerialDeserial<lbcrypto::SerType::SERJSON, std::ostream, std::ofstream>(
            sumKeyLocation, CryptoContextImpl::SerializeEvalSumKey, id);
    }
    return false;
}
bool DCRTPolySerializeEvalSumKeyToFile(const std::string& sumKeyLocation,
    const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode)
{
    if (serialMode == SerialMode::BINARY)
    {
        return SerialDeserial<lbcrypto::SerType::SERBINARY, std::ostream, std::ofstream>(
            sumKeyLocation, CryptoContextImpl::SerializeEvalAutomorphismKey,
            cryptoContext.GetRef());
    }
    if (serialMode == SerialMode::JSON)
    {
        return SerialDeserial<lbcrypto::SerType::SERJSON, std::ostream, std::ofstream>(
            sumKeyLocation, CryptoContextImpl::SerializeEvalAutomorphismKey,
            cryptoContext.GetRef());
    }
    return false;
}

// PublicKey
bool DCRTPolyDeserializePublicKeyFromFile(const std::string& publicKeyLocation,
    PublicKeyDCRTPoly& publicKey, const SerialMode serialMode)
{
    return Deserial(publicKeyLocation, publicKey, serialMode);
}
bool DCRTPolySerializePublicKeyToFile(const std::string& publicKeyLocation,
    const PublicKeyDCRTPoly& publicKey, const SerialMode serialMode)
{
    return Serial(publicKeyLocation, publicKey, serialMode);
}

bool DCRTPolyDeserializePrivateKeyFromFile(const std::string& privateKeyLocation,
    PrivateKeyDCRTPoly& privateKey, const SerialMode serialMode)
{
    return Deserial(privateKeyLocation, privateKey, serialMode);
}

bool DCRTPolySerializePrivateKeyToFile(const std::string& privateKeyLocation,
    const PrivateKeyDCRTPoly& privateKey, const SerialMode serialMode)
{
    return Serial(privateKeyLocation, privateKey, serialMode);
}

} // openfhe
