#include "SerialDeserial.h"

#include "openfhe/pke/cryptocontext-ser.h"

#include "Ciphertext.h"
#include "CryptoContext.h"
#include "PublicKey.h"

namespace openfhe
{

bool SerializeCryptoContextToFile(const std::string& ccLocation,
    const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode)
{
    if (serialMode == SerialMode::BINARY)
    {
        return lbcrypto::Serial::SerializeToFile(ccLocation,
            cryptoContext.m_cryptoContextImplSharedPtr, lbcrypto::SerType::BINARY);
    }
    if (serialMode == SerialMode::JSON)
    {
        return lbcrypto::Serial::SerializeToFile(ccLocation,
            cryptoContext.m_cryptoContextImplSharedPtr, lbcrypto::SerType::JSON);
    }
    return false;
}
bool DeserializeCryptoContextFromFile(const std::string& ccLocation,
    CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode)
{
    if (serialMode == SerialMode::BINARY)
    {
        return lbcrypto::Serial::DeserializeFromFile(ccLocation,
            cryptoContext.m_cryptoContextImplSharedPtr, lbcrypto::SerType::BINARY);
    }
    if (serialMode == SerialMode::JSON)
    {
        return lbcrypto::Serial::DeserializeFromFile(ccLocation,
            cryptoContext.m_cryptoContextImplSharedPtr, lbcrypto::SerType::JSON);
    }
    return false;
}
bool SerializeEvalMultKeyToFile(const std::string& multKeyLocation,
    const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode)
{
    const auto close = [](std::ofstream* const ofs){ if (ofs->is_open()) { ofs->close(); } };
    const std::unique_ptr<std::ofstream, decltype(close)> ofs(
        new std::ofstream(multKeyLocation, std::ios::out | std::ios::binary), close);

    if (ofs->is_open())
    {
        if (serialMode == SerialMode::BINARY)
        {
            return CryptoContextImpl::SerializeEvalMultKey(*ofs,
                lbcrypto::SerType::BINARY, cryptoContext.m_cryptoContextImplSharedPtr);
        }
        if (serialMode == SerialMode::JSON)
        {
            return CryptoContextImpl::SerializeEvalMultKey(*ofs,
                lbcrypto::SerType::JSON, cryptoContext.m_cryptoContextImplSharedPtr);
        }
    }
    return false;
}
bool SerializeEvalMultKeyByIdToFile(const std::string& multKeyLocation,
    const SerialMode serialMode, const std::string& id)
{
    const auto close = [](std::ofstream* const ofs){ if (ofs->is_open()) { ofs->close(); } };
    const std::unique_ptr<std::ofstream, decltype(close)> ofs(
        new std::ofstream(multKeyLocation, std::ios::out | std::ios::binary), close);

    if (ofs->is_open())
    {
        if (serialMode == SerialMode::BINARY)
        {
            return CryptoContextImpl::SerializeEvalMultKey(*ofs, lbcrypto::SerType::BINARY, id);
        }
        if (serialMode == SerialMode::JSON)
        {
            return CryptoContextImpl::SerializeEvalMultKey(*ofs, lbcrypto::SerType::JSON, id);
        }
    }
    return false;
}
bool DeserializeEvalMultKeyFromFile(const std::string& multKeyLocation,
    const SerialMode serialMode)
{
    const auto close = [](std::ifstream* const ifs){ if (ifs->is_open()) { ifs->close(); } };
    const std::unique_ptr<std::ifstream, decltype(close)> ifs(
        new std::ifstream(multKeyLocation, std::ios::in | std::ios::binary), close);

    if (ifs->is_open())
    {
        if (serialMode == SerialMode::BINARY)
        {
            return CryptoContextImpl::DeserializeEvalMultKey(*ifs, lbcrypto::SerType::BINARY);
        }
        if (serialMode == SerialMode::JSON)
        {
            return CryptoContextImpl::DeserializeEvalMultKey(*ifs, lbcrypto::SerType::JSON);
        }
    }
    return false;
}
bool SerializeEvalSumKeyToFile(const std::string& sumKeyLocation,
    const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode)
{
    const auto close = [](std::ofstream* const ofs){ if (ofs->is_open()) { ofs->close(); } };
    const std::unique_ptr<std::ofstream, decltype(close)> ofs(
        new std::ofstream(sumKeyLocation, std::ios::out | std::ios::binary), close);

    if (ofs->is_open())
    {
        if (serialMode == SerialMode::BINARY)
        {
            return CryptoContextImpl::SerializeEvalAutomorphismKey(*ofs, lbcrypto::SerType::BINARY,
                cryptoContext.m_cryptoContextImplSharedPtr);
        }
        if (serialMode == SerialMode::JSON)
        {
            return CryptoContextImpl::SerializeEvalAutomorphismKey(*ofs, lbcrypto::SerType::JSON,
                cryptoContext.m_cryptoContextImplSharedPtr);
        }
    }
    return false;
}
bool SerializeEvalSumKeyByIdToFile(const std::string& sumKeyLocation,
    const SerialMode serialMode, const std::string& id)
{
    const auto close = [](std::ofstream* const ofs){ if (ofs->is_open()) { ofs->close(); } };
    const std::unique_ptr<std::ofstream, decltype(close)> ofs(
        new std::ofstream(sumKeyLocation, std::ios::out | std::ios::binary), close);

    if (ofs->is_open())
    {
        if (serialMode == SerialMode::BINARY)
        {
            return CryptoContextImpl::SerializeEvalSumKey(*ofs, lbcrypto::SerType::BINARY, id);
        }
        if (serialMode == SerialMode::JSON)
        {
            return CryptoContextImpl::SerializeEvalSumKey(*ofs, lbcrypto::SerType::JSON, id);
        }
    }
    return false;
}
bool DeserializeEvalSumKeyFromFile(const std::string& sumKeyLocation, const SerialMode serialMode)
{
    const auto close = [](std::ifstream* const ifs){ if (ifs->is_open()) { ifs->close(); } };
    const std::unique_ptr<std::ifstream, decltype(close)> ifs(
        new std::ifstream(sumKeyLocation, std::ios::in | std::ios::binary), close);

    if (ifs->is_open())
    {
        if (serialMode == SerialMode::BINARY)
        {
            return CryptoContextImpl::DeserializeEvalAutomorphismKey(*ifs,
                lbcrypto::SerType::BINARY);
        }
        if (serialMode == SerialMode::JSON)
        {
            return CryptoContextImpl::DeserializeEvalAutomorphismKey(*ifs,
                lbcrypto::SerType::JSON);
        }
    }
    return false;
}
bool SerializeEvalAutomorphismKeyToFile(const std::string& automorphismKeyLocation,
    const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode)
{
    const auto close = [](std::ofstream* const ofs){ if (ofs->is_open()) { ofs->close(); } };
    const std::unique_ptr<std::ofstream, decltype(close)> ofs(
        new std::ofstream(automorphismKeyLocation, std::ios::out | std::ios::binary), close);

    if (ofs->is_open())
    {
        if (serialMode == SerialMode::BINARY)
        {
            return CryptoContextImpl::SerializeEvalAutomorphismKey(*ofs, lbcrypto::SerType::BINARY,
                cryptoContext.m_cryptoContextImplSharedPtr);
        }
        if (serialMode == SerialMode::JSON)
        {
            return CryptoContextImpl::SerializeEvalAutomorphismKey(*ofs, lbcrypto::SerType::JSON,
                cryptoContext.m_cryptoContextImplSharedPtr);
        }
    }
    return false;
}
bool SerializeEvalAutomorphismKeyByIdToFile(const std::string& automorphismKeyLocation,
    const SerialMode serialMode, const std::string& id)
{
    const auto close = [](std::ofstream* const ofs){ if (ofs->is_open()) { ofs->close(); } };
    const std::unique_ptr<std::ofstream, decltype(close)> ofs(
        new std::ofstream(automorphismKeyLocation, std::ios::out | std::ios::binary), close);

    if (ofs->is_open())
    {
        if (serialMode == SerialMode::BINARY)
        {
            return CryptoContextImpl::SerializeEvalAutomorphismKey(*ofs, lbcrypto::SerType::BINARY,
                id);
        }
        if (serialMode == SerialMode::JSON)
        {
            return CryptoContextImpl::SerializeEvalAutomorphismKey(*ofs, lbcrypto::SerType::JSON,
                id);
        }
    }
    return false;
}
bool DeserializeEvalAutomorphismKeyFromFile(const std::string& automorphismKeyLocation,
    const SerialMode serialMode)
{
    const auto close = [](std::ifstream* const ifs){ if (ifs->is_open()) { ifs->close(); } };
    const std::unique_ptr<std::ifstream, decltype(close)> ifs(
        new std::ifstream(automorphismKeyLocation, std::ios::in | std::ios::binary), close);

    if (ifs->is_open())
    {
        if (serialMode == SerialMode::BINARY)
        {
            return CryptoContextImpl::DeserializeEvalAutomorphismKey(*ifs,
                lbcrypto::SerType::BINARY);
        }
        if (serialMode == SerialMode::JSON)
        {
            return CryptoContextImpl::DeserializeEvalAutomorphismKey(*ifs,
                lbcrypto::SerType::JSON);
        }
    }
    return false;
}
bool SerializePublicKeyToFile(const std::string& publicKeyLocation,
    const PublicKeyDCRTPoly& publicKey, const SerialMode serialMode)
{
    if (serialMode == SerialMode::BINARY)
    {
        return lbcrypto::Serial::SerializeToFile(publicKeyLocation,
            publicKey.m_publicKey, lbcrypto::SerType::BINARY);
    }
    if (serialMode == SerialMode::JSON)
    {
        return lbcrypto::Serial::SerializeToFile(publicKeyLocation,
            publicKey.m_publicKey, lbcrypto::SerType::JSON);
    }
    return false;
}
bool DeserializePublicKeyFromFile(const std::string& publicKeyLocation,
    PublicKeyDCRTPoly& publicKey, const SerialMode serialMode)
{
    if (serialMode == SerialMode::BINARY)
    {
        return lbcrypto::Serial::DeserializeFromFile(publicKeyLocation,
            publicKey.m_publicKey, lbcrypto::SerType::BINARY);
    }
    if (serialMode == SerialMode::JSON)
    {
        return lbcrypto::Serial::DeserializeFromFile(publicKeyLocation,
            publicKey.m_publicKey, lbcrypto::SerType::JSON);
    }
    return false;
}
bool SerializeCiphertextToFile(const std::string& ciphertextLocation,
    const CiphertextDCRTPoly& ciphertext, const SerialMode serialMode)
{
    if (serialMode == SerialMode::BINARY)
    {
        return lbcrypto::Serial::SerializeToFile(ciphertextLocation,
            ciphertext.m_ciphertext, lbcrypto::SerType::BINARY);
    }
    if (serialMode == SerialMode::JSON)
    {
        return lbcrypto::Serial::SerializeToFile(ciphertextLocation,
            ciphertext.m_ciphertext, lbcrypto::SerType::JSON);
    }
    return false;
}
bool DeserializeCiphertextFromFile(const std::string& ciphertextLocation,
    CiphertextDCRTPoly& ciphertext, const SerialMode serialMode)
{
    if (serialMode == SerialMode::BINARY)
    {
        return lbcrypto::Serial::DeserializeFromFile(ciphertextLocation,
            ciphertext.m_ciphertext, lbcrypto::SerType::BINARY);
    }
    if (serialMode == SerialMode::JSON)
    {
        return lbcrypto::Serial::DeserializeFromFile(ciphertextLocation,
            ciphertext.m_ciphertext, lbcrypto::SerType::JSON);
    }
    return false;
}

} // openfhe
