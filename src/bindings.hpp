#pragma once

#include "openfhe/pke/scheme/ckksrns/gen-cryptocontext-ckksrns.h"
#include "openfhe/pke/scheme/bfvrns/gen-cryptocontext-bfvrns.h"
#include "openfhe/pke/scheme/bgvrns/gen-cryptocontext-bgvrns.h"

#include "rust/cxx.h" // rust::String

enum SerialMode
{
    BINARY = 0,
    JSON = 1,
};

namespace openfhe_rs_dev
{
using ParamsBFVRNS = lbcrypto::CCParams<lbcrypto::CryptoContextBFVRNS>;
using ParamsBGVRNS = lbcrypto::CCParams<lbcrypto::CryptoContextBGVRNS>;
using ParamsCKKSRNS = lbcrypto::CCParams<lbcrypto::CryptoContextCKKSRNS>;
using Params = lbcrypto::Params;
using SCHEME = lbcrypto::SCHEME;
using SecretKeyDist = lbcrypto::SecretKeyDist;
using ProxyReEncryptionMode = lbcrypto::ProxyReEncryptionMode;
using MultipartyMode = lbcrypto::MultipartyMode;
using ExecutionMode = lbcrypto::ExecutionMode;
using DecryptionNoiseMode = lbcrypto::DecryptionNoiseMode;
using KeySwitchTechnique = lbcrypto::KeySwitchTechnique;
using ScalingTechnique = lbcrypto::ScalingTechnique;
using SecurityLevel = lbcrypto::SecurityLevel;
using EncryptionTechnique = lbcrypto::EncryptionTechnique;
using MultiplicationTechnique = lbcrypto::MultiplicationTechnique;
using COMPRESSION_LEVEL = lbcrypto::COMPRESSION_LEVEL;
using PKESchemeFeature = lbcrypto::PKESchemeFeature;
using PublicKeyImpl = lbcrypto::PublicKeyImpl<lbcrypto::DCRTPoly>;
using PrivateKeyImpl = lbcrypto::PrivateKeyImpl<lbcrypto::DCRTPoly>;
using PlaintextImpl = lbcrypto::PlaintextImpl;
using CiphertextImpl = lbcrypto::CiphertextImpl<lbcrypto::DCRTPoly>;
using DecryptResult = lbcrypto::DecryptResult;
using DCRTPolyParams = lbcrypto::DCRTPoly::Params;
using ::SerialMode;
struct ComplexPair;
using Complex = std::complex<double>;
struct SharedComplex;

///////////////////////////////////////////////////////////////////////////////////////////////////

class PublicKeyDCRTPoly final
{
    std::shared_ptr<PublicKeyImpl> m_publicKey;
public:
    friend bool SerializePublicKeyToFile(const std::string& publicKeyLocation,
        const PublicKeyDCRTPoly& publicKey, const SerialMode serialMode);
    friend bool DeserializePublicKeyFromFile(const std::string& publicKeyLocation,
        PublicKeyDCRTPoly& publicKey, const SerialMode serialMode);

    explicit PublicKeyDCRTPoly();
    PublicKeyDCRTPoly(const PublicKeyDCRTPoly&) = delete;
    PublicKeyDCRTPoly(PublicKeyDCRTPoly&&) = delete;
    PublicKeyDCRTPoly& operator=(const PublicKeyDCRTPoly&) = delete;
    PublicKeyDCRTPoly& operator=(PublicKeyDCRTPoly&&) = delete;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

class KeyPairDCRTPoly final
{
    std::shared_ptr<PublicKeyImpl> m_publicKey;
    std::shared_ptr<PrivateKeyImpl> m_privateKey;
public:
    explicit KeyPairDCRTPoly(lbcrypto::KeyPair<lbcrypto::DCRTPoly> keyPair);
    KeyPairDCRTPoly(const KeyPairDCRTPoly&) = delete;
    KeyPairDCRTPoly(KeyPairDCRTPoly&&) = delete;
    KeyPairDCRTPoly& operator=(const KeyPairDCRTPoly&) = delete;
    KeyPairDCRTPoly& operator=(KeyPairDCRTPoly&&) = delete;

    [[nodiscard]] std::shared_ptr<PublicKeyImpl> GetPublicKey() const;
    [[nodiscard]] std::shared_ptr<PrivateKeyImpl> GetPrivateKey() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

class Plaintext final
{
    std::shared_ptr<PlaintextImpl> m_plaintext;
public:
    explicit Plaintext() = default;
    explicit Plaintext(std::shared_ptr<PlaintextImpl> plaintext);
    Plaintext(const Plaintext&) = delete;
    Plaintext(Plaintext&&) = delete;
    Plaintext& operator=(const Plaintext&) = delete;
    Plaintext& operator=(Plaintext&&) = delete;
    Plaintext& operator=(std::shared_ptr<PlaintextImpl> plaintext);

    [[nodiscard]] std::shared_ptr<PlaintextImpl> GetPlainText() const;
    void SetLength(const size_t newSize) const;
    [[nodiscard]] double GetLogPrecision() const;
    [[nodiscard]] rust::String GetString() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

class CiphertextDCRTPoly final
{
    std::shared_ptr<CiphertextImpl> m_ciphertext;
public:
    friend bool SerializeCiphertextToFile(const std::string& ciphertextLocation,
        const CiphertextDCRTPoly& ciphertext, const SerialMode serialMode);
    friend bool DeserializeCiphertextFromFile(const std::string& ciphertextLocation,
        CiphertextDCRTPoly& ciphertext, const SerialMode serialMode);

    explicit CiphertextDCRTPoly();
    explicit CiphertextDCRTPoly(std::shared_ptr<CiphertextImpl> ciphertext);
    CiphertextDCRTPoly(const CiphertextDCRTPoly&) = delete;
    CiphertextDCRTPoly(CiphertextDCRTPoly&&) = delete;
    CiphertextDCRTPoly& operator=(const CiphertextDCRTPoly&) = delete;
    CiphertextDCRTPoly& operator=(CiphertextDCRTPoly&&) = delete;

    [[nodiscard]] std::shared_ptr<CiphertextImpl> GetCipherText() const;
};

class CryptoContextDCRTPoly final
{
    std::shared_ptr<lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>> m_cryptoContextImplSharedPtr;
public:
    friend bool SerializeCryptoContextToFile(const std::string& ccLocation,
        const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);
    friend bool DeserializeCryptoContextFromFile(const std::string& ccLocation,
        CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);
    friend bool SerializeEvalMultKeyToFile(const std::string& multKeyLocation,
        const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);
    friend bool SerializeEvalSumKeyToFile(const std::string& sumKeyLocation,
        const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);
    friend bool SerializeEvalAutomorphismKeyToFile(const std::string& automorphismKeyLocation,
        const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);

    explicit CryptoContextDCRTPoly() = default;
    explicit CryptoContextDCRTPoly(const ParamsBFVRNS& params);
    explicit CryptoContextDCRTPoly(const ParamsBGVRNS& params);
    explicit CryptoContextDCRTPoly(const ParamsCKKSRNS& params);
    CryptoContextDCRTPoly(const CryptoContextDCRTPoly&) = delete;
    CryptoContextDCRTPoly(CryptoContextDCRTPoly&&) = delete;
    CryptoContextDCRTPoly& operator=(const CryptoContextDCRTPoly&) = delete;
    CryptoContextDCRTPoly& operator=(CryptoContextDCRTPoly&&) = delete;

    void Enable(const PKESchemeFeature feature) const;
    [[nodiscard]] std::unique_ptr<KeyPairDCRTPoly> KeyGen() const;
    void EvalMultKeyGen(const std::shared_ptr<PrivateKeyImpl> key) const;
    void EvalRotateKeyGen(
        const std::shared_ptr<PrivateKeyImpl> privateKey, const std::vector<int32_t>& indexList,
        const std::shared_ptr<PublicKeyImpl> publicKey /* nullptr */) const;
    [[nodiscard]] uint32_t GetRingDimension() const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> Encrypt(
        const std::shared_ptr<PublicKeyImpl> publicKey,
        std::shared_ptr<lbcrypto::PlaintextImpl> plaintext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAdd(
        std::shared_ptr<CiphertextImpl> ciphertext1,
        std::shared_ptr<CiphertextImpl> ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSub(
        std::shared_ptr<CiphertextImpl> ciphertext1,
        std::shared_ptr<CiphertextImpl> ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMult(
        std::shared_ptr<CiphertextImpl> ciphertext1,
        std::shared_ptr<CiphertextImpl> ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultByConst(
        std::shared_ptr<CiphertextImpl> ciphertext, const double constant) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalRotate(
        std::shared_ptr<CiphertextImpl> ciphertext, const int32_t index) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalPoly(
        std::shared_ptr<CiphertextImpl> ciphertext, const std::vector<double>& coefficients) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalChebyshevSeries(
        std::shared_ptr<CiphertextImpl> ciphertext, const std::vector<double>& coefficients,
        const double a, const double b) const;
    [[nodiscard]] std::unique_ptr<DecryptResult> Decrypt(
        const std::shared_ptr<PrivateKeyImpl> privateKey,
        std::shared_ptr<CiphertextImpl> ciphertext, Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<Plaintext> MakePackedPlaintext(
        const std::vector<int64_t>& value, const size_t noiseScaleDeg /* 1 */,
        const uint32_t level /* 0 */) const;
    [[nodiscard]] std::unique_ptr<Plaintext> MakeCKKSPackedPlaintext(
        const std::vector<double>& value, const size_t scaleDeg /* 1 */,
        const uint32_t level /* 0 */, const std::shared_ptr<DCRTPolyParams> params /* nullptr */,
        const uint32_t slots /* 0 */) const;
    [[nodiscard]] std::unique_ptr<Plaintext> MakeCKKSPackedPlaintextByVectorOfComplex(
        const std::vector<SharedComplex>& value, const size_t scaleDeg /* 1 */,
        const uint32_t level /* 0 */, const std::shared_ptr<DCRTPolyParams> params /* nullptr */,
        const uint32_t slots /* 0 */) const;
};

[[nodiscard]] std::unique_ptr<std::vector<SharedComplex>> GenVectorOfComplex(
    const std::vector<ComplexPair>& vals);
[[nodiscard]] std::unique_ptr<Params> GetParamsByScheme(const SCHEME scheme);
[[nodiscard]] std::unique_ptr<Params> GetParamsByVectorOfString(
    const std::vector<std::string>& vals);
[[nodiscard]] std::unique_ptr<ParamsBFVRNS> GetParamsBFVRNS();
[[nodiscard]] std::unique_ptr<ParamsBFVRNS> GetParamsBFVRNSbyVectorOfString(
    const std::vector<std::string>& vals);
[[nodiscard]] std::unique_ptr<ParamsBGVRNS> GetParamsBGVRNS();
[[nodiscard]] std::unique_ptr<ParamsBGVRNS> GetParamsBGVRNSbyVectorOfString(
    const std::vector<std::string>& vals);
[[nodiscard]] std::unique_ptr<ParamsCKKSRNS> GetParamsCKKSRNS();
[[nodiscard]] std::unique_ptr<ParamsCKKSRNS> GetParamsCKKSRNSbyVectorOfString(
    const std::vector<std::string>& vals);
[[nodiscard]] std::unique_ptr<Plaintext> GenEmptyPlainText();
[[nodiscard]] std::unique_ptr<CryptoContextDCRTPoly> GenEmptyCryptoContext();
[[nodiscard]] std::unique_ptr<CryptoContextDCRTPoly> GenCryptoContextByParamsBFVRNS(
    const ParamsBFVRNS& params);
[[nodiscard]] std::unique_ptr<CryptoContextDCRTPoly> GenCryptoContextByParamsBGVRNS(
    const ParamsBGVRNS& params);
[[nodiscard]] std::unique_ptr<CryptoContextDCRTPoly> GenCryptoContextByParamsCKKSRNS(
    const ParamsCKKSRNS& params);
[[nodiscard]] std::unique_ptr<PublicKeyDCRTPoly> GenDefaultConstructedPublicKey();
[[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> GenDefaultConstructedCiphertext();

bool SerializeCryptoContextToFile(const std::string& ccLocation,
    const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);
bool DeserializeCryptoContextFromFile(const std::string& ccLocation,
    CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);
bool SerializeEvalMultKeyToFile(const std::string& multKeyLocation,
    const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);
bool SerializeEvalMultKeyByIdToFile(const std::string& multKeyLocation,
    const SerialMode serialMode, const std::string& id);
bool DeserializeEvalMultKeyFromFile(const std::string& multKeyLocation,
    const SerialMode serialMode);
bool SerializeEvalSumKeyToFile(const std::string& sumKeyLocation,
    const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);
bool SerializeEvalSumKeyByIdToFile(const std::string& sumKeyLocation,
    const SerialMode serialMode, const std::string& id);
bool DeserializeEvalSumKeyFromFile(const std::string& sumKeyLocation, const SerialMode serialMode);
bool SerializeEvalAutomorphismKeyToFile(const std::string& automorphismKeyLocation,
    const CryptoContextDCRTPoly& cryptoContext, const SerialMode serialMode);
bool SerializeEvalAutomorphismKeyByIdToFile(const std::string& automorphismKeyLocation,
    const SerialMode serialMode, const std::string& id);
bool DeserializeEvalAutomorphismKeyFromFile(const std::string& automorphismKeyLocation,
    const SerialMode serialMode);
bool SerializeCiphertextToFile(const std::string& ciphertextLocation,
    const CiphertextDCRTPoly& ciphertext, const SerialMode serialMode);
bool DeserializeCiphertextFromFile(const std::string& ciphertextLocation,
    CiphertextDCRTPoly& ciphertext, const SerialMode serialMode);
bool SerializePublicKeyToFile(const std::string& publicKeyLocation,
    const PublicKeyDCRTPoly& publicKey, const SerialMode serialMode);
bool DeserializePublicKeyFromFile(const std::string& publicKeyLocation,
    PublicKeyDCRTPoly& publicKey, const SerialMode serialMode);
} // openfhe_rs_dev
