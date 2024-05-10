#include "openfhe_rs_dev/src/main.rs.h"

namespace openfhe_rs_dev
{
std::unique_ptr<VectorOfComplexNumbers> GenVectorOfComplexNumbers(const std::vector<ComplexPair>& vals)
{
    std::vector<std::complex<double>> result;
    result.reserve(vals.size());
    for (const ComplexPair& p : vals)
    {
        result.emplace_back(p.re, p.im);
    }
    return std::make_unique<VectorOfComplexNumbers>(std::move(result));
}
std::unique_ptr<Params> GetParamsByScheme(const SCHEME scheme)
{
    return std::make_unique<Params>(scheme);
}
std::unique_ptr<Params> GetParamsByVectorOfString(const std::vector<std::string>& vals)
{
    return std::make_unique<Params>(vals);
}
std::unique_ptr<ParamsBFVRNS> GetParamsBFVRNS()
{
    return std::make_unique<ParamsBFVRNS>();
}
std::unique_ptr<ParamsBFVRNS> GetParamsBFVRNSbyVectorOfString(const std::vector<std::string>& vals)
{
    return std::make_unique<ParamsBFVRNS>(vals);
}
std::unique_ptr<ParamsBGVRNS> GetParamsBGVRNS()
{
    return std::make_unique<ParamsBGVRNS>();
}
std::unique_ptr<ParamsBGVRNS> GetParamsBGVRNSbyVectorOfString(const std::vector<std::string>& vals)
{
    return std::make_unique<ParamsBGVRNS>(vals);
}
std::unique_ptr<ParamsCKKSRNS> GetParamsCKKSRNS()
{
    return std::make_unique<ParamsCKKSRNS>();
}
std::unique_ptr<ParamsCKKSRNS> GetParamsCKKSRNSbyVectorOfString(const std::vector<std::string>& vals)
{
    return std::make_unique<ParamsCKKSRNS>(vals);
}
std::unique_ptr<Plaintext> GenEmptyPlainText()
{
    return std::make_unique<Plaintext>();
}
std::unique_ptr<CryptoContextDCRTPoly> GenEmptyCryptoContext()
{
    return std::make_unique<CryptoContextDCRTPoly>();
}
std::unique_ptr<CryptoContextDCRTPoly> GenCryptoContextByParamsBFVRNS(const ParamsBFVRNS& params)
{
    return std::make_unique<CryptoContextDCRTPoly>(params);
}
std::unique_ptr<CryptoContextDCRTPoly> GenCryptoContextByParamsBGVRNS(const ParamsBGVRNS& params)
{
    return std::make_unique<CryptoContextDCRTPoly>(params);
}
std::unique_ptr<CryptoContextDCRTPoly> GenCryptoContextByParamsCKKSRNS(const ParamsCKKSRNS& params)
{
    return std::make_unique<CryptoContextDCRTPoly>(params);
}
std::unique_ptr<PublicKeyDCRTPoly> GenDefaultConstructedPublicKey()
{
    return std::make_unique<PublicKeyDCRTPoly>();
}
std::unique_ptr<CiphertextDCRTPoly> GenDefaultConstructedCiphertext()
{
    return std::make_unique<CiphertextDCRTPoly>();
}
bool SerializeCryptoContextToFile(const std::string& ccLocation, const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode)
{
    if (serialMode == SerialMode::BINARY)
    {
        return lbcrypto::Serial::SerializeToFile(ccLocation, cryptoContext.m_cryptoContextImplSharedPtr, lbcrypto::SerType::BINARY);
    }
    else if (serialMode == SerialMode::JSON)
    {
        return lbcrypto::Serial::SerializeToFile(ccLocation, cryptoContext.m_cryptoContextImplSharedPtr, lbcrypto::SerType::JSON);
    }
    return false;
}
bool DeserializeCryptoContextFromFile(const std::string& ccLocation, CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode)
{
    if (serialMode == SerialMode::BINARY)
    {
        return lbcrypto::Serial::DeserializeFromFile(ccLocation, cryptoContext.m_cryptoContextImplSharedPtr, lbcrypto::SerType::BINARY);
    }
    else if (serialMode == SerialMode::JSON)
    {
        return lbcrypto::Serial::DeserializeFromFile(ccLocation, cryptoContext.m_cryptoContextImplSharedPtr, lbcrypto::SerType::JSON);
    }
    return false;
}
bool SerializeEvalMultKeyToFile(const std::string& multKeyLocation, const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode)
{
    std::ofstream ofs(multKeyLocation, std::ios::out | std::ios::binary);
    if (ofs.is_open())
    {
        if (serialMode == SerialMode::BINARY)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalMultKey(ofs, lbcrypto::SerType::BINARY, cryptoContext.m_cryptoContextImplSharedPtr);
        }
        else if (serialMode == SerialMode::JSON)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalMultKey(ofs, lbcrypto::SerType::JSON, cryptoContext.m_cryptoContextImplSharedPtr);
        }
        ofs.close();
    }
    return false;
}
bool SerializeEvalMultKeyByIdToFile(const std::string& multKeyLocation, const SerialMode serialMode, const std::string& id)
{
    std::ofstream ofs(multKeyLocation, std::ios::out | std::ios::binary);
    if (ofs.is_open())
    {
        if (serialMode == SerialMode::BINARY)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalMultKey(ofs, lbcrypto::SerType::BINARY, id);
        }
        else if (serialMode == SerialMode::JSON)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalMultKey(ofs, lbcrypto::SerType::JSON, id);
        }
        ofs.close();
    }
    return false;
}
bool DeserializeEvalMultKeyFromFile(const std::string& multKeyLocation, const SerialMode serialMode)
{
    std::ifstream ifs(multKeyLocation, std::ios::in | std::ios::binary);
    if (ifs.is_open())
    {
        if (serialMode == SerialMode::BINARY)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::DeserializeEvalMultKey(ifs, lbcrypto::SerType::BINARY);
        }
        else if (serialMode == SerialMode::JSON)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::DeserializeEvalMultKey(ifs, lbcrypto::SerType::JSON);
        }
        ifs.close();
    }
    return false;
}
bool SerializeEvalSumKeyToFile(const std::string& sumKeyLocation, const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode)
{
    std::ofstream ofs(sumKeyLocation, std::ios::out | std::ios::binary);
    if (ofs.is_open())
    {
        if (serialMode == SerialMode::BINARY)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalAutomorphismKey(ofs, lbcrypto::SerType::BINARY, cryptoContext.m_cryptoContextImplSharedPtr);
        }
        else if (serialMode == SerialMode::JSON)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalAutomorphismKey(ofs, lbcrypto::SerType::JSON, cryptoContext.m_cryptoContextImplSharedPtr);
        }
        ofs.close();
    }
    return false;
}
bool SerializeEvalSumKeyByIdToFile(const std::string& sumKeyLocation, const SerialMode serialMode, const std::string& id)
{
    std::ofstream ofs(sumKeyLocation, std::ios::out | std::ios::binary);
    if (ofs.is_open())
    {
        if (serialMode == SerialMode::BINARY)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalSumKey(ofs, lbcrypto::SerType::BINARY, id);
        }
        else if (serialMode == SerialMode::JSON)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalSumKey(ofs, lbcrypto::SerType::JSON, id);
        }
        ofs.close();
    }
    return false;
}
bool DeserializeEvalSumKeyFromFile(const std::string& sumKeyLocation, const SerialMode serialMode)
{
    std::ifstream ifs(sumKeyLocation, std::ios::in | std::ios::binary);
    if (ifs.is_open())
    {
        if (serialMode == SerialMode::BINARY)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::DeserializeEvalAutomorphismKey(ifs, lbcrypto::SerType::BINARY);
        }
        else if (serialMode == SerialMode::JSON)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::DeserializeEvalAutomorphismKey(ifs, lbcrypto::SerType::JSON);
        }
        ifs.close();
    }
    return false;
}
bool SerializeEvalAutomorphismKeyToFile(const std::string& automorphismKeyLocation, const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode)
{
    std::ofstream ofs(automorphismKeyLocation, std::ios::out | std::ios::binary);
    if (ofs.is_open())
    {
        if (serialMode == SerialMode::BINARY)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalAutomorphismKey(ofs, lbcrypto::SerType::BINARY, cryptoContext.m_cryptoContextImplSharedPtr);
        }
        else if (serialMode == SerialMode::JSON)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalAutomorphismKey(ofs, lbcrypto::SerType::JSON, cryptoContext.m_cryptoContextImplSharedPtr);
        }
        ofs.close();
    }
    return false;
}
bool SerializeEvalAutomorphismKeyByIdToFile(const std::string& automorphismKeyLocation, const SerialMode serialMode, const std::string& id)
{
    std::ofstream ofs(automorphismKeyLocation, std::ios::out | std::ios::binary);
    if (ofs.is_open())
    {
        if (serialMode == SerialMode::BINARY)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalAutomorphismKey(ofs, lbcrypto::SerType::BINARY, id);
        }
        else if (serialMode == SerialMode::JSON)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalAutomorphismKey(ofs, lbcrypto::SerType::JSON, id);
        }
        ofs.close();
    }
    return false;
}
bool DeserializeEvalAutomorphismKeyFromFile(const std::string& automorphismKeyLocation, const SerialMode serialMode)
{
    std::ifstream ifs(automorphismKeyLocation, std::ios::in | std::ios::binary);
    if (ifs.is_open())
    {
        if (serialMode == SerialMode::BINARY)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::DeserializeEvalAutomorphismKey(ifs, lbcrypto::SerType::BINARY);
        }
        else if (serialMode == SerialMode::JSON)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::DeserializeEvalAutomorphismKey(ifs, lbcrypto::SerType::JSON);
        }
        ifs.close();
    }
    return false;
}
bool SerializeCiphertextToFile(const std::string& ciphertextLocation, const CiphertextDCRTPoly& ciphertext, const SerialMode serialMode)
{
    if (serialMode == SerialMode::BINARY)
    {
        return lbcrypto::Serial::SerializeToFile(ciphertextLocation, ciphertext.m_ciphertext, lbcrypto::SerType::BINARY);
    }
    else if (serialMode == SerialMode::JSON)
    {
        return lbcrypto::Serial::SerializeToFile(ciphertextLocation, ciphertext.m_ciphertext, lbcrypto::SerType::JSON);
    }
    return false;
}
bool DeserializeCiphertextFromFile(const std::string& ciphertextLocation, CiphertextDCRTPoly& ciphertext, const SerialMode serialMode)
{
    if (serialMode == SerialMode::BINARY)
    {
        return lbcrypto::Serial::DeserializeFromFile(ciphertextLocation, ciphertext.m_ciphertext, lbcrypto::SerType::BINARY);
    }
    else if (serialMode == SerialMode::JSON)
    {
        return lbcrypto::Serial::DeserializeFromFile(ciphertextLocation, ciphertext.m_ciphertext, lbcrypto::SerType::JSON);
    }
    return false;
}
bool SerializePublicKeyToFile(const std::string& publicKeyLocation, const PublicKeyDCRTPoly& publicKey, const SerialMode serialMode)
{
    if (serialMode == SerialMode::BINARY)
    {
        return lbcrypto::Serial::SerializeToFile(publicKeyLocation, publicKey.m_publicKey, lbcrypto::SerType::BINARY);
    }
    else if (serialMode == SerialMode::JSON)
    {
        return lbcrypto::Serial::SerializeToFile(publicKeyLocation, publicKey.m_publicKey, lbcrypto::SerType::JSON);
    }
    return false;
}
bool DeserializePublicKeyFromFile(const std::string& publicKeyLocation, PublicKeyDCRTPoly& publicKey, const SerialMode serialMode)
{
    if (serialMode == SerialMode::BINARY)
    {
        return lbcrypto::Serial::DeserializeFromFile(publicKeyLocation, publicKey.m_publicKey, lbcrypto::SerType::BINARY);
    }
    else if (serialMode == SerialMode::JSON)
    {
        return lbcrypto::Serial::DeserializeFromFile(publicKeyLocation, publicKey.m_publicKey, lbcrypto::SerType::JSON);
    }
    return false;
}
} // openfhe_rs_dev

