#include "openfhe/src/lib.rs.h"

#include "openfhe/pke/gen-cryptocontext.h"

namespace openfhe
{
PublicKeyDCRTPoly::PublicKeyDCRTPoly()
    : m_publicKey(std::make_shared<PublicKeyImpl>())
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////

KeyPairDCRTPoly::KeyPairDCRTPoly(lbcrypto::KeyPair<lbcrypto::DCRTPoly> keyPair)
    : m_publicKey(keyPair.publicKey)
    , m_privateKey(keyPair.secretKey)
{ }
std::shared_ptr<PublicKeyImpl> KeyPairDCRTPoly::GetPublicKey() const
{
    return m_publicKey;
}
std::shared_ptr<PrivateKeyImpl> KeyPairDCRTPoly::GetPrivateKey() const
{
    return m_privateKey;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

Plaintext::Plaintext(std::shared_ptr<PlaintextImpl> plaintext)
    : m_plaintext(plaintext)
{ }
Plaintext& Plaintext::operator=(std::shared_ptr<PlaintextImpl> plaintext)
{
    m_plaintext = plaintext;
    return *this;
}
std::shared_ptr<PlaintextImpl> Plaintext::GetPlainText() const
{
    return m_plaintext;
}
void Plaintext::SetLength(const size_t newSize) const
{
    m_plaintext->SetLength(newSize);
}
double Plaintext::GetLogPrecision() const
{
    return m_plaintext->GetLogPrecision();
}
rust::String Plaintext::GetString() const
{
    std::stringstream stream;
    stream << *m_plaintext;
    return rust::String(stream.str());
}

///////////////////////////////////////////////////////////////////////////////////////////////////

CiphertextDCRTPoly::CiphertextDCRTPoly()
    : m_ciphertext(std::make_shared<CiphertextImpl>())
{ }
CiphertextDCRTPoly::CiphertextDCRTPoly(std::shared_ptr<CiphertextImpl> ciphertext)
    : m_ciphertext(ciphertext)
{ }
std::shared_ptr<CiphertextImpl> CiphertextDCRTPoly::GetCipherText() const
{
    return m_ciphertext;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

CryptoContextDCRTPoly::CryptoContextDCRTPoly(const ParamsBFVRNS& params)
    : m_cryptoContextImplSharedPtr(lbcrypto::GenCryptoContext(params))
{ }
CryptoContextDCRTPoly::CryptoContextDCRTPoly(const ParamsBGVRNS& params)
    : m_cryptoContextImplSharedPtr(lbcrypto::GenCryptoContext(params))
{ }
CryptoContextDCRTPoly::CryptoContextDCRTPoly(const ParamsCKKSRNS& params)
    : m_cryptoContextImplSharedPtr(lbcrypto::GenCryptoContext(params))
{ }
std::unique_ptr<Plaintext> CryptoContextDCRTPoly::MakeCKKSPackedPlaintextByVectorOfComplex(
    const std::vector<SharedComplex>& value, const size_t scaleDeg, const uint32_t level,
    const std::shared_ptr<DCRTPolyParams> params, const uint32_t slots) const
{
    std::vector<Complex> v;
    v.reserve(value.size());
    for (const SharedComplex& elem : value)
    {
        v.push_back(std::move(*elem.ptr));
    }
    return std::make_unique<Plaintext>(m_cryptoContextImplSharedPtr->MakeCKKSPackedPlaintext(
        v, scaleDeg, level, params, slots));
}
void CryptoContextDCRTPoly::Enable(const PKESchemeFeature feature) const
{
    m_cryptoContextImplSharedPtr->Enable(feature);
}
std::unique_ptr<KeyPairDCRTPoly> CryptoContextDCRTPoly::KeyGen() const
{
    return std::make_unique<KeyPairDCRTPoly>(m_cryptoContextImplSharedPtr->KeyGen());
}
void CryptoContextDCRTPoly::EvalMultKeyGen(const std::shared_ptr<PrivateKeyImpl> key) const
{
    m_cryptoContextImplSharedPtr->EvalMultKeyGen(key);
}
void CryptoContextDCRTPoly::EvalMultKeysGen(const std::shared_ptr<PrivateKeyImpl> key) const
{
    m_cryptoContextImplSharedPtr->EvalMultKeysGen(key);
}
void CryptoContextDCRTPoly::EvalRotateKeyGen(
    const std::shared_ptr<PrivateKeyImpl> privateKey, const std::vector<int32_t>& indexList,
    const std::shared_ptr<PublicKeyImpl> publicKey) const
{
    m_cryptoContextImplSharedPtr->EvalRotateKeyGen(privateKey, indexList, publicKey);
}
std::unique_ptr<Plaintext> CryptoContextDCRTPoly::MakePackedPlaintext(
    const std::vector<int64_t>& value, const size_t noiseScaleDeg,
    const uint32_t level) const
{
    return std::make_unique<Plaintext>(m_cryptoContextImplSharedPtr->MakePackedPlaintext(
        value, noiseScaleDeg, level));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::Encrypt(
    const std::shared_ptr<lbcrypto::PublicKeyImpl<lbcrypto::DCRTPoly>> publicKey,
    std::shared_ptr<PlaintextImpl> plaintext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->Encrypt(
        publicKey, plaintext));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAdd(
    std::shared_ptr<CiphertextImpl> ciphertext1, std::shared_ptr<CiphertextImpl> ciphertext2) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAdd(
        ciphertext1, ciphertext2));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSub(
    std::shared_ptr<CiphertextImpl> ciphertext1, std::shared_ptr<CiphertextImpl> ciphertext2) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSub(
        ciphertext1, ciphertext2));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMult(
    std::shared_ptr<CiphertextImpl> ciphertext1, std::shared_ptr<CiphertextImpl> ciphertext2) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMult(
        ciphertext1, ciphertext2));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultNoRelin(
    std::shared_ptr<CiphertextImpl> ciphertext1, std::shared_ptr<CiphertextImpl> ciphertext2) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMultNoRelin(
        ciphertext1, ciphertext2));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultAndRelinearize(
    std::shared_ptr<CiphertextImpl> ciphertext1, std::shared_ptr<CiphertextImpl> ciphertext2) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalMultAndRelinearize(ciphertext1, ciphertext2));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultByConst(
    std::shared_ptr<CiphertextImpl> ciphertext, const double constant) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMult(
        ciphertext, constant));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalRotate(
    std::shared_ptr<CiphertextImpl> ciphertext, const int32_t index) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalRotate(ciphertext, index));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalChebyshevSeries(
    std::shared_ptr<CiphertextImpl> ciphertext, const std::vector<double>& coefficients,
    const double a, const double b) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalChebyshevSeries(
        ciphertext, coefficients, a, b));
}
std::unique_ptr<DecryptResult> CryptoContextDCRTPoly::Decrypt(
    const std::shared_ptr<PrivateKeyImpl> privateKey,
    std::shared_ptr<CiphertextImpl> ciphertext, Plaintext& plaintext) const
{
    std::shared_ptr<PlaintextImpl> res;
    std::unique_ptr<DecryptResult> result = std::make_unique<DecryptResult>(
        m_cryptoContextImplSharedPtr->Decrypt(privateKey, ciphertext, &res));
    plaintext = res;
    return result;
}
uint32_t CryptoContextDCRTPoly::GetRingDimension() const
{
    return m_cryptoContextImplSharedPtr->GetRingDimension();
}
std::unique_ptr<Plaintext> CryptoContextDCRTPoly::MakeCKKSPackedPlaintext(
    const std::vector<double>& value, const size_t scaleDeg, const uint32_t level,
    const std::shared_ptr<DCRTPolyParams> params, const uint32_t slots) const
{
    return std::make_unique<Plaintext>(m_cryptoContextImplSharedPtr->MakeCKKSPackedPlaintext(
        value, scaleDeg, level, params, slots));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalPoly(
    std::shared_ptr<CiphertextImpl> ciphertext, const std::vector<double>& coefficients) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalPoly(ciphertext, coefficients));
}

///////////////////////////////////////////////////////////////////////////////////////////////////

std::unique_ptr<std::vector<SharedComplex>> GenVectorOfComplex(
    const std::vector<ComplexPair>& vals)
{
    std::vector<SharedComplex> result;
    result.reserve(vals.size());
    for (const ComplexPair& p : vals)
    {
        SharedComplex temp;
        temp.ptr = std::make_shared<Complex>(p.re, p.im);
        result.emplace_back(std::move(temp));
    }
    return std::make_unique<std::vector<SharedComplex>>(std::move(result));
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
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalMultKey(
                *ofs, lbcrypto::SerType::BINARY, cryptoContext.m_cryptoContextImplSharedPtr);
        }
        if (serialMode == SerialMode::JSON)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalMultKey(
                *ofs, lbcrypto::SerType::JSON, cryptoContext.m_cryptoContextImplSharedPtr);
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
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalMultKey(
                *ofs, lbcrypto::SerType::BINARY, id);
        }
        if (serialMode == SerialMode::JSON)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalMultKey(
                *ofs, lbcrypto::SerType::JSON, id);
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
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::DeserializeEvalMultKey(
                *ifs, lbcrypto::SerType::BINARY);
        }
        if (serialMode == SerialMode::JSON)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::DeserializeEvalMultKey(
                *ifs, lbcrypto::SerType::JSON);
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
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalAutomorphismKey(
                *ofs, lbcrypto::SerType::BINARY, cryptoContext.m_cryptoContextImplSharedPtr);
        }
        if (serialMode == SerialMode::JSON)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalAutomorphismKey(
                *ofs, lbcrypto::SerType::JSON, cryptoContext.m_cryptoContextImplSharedPtr);
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
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalSumKey(
                *ofs, lbcrypto::SerType::BINARY, id);
        }
        if (serialMode == SerialMode::JSON)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalSumKey(
                *ofs, lbcrypto::SerType::JSON, id);
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
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::DeserializeEvalAutomorphismKey(
                *ifs, lbcrypto::SerType::BINARY);
        }
        if (serialMode == SerialMode::JSON)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::DeserializeEvalAutomorphismKey(
                *ifs, lbcrypto::SerType::JSON);
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
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalAutomorphismKey(
                *ofs, lbcrypto::SerType::BINARY, cryptoContext.m_cryptoContextImplSharedPtr);
        }
        if (serialMode == SerialMode::JSON)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalAutomorphismKey(
                *ofs, lbcrypto::SerType::JSON, cryptoContext.m_cryptoContextImplSharedPtr);
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
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalAutomorphismKey(
                *ofs, lbcrypto::SerType::BINARY, id);
        }
        if (serialMode == SerialMode::JSON)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::SerializeEvalAutomorphismKey(
                *ofs, lbcrypto::SerType::JSON, id);
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
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::DeserializeEvalAutomorphismKey(
                *ifs, lbcrypto::SerType::BINARY);
        }
        if (serialMode == SerialMode::JSON)
        {
            return lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>::DeserializeEvalAutomorphismKey(
                *ifs, lbcrypto::SerType::JSON);
        }
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
} // openfhe
