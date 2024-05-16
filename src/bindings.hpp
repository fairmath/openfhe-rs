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

namespace openfhe
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
using DecryptResult = lbcrypto::DecryptResult;
using DCRTPolyParams = lbcrypto::DCRTPoly::Params;
using ::SerialMode;
struct ComplexPair;
using Complex = std::complex<double>;
struct SharedComplex;

// not used in the Rust side
using PlaintextImpl = lbcrypto::PlaintextImpl;
// not used in the Rust side
using CiphertextImpl = lbcrypto::CiphertextImpl<lbcrypto::DCRTPoly>;
// not used in the Rust side
using CryptoContextImpl = lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>;
// not used in the Rust side
using KeyPair = lbcrypto::KeyPair<lbcrypto::DCRTPoly>;

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

    [[nodiscard]] std::shared_ptr<PublicKeyImpl> GetInternal() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

class KeyPairDCRTPoly final
{
    std::shared_ptr<PublicKeyImpl> m_publicKey;
    std::shared_ptr<PrivateKeyImpl> m_privateKey;
public:
    explicit KeyPairDCRTPoly(KeyPair keyPair);
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

    [[nodiscard]] std::shared_ptr<PlaintextImpl> GetInternal() const;
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

    [[nodiscard]] std::shared_ptr<CiphertextImpl> GetInternal() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

class CryptoContextDCRTPoly final
{
    std::shared_ptr<CryptoContextImpl> m_cryptoContextImplSharedPtr;
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
    void EvalMultKeysGen(const std::shared_ptr<PrivateKeyImpl> key) const;
    void EvalRotateKeyGen(
        const std::shared_ptr<PrivateKeyImpl> privateKey, const std::vector<int32_t>& indexList,
        const std::shared_ptr<PublicKeyImpl> publicKey /* nullptr */) const;
    void EvalCKKStoFHEWPrecompute(const double scale /* 1.0 */) const;
    [[nodiscard]] uint32_t GetRingDimension() const;
    [[nodiscard]] uint32_t GetCyclotomicOrder() const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> Encrypt(
        const std::shared_ptr<PublicKeyImpl> publicKey, const Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAdd(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSub(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMult(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultNoRelin(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultAndRelinearize(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultByConst(
        const CiphertextDCRTPoly& ciphertext, const double constant) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalRotate(
        const CiphertextDCRTPoly& ciphertext, const int32_t index) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalPoly(
        const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalChebyshevSeries(
   	    const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients,
        const double a, const double b) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalBootstrap(
        const CiphertextDCRTPoly& ciphertext, const uint32_t numIterations /* 1 */,
        const uint32_t precision /* 0 */) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> Rescale(
   	    const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> ModReduce(
        const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSum(const CiphertextDCRTPoly& ciphertext,
        const uint32_t batchSize) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> IntMPBootAdjustScale(
   	    const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> IntMPBootRandomElementGen(
        const PublicKeyDCRTPoly& publicKey) const;
    void EvalBootstrapSetup(const std::vector<uint32_t>& levelBudget /* {5, 4} */,
        const std::vector<uint32_t>& dim1 /* {0, 0} */, const uint32_t slots /* 0 */,
        const uint32_t correctionFactor /* 0 */, const bool precompute /* true */) const;
    void EvalBootstrapKeyGen(const std::shared_ptr<PrivateKeyImpl> privateKey,
        const uint32_t slots) const;
    [[nodiscard]] std::unique_ptr<DecryptResult> Decrypt(
        const std::shared_ptr<PrivateKeyImpl> privateKey, const CiphertextDCRTPoly& ciphertext,
        Plaintext& plaintext) const;
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

///////////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////////

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
} // openfhe
