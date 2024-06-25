#pragma once

#include "openfhe/core/lattice/hal/lat-backend.h"
#include "openfhe/pke/constants.h"
#include "openfhe/pke/cryptocontext-fwd.h"
#include "openfhe/pke/scheme/scheme-id.h"

#include "rust/cxx.h"

namespace lbcrypto
{

template <typename T>
class CCParams;

class CryptoContextBFVRNS;
class CryptoContextBGVRNS;
class CryptoContextCKKSRNS;
class Params;

} // lbcrypto

namespace openfhe
{

class CiphertextDCRTPoly;
struct ComplexPair;
class CryptoParametersBaseDCRTPoly;
class DCRTPoly;
class DCRTPolyParams;
class DecryptResult;
class EncodingParams;
class EvalKeyDCRTPoly;
class KeyPairDCRTPoly;
class LWEPrivateKey;
class MapFromIndexToEvalKey;
class MapFromStringToMapFromIndexToEvalKey;
class MapFromStringToVectorOfEvalKeys;
class Plaintext;
class PrivateKeyDCRTPoly;
class PublicKeyDCRTPoly;
class SchemeBaseDCRTPoly;
class SetOfUints;
class UnorderedMapFromIndexToDCRTPoly;
class VectorOfCiphertexts;
class VectorOfDCRTPolys;
class VectorOfEvalKeys;
class VectorOfLWECiphertexts;
class VectorOfPrivateKeys;
class VectorOfVectorOfCiphertexts;

using CryptoContextImpl = lbcrypto::CryptoContextImpl<lbcrypto::DCRTPoly>;
using Params = lbcrypto::Params;
using ParamsBFVRNS = lbcrypto::CCParams<lbcrypto::CryptoContextBFVRNS>;
using ParamsBGVRNS = lbcrypto::CCParams<lbcrypto::CryptoContextBGVRNS>;
using ParamsCKKSRNS = lbcrypto::CCParams<lbcrypto::CryptoContextCKKSRNS>;
using PKESchemeFeature = lbcrypto::PKESchemeFeature;
using PlaintextEncodings = lbcrypto::PlaintextEncodings;
using SCHEME = lbcrypto::SCHEME;

class CryptoContextDCRTPoly final
{
    std::shared_ptr<CryptoContextImpl> m_cryptoContextImplSharedPtr;
public:
    CryptoContextDCRTPoly() = default;
    explicit CryptoContextDCRTPoly(const ParamsBFVRNS& params);
    explicit CryptoContextDCRTPoly(const ParamsBGVRNS& params);
    explicit CryptoContextDCRTPoly(const ParamsCKKSRNS& params);
    CryptoContextDCRTPoly(const CryptoContextDCRTPoly&) = delete;
    CryptoContextDCRTPoly(CryptoContextDCRTPoly&&) = delete;
    CryptoContextDCRTPoly& operator=(const CryptoContextDCRTPoly&) = delete;
    CryptoContextDCRTPoly& operator=(CryptoContextDCRTPoly&&) = delete;

    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> ComposedEvalMult(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> Compress(
        const CiphertextDCRTPoly& ciphertext, const uint32_t towersLeft /* 1 */) const;
    [[nodiscard]] std::unique_ptr<DecryptResult> DecryptByCiphertextAndPrivateKey(
        const CiphertextDCRTPoly& ciphertext, const PrivateKeyDCRTPoly& privateKey,
        Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<DecryptResult> DecryptByPrivateKeyAndCiphertext(
        const PrivateKeyDCRTPoly& privateKey, const CiphertextDCRTPoly& ciphertext,
        Plaintext& plaintext) const;
    void EnableByFeature(const PKESchemeFeature feature) const;
    void EnableByMask(const uint32_t featureMask) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EncryptByPrivateKey(
        const PrivateKeyDCRTPoly& privateKey, const Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EncryptByPublicKey(
        const PublicKeyDCRTPoly& publicKey, const Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAddByCiphertextAndConst(
        const CiphertextDCRTPoly& ciphertext, const double constant) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAddByCiphertextAndPlaintext(
        const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAddByCiphertexts(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAddByConstAndCiphertext(
        const double constant, const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAddByPlaintextAndCiphertext(
        const Plaintext& plaintext, const CiphertextDCRTPoly& ciphertext) const;
    void EvalAddInPlaceByCiphertextAndConst(CiphertextDCRTPoly& ciphertext,
        const double constant) const;
    void EvalAddInPlaceByCiphertextAndPlaintext(CiphertextDCRTPoly& ciphertext,
        const Plaintext& plaintext) const;
    void EvalAddInPlaceByCiphertexts(CiphertextDCRTPoly& ciphertext1,
        const CiphertextDCRTPoly& ciphertext2) const;
    void EvalAddInPlaceByConstAndCiphertext(const double constant,
        CiphertextDCRTPoly& ciphertext) const;
    void EvalAddInPlaceByPlaintextAndCiphertext(const Plaintext& plaintext,
        CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAddMany(
        const VectorOfCiphertexts& ciphertextVec) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAddManyInPlace(
        VectorOfCiphertexts& ciphertextVec) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAddMutableByCiphertextAndPlaintext(
        CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAddMutableByCiphertexts(
        CiphertextDCRTPoly& ciphertext1, CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAddMutableByPlaintextAndCiphertext(
        const Plaintext& plaintext, CiphertextDCRTPoly& ciphertext) const;
    void EvalAddMutableInPlace(CiphertextDCRTPoly& ciphertext1,
        CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAtIndex(
        const CiphertextDCRTPoly& ciphertext, const uint32_t index) const;
    void EvalAtIndexKeyGen(const PrivateKeyDCRTPoly& privateKey,
        const std::vector<int32_t>& indexList,
        const PublicKeyDCRTPoly& publicKey /* GenNullPublicKeyDCRTPoly() */) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalAutomorphism(
        const CiphertextDCRTPoly& ciphertext, const uint32_t i,
        const MapFromIndexToEvalKey& evalKeyMap) const;
    [[nodiscard]] std::unique_ptr<MapFromIndexToEvalKey> EvalAutomorphismKeyGen(
        const PrivateKeyDCRTPoly& privateKey, const std::vector<uint32_t>& indexList) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalBootstrap(
        const CiphertextDCRTPoly& ciphertext, const uint32_t numIterations /* 1 */,
        const uint32_t precision /* 0 */) const;
    void EvalBootstrapKeyGen(const PrivateKeyDCRTPoly& privateKey, const uint32_t slots) const;
    void EvalBootstrapPrecompute(const uint32_t slots /* 0 */) const;
    void EvalBootstrapSetup(const std::vector<uint32_t>& levelBudget /* {5, 4} */,
        const std::vector<uint32_t>& dim1 /* {0, 0} */, const uint32_t slots /* 0 */,
        const uint32_t correctionFactor /* 0 */, const bool precompute /* true */) const;
    [[nodiscard]] std::unique_ptr<VectorOfLWECiphertexts> EvalCKKStoFHEW(
        const CiphertextDCRTPoly& ciphertext, const uint32_t numCtxts /* 0 */) const;
    void EvalCKKStoFHEWKeyGen(const KeyPairDCRTPoly& keyPair, const LWEPrivateKey& lwesk) const;
    void EvalCKKStoFHEWPrecompute(const double scale /* 1.0 */) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalChebyshevFunction(
        rust::Fn<void(const double x, double& ret)> func, const CiphertextDCRTPoly& ciphertext,
        const double a, const double b, const uint32_t degree) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalChebyshevSeries(
        const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients,
        const double a, const double b) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalChebyshevSeriesLinear(
        const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients,
        const double a, const double b) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalChebyshevSeriesPS(
        const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients,
        const double a, const double b) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalCompareSchemeSwitching(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2,
        const uint32_t numCtxts /* 0 */, const uint32_t numSlots /* 0 */,
        const uint32_t pLWE /* 0 */, const double scaleSign /* 1.0 */,
        const bool unit /* false */) const;
    void EvalCompareSwitchPrecompute(const uint32_t pLWE /* 0 */, const double scaleSign /* 1.0 */,
        const bool unit /* false */) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalCos(const CiphertextDCRTPoly& ciphertext,
        const double a, const double b, const uint32_t degree) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalDivide(
        const CiphertextDCRTPoly& ciphertext, const double a, const double b,
        const uint32_t degree) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalFHEWtoCKKS(
        VectorOfLWECiphertexts& LWECiphertexts, const uint32_t numCtxts /* 0 */,
        const uint32_t numSlots /* 0 */, const uint32_t p /* 4 */, const double pmin /* 0.0 */,
        const double pmax /* 2.0 */, const uint32_t dim1 /* 0 */) const;
    void EvalFHEWtoCKKSKeyGen(const KeyPairDCRTPoly& keyPair, const LWEPrivateKey& lwesk,
        const uint32_t numSlots /* 0 */, const uint32_t numCtxts /* 0 */,
        const uint32_t dim1 /* 0 */, const uint32_t L /* 0 */) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalFastRotation(
        const CiphertextDCRTPoly& ciphertext, const uint32_t index, const uint32_t m,
        const VectorOfDCRTPolys& digits) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalFastRotationExt(
        const CiphertextDCRTPoly& ciphertext, const uint32_t index,
        const VectorOfDCRTPolys& digits, const bool addFirst) const;
    [[nodiscard]] std::unique_ptr<VectorOfDCRTPolys> EvalFastRotationPrecompute(
        const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalInnerProductByCiphertexts(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2,
        const uint32_t batchSize) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalInnerProductByCiphertextAndPlaintext(
        const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext,
        const uint32_t batchSize) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalInnerProductByPlaintextAndCiphertext(
        const Plaintext& plaintext, const CiphertextDCRTPoly& ciphertext,
        const uint32_t batchSize) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly>
        EvalLinearWSumMutableByConstantsAndVectorOfCiphertexts(
        const std::vector<double>& constantsVec, VectorOfCiphertexts& ciphertextVec) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly>
        EvalLinearWSumMutableByVectorOfCiphertextsAndConstants(
        VectorOfCiphertexts& ciphertextVec, const std::vector<double>& constantsVec) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalLogistic(
        const CiphertextDCRTPoly& ciphertext, const double a, const double b,
        const uint32_t degree) const;
    [[nodiscard]] std::unique_ptr<VectorOfCiphertexts> EvalMaxSchemeSwitching(
        const CiphertextDCRTPoly& ciphertext, const PublicKeyDCRTPoly& publicKey,
        const uint32_t numValues /* 0 */, const uint32_t numSlots /* 0 */,
        const uint32_t pLWE /* 0 */, const double scaleSign /* 1.0 */) const;
    [[nodiscard]] std::unique_ptr<VectorOfCiphertexts> EvalMaxSchemeSwitchingAlt(
        const CiphertextDCRTPoly& ciphertext, const PublicKeyDCRTPoly& publicKey,
        const uint32_t numValues /* 0 */, const uint32_t numSlots /* 0 */,
        const uint32_t pLWE /* 0 */, const double scaleSign /* 1.0 */) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMerge(
        const VectorOfCiphertexts& ciphertextVec) const;
    [[nodiscard]] std::unique_ptr<VectorOfCiphertexts> EvalMinSchemeSwitching(
        const CiphertextDCRTPoly& ciphertext, const PublicKeyDCRTPoly& publicKey,
        const uint32_t numValues /* 0 */, const uint32_t numSlots /* 0 */,
        const uint32_t pLWE /* 0 */, const double scaleSign /* 1.0 */) const;
    [[nodiscard]] std::unique_ptr<VectorOfCiphertexts> EvalMinSchemeSwitchingAlt(
        const CiphertextDCRTPoly& ciphertext, const PublicKeyDCRTPoly& publicKey,
        const uint32_t numValues /* 0 */, const uint32_t numSlots /* 0 */,
        const uint32_t pLWE /* 0 */, const double scaleSign /* 1.0 */) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultAndRelinearize(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultByCiphertextAndConst(
        const CiphertextDCRTPoly& ciphertext, const double constant) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultByCiphertextAndPlaintext(
        const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultByCiphertexts(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultByConstAndCiphertext(
        const double constant, const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultByPlaintextAndCiphertext(
        const Plaintext& plaintext, const CiphertextDCRTPoly& ciphertext) const;
    void EvalMultInPlaceByCiphertextAndConst(CiphertextDCRTPoly& ciphertext,
        const double constant) const;
    void EvalMultInPlaceByConstAndCiphertext(const double constant,
        CiphertextDCRTPoly& ciphertext) const;
    void EvalMultKeyGen(const PrivateKeyDCRTPoly& key) const;
    void EvalMultKeysGen(const PrivateKeyDCRTPoly& key) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultMany(
        const VectorOfCiphertexts& ciphertextVec) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultMutableByCiphertextAndPlaintext(
        CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultMutableByCiphertexts(
        CiphertextDCRTPoly& ciphertext1, CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultMutableByPlaintextAndCiphertext(
        const Plaintext& plaintext, CiphertextDCRTPoly& ciphertext) const;
    void EvalMultMutableInPlace(CiphertextDCRTPoly& ciphertext1,
         CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalMultNoRelin(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalNegate(
        const CiphertextDCRTPoly& ciphertext) const;
    void EvalNegateInPlace(CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalPoly(
        const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalPolyLinear(
        const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalPolyPS(
        const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalRotate(
        const CiphertextDCRTPoly& ciphertext, const int32_t index) const;
    void EvalRotateKeyGen(const PrivateKeyDCRTPoly& privateKey,
        const std::vector<int32_t>& indexList,
        const PublicKeyDCRTPoly& publicKey /* GenNullPublicKeyDCRTPoly() */) const;
    void EvalSchemeSwitchingKeyGen(const KeyPairDCRTPoly& keyPair,
        const LWEPrivateKey& lwesk) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSin(const CiphertextDCRTPoly& ciphertext,
        const double a, const double b, const uint32_t degree) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSquare(
        const CiphertextDCRTPoly& ciphertext) const;
    void EvalSquareInPlace(CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSquareMutable(
        CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSubByCiphertextAndConst(
        const CiphertextDCRTPoly& ciphertext, const double constant) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSubByCiphertextAndPlaintext(
        const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSubByCiphertexts(
        const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSubByConstAndCiphertext(
        const double constant, const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSubByPlaintextAndCiphertext(
        const Plaintext& plaintext, const CiphertextDCRTPoly& ciphertext) const;
    void EvalSubInPlaceByCiphertextAndConst(CiphertextDCRTPoly& ciphertext,
        const double constant) const;
    void EvalSubInPlaceByCiphertexts(CiphertextDCRTPoly& ciphertext1,
        const CiphertextDCRTPoly& ciphertext2) const;
    void EvalSubInPlaceByConstAndCiphertext(const double constant,
        CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSubMutableByCiphertextAndPlaintext(
        CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSubMutableByCiphertexts(
        CiphertextDCRTPoly& ciphertext1, CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSubMutableByPlaintextAndCiphertext(
        const Plaintext& plaintext, CiphertextDCRTPoly& ciphertext) const;
    void EvalSubMutableInPlace(CiphertextDCRTPoly& ciphertext1,
        CiphertextDCRTPoly& ciphertext2) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSum(const CiphertextDCRTPoly& ciphertext,
        const uint32_t batchSize) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSumCols(
        const CiphertextDCRTPoly& ciphertext, const uint32_t rowSize,
        const MapFromIndexToEvalKey& evalSumKeyMap) const;
    [[nodiscard]] std::unique_ptr<MapFromIndexToEvalKey> EvalSumColsKeyGen(
        const PrivateKeyDCRTPoly& privateKey,
        const PublicKeyDCRTPoly& publicKey /* GenNullPublicKeyDCRTPoly() */) const;
    void EvalSumKeyGen(const PrivateKeyDCRTPoly& privateKey,
        const PublicKeyDCRTPoly& publicKey /* GenNullPublicKeyDCRTPoly() */) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> EvalSumRows(
        const CiphertextDCRTPoly& ciphertext, const uint32_t rowSize,
        const MapFromIndexToEvalKey& evalSumKeyMap, const uint32_t subringDim /* 0 */) const;
    [[nodiscard]] std::unique_ptr<MapFromIndexToEvalKey> EvalSumRowsKeyGen(
        const PrivateKeyDCRTPoly& privateKey,
        const PublicKeyDCRTPoly& publicKey /* GenNullPublicKeyDCRTPoly() */,
        const uint32_t rowSize /* 0 */, const uint32_t subringDim /* 0 */) const;
    [[nodiscard]] uint32_t FindAutomorphismIndex(const uint32_t idx) const;
    [[nodiscard]] std::unique_ptr<std::vector<uint32_t>> FindAutomorphismIndices(
        const std::vector<uint32_t>& idxList) const;
    [[nodiscard]] std::unique_ptr<CryptoParametersBaseDCRTPoly> GetCryptoParameters() const;
    [[nodiscard]] uint32_t GetCyclotomicOrder() const;
    [[nodiscard]] std::unique_ptr<DCRTPolyParams> GetElementParams() const;
    [[nodiscard]] std::unique_ptr<EncodingParams> GetEncodingParams() const;
    [[nodiscard]] size_t GetKeyGenLevel() const;
    [[nodiscard]] uint64_t GetModulus() const;
    [[nodiscard]] uint32_t GetRingDimension() const;
    [[nodiscard]] uint64_t GetRootOfUnity() const;
    [[nodiscard]] std::unique_ptr<SchemeBaseDCRTPoly> GetScheme() const;
    [[nodiscard]] SCHEME GetSchemeId() const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> GetSwkFC() const;
    [[nodiscard]] std::unique_ptr<VectorOfCiphertexts> IntMPBootAdd(
        VectorOfVectorOfCiphertexts& sharesPairVec) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> IntMPBootAdjustScale(
        const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<VectorOfCiphertexts> IntMPBootDecrypt(
        const PrivateKeyDCRTPoly& privateKey, const CiphertextDCRTPoly& ciphertext,
        const CiphertextDCRTPoly& a) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> IntMPBootEncrypt(
        const PublicKeyDCRTPoly& publicKey, const VectorOfCiphertexts& sharesPair,
        const CiphertextDCRTPoly& a, const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> IntMPBootRandomElementGen(
        const PublicKeyDCRTPoly& publicKey) const;
    [[nodiscard]] std::unique_ptr<KeyPairDCRTPoly> KeyGen() const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> KeySwitch(
        const CiphertextDCRTPoly& ciphertext, const EvalKeyDCRTPoly& evalKey) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> KeySwitchDown(
        const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<DCRTPoly> KeySwitchDownFirstElement(
        const CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> KeySwitchExt(
        const CiphertextDCRTPoly& ciphertext, const bool addFirst) const;
    [[nodiscard]] std::unique_ptr<EvalKeyDCRTPoly> KeySwitchGen(
        const PrivateKeyDCRTPoly& oldPrivateKey, const PrivateKeyDCRTPoly& newPrivateKey) const;
    void KeySwitchInPlace(CiphertextDCRTPoly& ciphertext, const EvalKeyDCRTPoly& evalKey) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> LevelReduce(
        const CiphertextDCRTPoly& ciphertext, const EvalKeyDCRTPoly& evalKey,
        const size_t levels /* 1 */) const;
    void LevelReduceInPlace(CiphertextDCRTPoly& ciphertext, const EvalKeyDCRTPoly& evalKey,
        const size_t levels /* 1 */) const;
    [[nodiscard]] std::unique_ptr<Plaintext> MakeCKKSPackedPlaintextByVectorOfDouble(
        const std::vector<double>& value, const size_t scaleDeg /* 1 */,
        const uint32_t level /* 0 */, const DCRTPolyParams& params /* GenNullDCRTPolyParams() */,
        const uint32_t slots /* 0 */) const;
    [[nodiscard]] std::unique_ptr<Plaintext> MakeCKKSPackedPlaintextByVectorOfComplex(
        const std::vector<ComplexPair>& value, const size_t scaleDeg /* 1 */,
        const uint32_t level /* 0 */, const DCRTPolyParams& params /* GenNullDCRTPolyParams() */,
        const uint32_t slots /* 0 */) const;
    [[nodiscard]] std::unique_ptr<Plaintext> MakeCoefPackedPlaintext(
        const std::vector<int64_t>& value, const size_t noiseScaleDeg /* 1 */,
        const uint32_t level /* 0 */) const;
    [[nodiscard]] std::unique_ptr<Plaintext> MakePackedPlaintext(
        const std::vector<int64_t>& value, const size_t noiseScaleDeg /* 1 */,
        const uint32_t level /* 0 */) const;
    [[nodiscard]] std::unique_ptr<Plaintext> MakeStringPlaintext(const std::string& s) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> ModReduce(
        const CiphertextDCRTPoly& ciphertext) const;
    void ModReduceInPlace(CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<MapFromIndexToEvalKey> MultiAddEvalAutomorphismKeys(
        const MapFromIndexToEvalKey& evalKeyMap1, const MapFromIndexToEvalKey& evalKeyMap2,
        const std::string& keyId /* "" */) const;
    [[nodiscard]] std::unique_ptr<EvalKeyDCRTPoly> MultiAddEvalKeys(
        const EvalKeyDCRTPoly& evalKey1, const EvalKeyDCRTPoly& evalKey2,
        const std::string& keyId /* "" */) const;
    [[nodiscard]] std::unique_ptr<EvalKeyDCRTPoly> MultiAddEvalMultKeys(
        const EvalKeyDCRTPoly& evalKey1, const EvalKeyDCRTPoly& evalKey2,
        const std::string& keyId /* "" */) const;
    [[nodiscard]] std::unique_ptr<MapFromIndexToEvalKey> MultiAddEvalSumKeys(
        const MapFromIndexToEvalKey& evalKeyMap1, const MapFromIndexToEvalKey& evalKeyMap2,
        const std::string& keyId /* "" */) const;
    [[nodiscard]] std::unique_ptr<PublicKeyDCRTPoly> MultiAddPubKeys(
        const PublicKeyDCRTPoly& publicKey1, const PublicKeyDCRTPoly& publicKey2,
        const std::string& keyId /* "" */) const;
    [[nodiscard]] std::unique_ptr<MapFromIndexToEvalKey> MultiEvalAtIndexKeyGen(
        const PrivateKeyDCRTPoly& privateKey, const MapFromIndexToEvalKey& evalKeyMap,
        const std::vector<int32_t>& indexList, const std::string& keyId /* "" */) const;
    [[nodiscard]] std::unique_ptr<MapFromIndexToEvalKey> MultiEvalAutomorphismKeyGen(
        const PrivateKeyDCRTPoly& privateKey, const MapFromIndexToEvalKey& evalKeyMap,
        const std::vector<uint32_t>& indexList, const std::string& keyId /* "" */) const;
    [[nodiscard]] std::unique_ptr<MapFromIndexToEvalKey> MultiEvalSumKeyGen(
        const PrivateKeyDCRTPoly& privateKey, const MapFromIndexToEvalKey& evalKeyMap,
        const std::string& keyId /* "" */) const;
    [[nodiscard]] std::unique_ptr<EvalKeyDCRTPoly> MultiKeySwitchGen(
        const PrivateKeyDCRTPoly& originalPrivateKey, const PrivateKeyDCRTPoly& newPrivateKey,
        const EvalKeyDCRTPoly& evalKey) const;
    [[nodiscard]] std::unique_ptr<EvalKeyDCRTPoly> MultiMultEvalKey(
        const PrivateKeyDCRTPoly& privateKey, const EvalKeyDCRTPoly& evalKey,
        const std::string& keyId /* "" */) const;
    [[nodiscard]] std::unique_ptr<DecryptResult> MultipartyDecryptFusion(
        const VectorOfCiphertexts& partialCiphertextVec, Plaintext& plaintext) const;
    [[nodiscard]] std::unique_ptr<VectorOfCiphertexts> MultipartyDecryptLead(
        const VectorOfCiphertexts& ciphertextVec, const PrivateKeyDCRTPoly& privateKey) const;
    [[nodiscard]] std::unique_ptr<VectorOfCiphertexts> MultipartyDecryptMain(
        const VectorOfCiphertexts& ciphertextVec, const PrivateKeyDCRTPoly& privateKey) const;
    [[nodiscard]] std::unique_ptr<KeyPairDCRTPoly> MultipartyKeyGenByPublicKey(
        const PublicKeyDCRTPoly& publicKey, const bool makeSparse /* false */,
        const bool fresh /* false */) const;
    [[nodiscard]] std::unique_ptr<KeyPairDCRTPoly> MultipartyKeyGenByVectorOfPrivateKeys(
        const VectorOfPrivateKeys& privateKeyVec) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> ReEncrypt(
        const CiphertextDCRTPoly& ciphertext, const EvalKeyDCRTPoly& evalKey,
        const PublicKeyDCRTPoly& publicKey /* GenNullPublicKeyDCRTPoly() */) const;
    [[nodiscard]] std::unique_ptr<EvalKeyDCRTPoly> ReKeyGen(
        const PrivateKeyDCRTPoly& oldPrivateKey, const PublicKeyDCRTPoly& newPublicKey) const;
    void RecoverSharedKey(PrivateKeyDCRTPoly& sk, UnorderedMapFromIndexToDCRTPoly& sk_shares,
        const uint32_t N, const uint32_t threshold, const std::string& shareType) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> Relinearize(
        const CiphertextDCRTPoly& ciphertext) const;
    void RelinearizeInPlace(CiphertextDCRTPoly& ciphertext) const;
    [[nodiscard]] std::unique_ptr<CiphertextDCRTPoly> Rescale(
        const CiphertextDCRTPoly& ciphertext) const;
    void RescaleInPlace(CiphertextDCRTPoly& ciphertext) const;
    void SetKeyGenLevel(const size_t level) const;
    void SetSchemeId(const SCHEME schemeTag) const;
    void SetSwkFC(const CiphertextDCRTPoly& FHEWtoCKKSswk) const;
    [[nodiscard]] std::unique_ptr<UnorderedMapFromIndexToDCRTPoly> ShareKeys(
        const PrivateKeyDCRTPoly& sk, const uint32_t N, const uint32_t threshold,
        const uint32_t index, const std::string& shareType) const;
    [[nodiscard]] std::unique_ptr<KeyPairDCRTPoly> SparseKeyGen() const;

    [[nodiscard]] const std::shared_ptr<CryptoContextImpl>& GetRef() const noexcept;
    [[nodiscard]] std::shared_ptr<CryptoContextImpl>& GetRef() noexcept;
};

// cxx currently does not support static class methods
void DCRTPolyClearEvalAutomorphismKeys();
void DCRTPolyClearEvalAutomorphismKeysByCryptoContext(const CryptoContextDCRTPoly& cryptoContext);
void DCRTPolyClearEvalAutomorphismKeysById(const std::string& id);
void DCRTPolyClearEvalMultKeys();
void DCRTPolyClearEvalMultKeysByCryptoContext(const CryptoContextDCRTPoly& cryptoContext);
void DCRTPolyClearEvalMultKeysById(const std::string& id);
void DCRTPolyClearEvalSumKeys();
void DCRTPolyClearEvalSumKeysByCryptoContext(const CryptoContextDCRTPoly& cryptoContext);
void DCRTPolyClearEvalSumKeysById(const std::string& id);
[[nodiscard]] std::unique_ptr<MapFromStringToMapFromIndexToEvalKey>
    DCRTPolyGetCopyOfAllEvalAutomorphismKeys();
[[nodiscard]] std::unique_ptr<MapFromStringToVectorOfEvalKeys> DCRTPolyGetCopyOfAllEvalMultKeys();
[[nodiscard]] std::unique_ptr<MapFromStringToMapFromIndexToEvalKey>
    DCRTPolyGetCopyOfAllEvalSumKeys();
[[nodiscard]] std::unique_ptr<MapFromIndexToEvalKey> DCRTPolyGetCopyOfEvalAutomorphismKeyMap(
    const std::string& keyID);
[[nodiscard]] std::unique_ptr<VectorOfEvalKeys> DCRTPolyGetCopyOfEvalMultKeyVector(
    const std::string& keyID);
[[nodiscard]] std::unique_ptr<MapFromIndexToEvalKey> DCRTPolyGetCopyOfEvalSumKeyMap(
    const std::string& id);
[[nodiscard]] std::unique_ptr<SetOfUints> DCRTPolyGetExistingEvalAutomorphismKeyIndices(
    const std::string& keyTag);
[[nodiscard]] std::unique_ptr<Plaintext> DCRTPolyGetPlaintextForDecrypt(
    const PlaintextEncodings pte, const DCRTPolyParams& evp, const EncodingParams& ep);
[[nodiscard]] std::unique_ptr<SetOfUints> DCRTPolyGetUniqueValues(
    const SetOfUints& oldValues, const SetOfUints& newValues);
void DCRTPolyInsertEvalAutomorphismKey(const MapFromIndexToEvalKey& evalKeyMap,
    const std::string& keyTag /* "" */);
void DCRTPolyInsertEvalMultKey(const VectorOfEvalKeys& evalKeyVec);
void DCRTPolyInsertEvalSumKey(const MapFromIndexToEvalKey& mapToInsert,
    const std::string& keyTag /* "" */);

// Generator functions
[[nodiscard]] std::unique_ptr<CryptoContextDCRTPoly> DCRTPolyGenCryptoContextByParamsBFVRNS(
    const ParamsBFVRNS& params);
[[nodiscard]] std::unique_ptr<CryptoContextDCRTPoly> DCRTPolyGenCryptoContextByParamsBGVRNS(
    const ParamsBGVRNS& params);
[[nodiscard]] std::unique_ptr<CryptoContextDCRTPoly> DCRTPolyGenCryptoContextByParamsCKKSRNS(
    const ParamsCKKSRNS& params);
[[nodiscard]] std::unique_ptr<CryptoContextDCRTPoly> DCRTPolyGenNullCryptoContext();

} // openfhe
