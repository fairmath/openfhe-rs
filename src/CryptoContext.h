#pragma once

#include "openfhe/pke/constants-fwd.h" // PKESchemeFeature
#include "openfhe/pke/cryptocontext-fwd.h" // CryptoContextImpl
#include "openfhe/pke/key/privatekey-fwd.h" // PrivateKeyImpl
#include "openfhe/pke/key/publickey-fwd.h" // PublicKeyImpl
#include "openfhe/pke/scheme/scheme-id.h" // SCHEME
#include "openfhe/pke/schemebase/decrypt-result.h" // DecryptResult

#include "rust/cxx.h" // rust::Fn

#include "SerialMode.h" // SerialMode

namespace lbcrypto
{

class Params;
class CryptoContextBFVRNS;
class CryptoContextBGVRNS;
class CryptoContextCKKSRNS;

template <typename T>
class CCParams;

} // lbcrypto

namespace openfhe
{

struct ComplexPair;

class KeyPairDCRTPoly;
class PublicKeyDCRTPoly;
class Plaintext;
class CiphertextDCRTPoly;

using SCHEME = lbcrypto::SCHEME;
using PKESchemeFeature = lbcrypto::PKESchemeFeature;

using Params = lbcrypto::Params;
using ParamsBFVRNS = lbcrypto::CCParams<lbcrypto::CryptoContextBFVRNS>;
using ParamsBGVRNS = lbcrypto::CCParams<lbcrypto::CryptoContextBGVRNS>;
using ParamsCKKSRNS = lbcrypto::CCParams<lbcrypto::CryptoContextCKKSRNS>;

using CryptoContextImpl = lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>;
using PublicKeyImpl = lbcrypto::PublicKeyImpl<lbcrypto::DCRTPoly>;
using PrivateKeyImpl = lbcrypto::PrivateKeyImpl<lbcrypto::DCRTPoly>;
using DCRTPolyParams = lbcrypto::DCRTPoly::Params;
using DecryptResult = lbcrypto::DecryptResult;

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

    void SetSchemeId(const SCHEME schemeTag) const;
    [[nodiscard]] SCHEME GetSchemeId() const;
    [[nodiscard]] size_t GetKeyGenLevel() const;
    void SetKeyGenLevel(const size_t level) const;
    void SetSwkFC(const CiphertextDCRTPoly& FHEWtoCKKSswk) const;
    void EvalCompareSwitchPrecompute(const uint32_t pLWE /* 0 */, const double scaleSign /* 1.0 */,
        const bool unit /* false */) const;
    [[nodiscard]] uint32_t FindAutomorphismIndex(const uint32_t idx) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> GetSwkFC() const;
    void Enable(const PKESchemeFeature feature) const;
    void EnableByMask(const uint32_t featureMask) const;
    [[nodiscard]] std::unique_ptr<KeyPairDCRTPoly> KeyGen() const;
    [[nodiscard]] std::unique_ptr<KeyPairDCRTPoly> MultipartyKeyGen(
        const PublicKeyDCRTPoly& publicKey, const bool makeSparse /* false */,
        const bool fresh /* false */) const;
    [[nodiscard]] std::unique_ptr<PublicKeyDCRTPoly> MultiAddPubKeys(
        const PublicKeyDCRTPoly& publicKey1, const PublicKeyDCRTPoly& publicKey2,
        const std::string& keyId /* "" */) const;
    [[nodiscard]] std::unique_ptr<KeyPairDCRTPoly> SparseKeyGen() const;
    void EvalMultKeyGen(const std::shared_ptr<PrivateKeyImpl> key) const;
    void EvalMultKeysGen(const std::shared_ptr<PrivateKeyImpl> key) const;
    void EvalRotateKeyGen(
        const std::shared_ptr<PrivateKeyImpl> privateKey, const std::vector<int32_t>& indexList,
        const std::shared_ptr<PublicKeyImpl> publicKey /* nullptr */) const;
    void EvalCKKStoFHEWPrecompute(const double scale /* 1.0 */) const;
    [[nodiscard]] uint32_t GetRingDimension() const;
    [[nodiscard]] uint32_t GetCyclotomicOrder() const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSin(const CiphertextDCRTPoly& ciphertext,
        const double a, const double b, const uint32_t degree) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalCos(const CiphertextDCRTPoly& ciphertext,
        const double a, const double b, const uint32_t degree) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EncryptByPublicKey(
        const std::shared_ptr<PublicKeyImpl> publicKey, const Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EncryptByPrivateKey(
        const std::shared_ptr<PrivateKeyImpl> privateKey, const Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAddByCiphertexts(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAddByCiphertextAndPlaintext(
        const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAddByPlaintextAndCiphertext(
        const Plaintext& plaintext, const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAddByConstAndCiphertext(
        const double constant, const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAddByCiphertextAndConst(
        const CiphertextDCRTPoly& ciphertext, const double constant) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAddMutableByCiphertexts(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAddMutableByCiphertextAndPlaintext(
        const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAddMutableByPlaintextAndCiphertext(
        const Plaintext& plaintext, const CiphertextDCRTPoly& ciphertext) const;
    void EvalAddInPlaceByCiphertexts(const CiphertextDCRTPoly& ciphertext1,
        const CiphertextDCRTPoly& ciphertext2) const;
    void EvalAddInPlaceByCiphertextAndPlaintext(const CiphertextDCRTPoly& ciphertext,
        const Plaintext& plaintext) const;
    void EvalAddInPlaceByPlaintextAndCiphertext(const Plaintext& plaintext,
        const CiphertextDCRTPoly& ciphertext) const;
    void EvalAddInPlaceByCiphertextAndConst(const CiphertextDCRTPoly& ciphertext,
        const double constant) const;
    void EvalAddInPlaceByConstAndCiphertext(const double constant,
        const CiphertextDCRTPoly& ciphertext) const;
    void EvalAddMutableInPlace(const CiphertextDCRTPoly& ciphertext1,
        const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSubByCiphertexts(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSubByCiphertextAndPlaintext(
        const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSubByPlaintextAndCiphertext(
        const Plaintext& plaintext, const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSubByConstAndCiphertext(
        const double constant, const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSubByCiphertextAndConst(
        const CiphertextDCRTPoly& ciphertext, const double constant) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSubMutableByCiphertexts(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSubMutableByCiphertextAndPlaintext(
        const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSubMutableByPlaintextAndCiphertext(
        const Plaintext& plaintext, const CiphertextDCRTPoly& ciphertext) const;
    void EvalSubInPlaceByCiphertexts(const CiphertextDCRTPoly& ciphertext1,
        const CiphertextDCRTPoly& ciphertext2) const;
    void EvalSubInPlaceByCiphertextAndConst(const CiphertextDCRTPoly& ciphertext,
        const double constant) const;
    void EvalSubInPlaceByConstAndCiphertext(const double constant,
        const CiphertextDCRTPoly& ciphertext) const;
    void EvalSubMutableInPlace(const CiphertextDCRTPoly& ciphertext1,
        const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultByCiphertexts(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultByCiphertextAndPlaintext(
        const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultByPlaintextAndCiphertext(
        const Plaintext& plaintext, const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultByConstAndCiphertext(
        const double constant, const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultByCiphertextAndConst(
        const CiphertextDCRTPoly& ciphertext, const double constant) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultMutableByCiphertexts(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultMutableByCiphertextAndPlaintext(
        const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultMutableByPlaintextAndCiphertext(
        const Plaintext& plaintext, const CiphertextDCRTPoly& ciphertext) const;
    void EvalMultInPlaceByCiphertextAndConst(const CiphertextDCRTPoly& ciphertext,
        const double constant) const;
    void EvalMultInPlaceByConstAndCiphertext(const double constant,
        const CiphertextDCRTPoly& ciphertext) const;
    void EvalMultMutableInPlace(const CiphertextDCRTPoly& ciphertext1,
        const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultNoRelin(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultAndRelinearize(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalRotate(
        const CiphertextDCRTPoly& ciphertext, const int32_t index) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalPoly(
        const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> KeySwitchDown(
        const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> KeySwitchExt(
        const CiphertextDCRTPoly& ciphertext, const bool addFirst) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> Compress(
        const CiphertextDCRTPoly& ciphertext, const uint32_t towersLeft /* 1 */) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalNegate(
        const CiphertextDCRTPoly& ciphertext) const;
    void EvalNegateInPlace(const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSquare(
        const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSquareMutable(
        const CiphertextDCRTPoly& ciphertext) const;
    void EvalSquareInPlace(const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAtIndex(
        const CiphertextDCRTPoly& ciphertext, const uint32_t index) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> ComposedEvalMult(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> Relinearize(
        const CiphertextDCRTPoly& ciphertext) const;
    void RelinearizeInPlace(const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalChebyshevSeries(
        const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients,
        const double a, const double b) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalChebyshevFunction(
        rust::Fn<void(const double x, double& ret)> func, const CiphertextDCRTPoly& ciphertext,
        const double a, const double b, const uint32_t degree) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalBootstrap(
        const CiphertextDCRTPoly& ciphertext, const uint32_t numIterations /* 1 */,
        const uint32_t precision /* 0 */) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> Rescale(
        const CiphertextDCRTPoly& ciphertext) const;
    void RescaleInPlace(const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> ModReduce(
        const CiphertextDCRTPoly& ciphertext) const;
    void ModReduceInPlace(const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSum(const CiphertextDCRTPoly& ciphertext,
        const uint32_t batchSize) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalPolyLinear(
        const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalPolyPS(
        const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalChebyshevSeriesLinear(
        const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients,
        const double a, const double b) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalChebyshevSeriesPS(
        const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients,
        const double a, const double b) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalDivide(
        const CiphertextDCRTPoly& ciphertext, const double a, const double b,
        const uint32_t degree) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> IntMPBootAdjustScale(
        const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalLogistic(
        const CiphertextDCRTPoly& ciphertext, const double a, const double b,
        const uint32_t degree) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> IntMPBootRandomElementGen(
        const PublicKeyDCRTPoly& publicKey) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalCompareSchemeSwitching(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2,
        const uint32_t numCtxts /* 0 */, const uint32_t numSlots /* 0 */,
        const uint32_t pLWE /* 0 */, const double scaleSign /* 1.0 */,
        const bool unit /* false */) const;
    void EvalBootstrapSetup(const std::vector<uint32_t>& levelBudget /* {5, 4} */,
        const std::vector<uint32_t>& dim1 /* {0, 0} */, const uint32_t slots /* 0 */,
        const uint32_t correctionFactor /* 0 */, const bool precompute /* true */) const;
    void EvalBootstrapKeyGen(const std::shared_ptr<PrivateKeyImpl> privateKey,
        const uint32_t slots) const;
    void EvalBootstrapPrecompute(const uint32_t slots /* 0 */) const;
    [[nodiscard]] std::unique_ptr<DecryptResult> DecryptByPrivateKeyAndCiphertext(
        const std::shared_ptr<PrivateKeyImpl> privateKey, const CiphertextDCRTPoly& ciphertext,
        Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<DecryptResult> DecryptByCiphertextAndPrivateKey(
        const CiphertextDCRTPoly& ciphertext, const std::shared_ptr<PrivateKeyImpl> privateKey,
        Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<Plaintext> MakePackedPlaintext(
        const std::vector<int64_t>& value, const size_t noiseScaleDeg /* 1 */,
        const uint32_t level /* 0 */) const;
    [[nodiscard]] std::unique_ptr<Plaintext> MakeStringPlaintext(const std::string& s) const;
    [[nodiscard]] std::unique_ptr<Plaintext> MakeCoefPackedPlaintext(
        const std::vector<int64_t>& value, const size_t noiseScaleDeg /* 1 */,
        const uint32_t level /* 0 */) const;
    [[nodiscard]] std::unique_ptr<Plaintext> MakeCKKSPackedPlaintext(
        const std::vector<double>& value, const size_t scaleDeg /* 1 */,
        const uint32_t level /* 0 */, const std::shared_ptr<DCRTPolyParams> params /* nullptr */,
        const uint32_t slots /* 0 */) const;
    [[nodiscard]] std::unique_ptr<Plaintext> MakeCKKSPackedPlaintextByVectorOfComplex(
        const std::vector<ComplexPair>& value, const size_t scaleDeg /* 1 */,
        const uint32_t level /* 0 */, const std::shared_ptr<DCRTPolyParams> params /* nullptr */,
        const uint32_t slots /* 0 */) const;
    [[nodiscard]] std::unique_ptr<std::vector<uint32_t>> FindAutomorphismIndices(
        const std::vector<uint32_t>& idxList) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalInnerProductByCiphertexts(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2,
        const uint32_t batchSize) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalInnerProductByPlaintext(
        const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext,
        const uint32_t batchSize) const;
    [[nodiscard]] std::shared_ptr<CryptoContextImpl> GetInternal() const;
};
// cxx currently does not support static class methods
void ClearEvalMultKeys();
void ClearEvalMultKeysById(const std::string& id);
void ClearEvalMultKeysByCryptoContext(const CryptoContextDCRTPoly& cryptoContext);
void ClearEvalSumKeys();
void ClearEvalSumKeysById(const std::string& id);
void ClearEvalSumKeysByCryptoContext(const CryptoContextDCRTPoly& cryptoContext);
void ClearEvalAutomorphismKeys();
void ClearEvalAutomorphismKeysById(const std::string& id);
void ClearEvalAutomorphismKeysByCryptoContext(const CryptoContextDCRTPoly& cryptoContext);
[[nodiscard]] std::unique_ptr<std::vector<uint32_t>> GetExistingEvalAutomorphismKeyIndices(
    const std::string& keyTag);
[[nodiscard]] std::unique_ptr<std::vector<uint32_t>> GetUniqueValues(
    const std::vector<uint32_t>& oldValues, const std::vector<uint32_t>& newValues);

[[nodiscard]] std::unique_ptr<CryptoContextDCRTPoly> GenEmptyCryptoContext();
[[nodiscard]] std::unique_ptr<CryptoContextDCRTPoly> GenCryptoContextByParamsBFVRNS(
    const ParamsBFVRNS& params);
[[nodiscard]] std::unique_ptr<CryptoContextDCRTPoly> GenCryptoContextByParamsBGVRNS(
    const ParamsBGVRNS& params);
[[nodiscard]] std::unique_ptr<CryptoContextDCRTPoly> GenCryptoContextByParamsCKKSRNS(
    const ParamsCKKSRNS& params);

} // openfhe
