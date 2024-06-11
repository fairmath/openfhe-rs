#include "CryptoContext.h"

#include "openfhe/pke/gen-cryptocontext.h"
#include "openfhe/pke/scheme/bfvrns/gen-cryptocontext-bfvrns.h"
#include "openfhe/pke/scheme/bgvrns/gen-cryptocontext-bgvrns.h"
#include "openfhe/pke/scheme/ckksrns/gen-cryptocontext-ckksrns.h"

#include "openfhe/src/lib.rs.h"

#include "AssociativeContainers.h"
#include "Ciphertext.h"
#include "CryptoParametersBase.h"
#include "DCRTPoly.h"
#include "DecryptResult.h"
#include "EncodingParams.h"
#include "EvalKey.h"
#include "KeyPair.h"
#include "LWEPrivateKey.h"
#include "Plaintext.h"
#include "PrivateKey.h"
#include "PublicKey.h"
#include "SchemeBase.h"
#include "SequenceContainers.h"

namespace openfhe
{

using PlaintextImpl = lbcrypto::PlaintextImpl;

CryptoContextDCRTPoly::CryptoContextDCRTPoly(const ParamsCKKSRNS& params)
    : m_cryptoContextImplSharedPtr(lbcrypto::GenCryptoContext(params))
{ }
CryptoContextDCRTPoly::CryptoContextDCRTPoly(const ParamsBFVRNS& params)
    : m_cryptoContextImplSharedPtr(lbcrypto::GenCryptoContext(params))
{ }
CryptoContextDCRTPoly::CryptoContextDCRTPoly(const ParamsBGVRNS& params)
    : m_cryptoContextImplSharedPtr(lbcrypto::GenCryptoContext(params))
{ }

std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::ComposedEvalMult(
    const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->ComposedEvalMult(ciphertext1.GetRef(),
        ciphertext2.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::Compress(
    const CiphertextDCRTPoly& ciphertext, const uint32_t towersLeft) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->Compress(
        ciphertext.GetRef(), towersLeft));
}
std::unique_ptr<DecryptResult> CryptoContextDCRTPoly::DecryptByCiphertextAndPrivateKey(
    const CiphertextDCRTPoly& ciphertext, const PrivateKeyDCRTPoly& privateKey,
    Plaintext& plaintext) const
{
    return std::make_unique<DecryptResult>(m_cryptoContextImplSharedPtr->Decrypt(
        ciphertext.GetRef(), privateKey.GetRef(), &plaintext.GetRef()));
}
std::unique_ptr<DecryptResult> CryptoContextDCRTPoly::DecryptByPrivateKeyAndCiphertext(
    const PrivateKeyDCRTPoly& privateKey, const CiphertextDCRTPoly& ciphertext,
    Plaintext& plaintext) const
{
    return std::make_unique<DecryptResult>(m_cryptoContextImplSharedPtr->Decrypt(
        privateKey.GetRef(), ciphertext.GetRef(), &plaintext.GetRef()));
}
void CryptoContextDCRTPoly::EnableByFeature(const PKESchemeFeature feature) const
{
    m_cryptoContextImplSharedPtr->Enable(feature);
}
void CryptoContextDCRTPoly::EnableByMask(const uint32_t featureMask) const
{
    m_cryptoContextImplSharedPtr->Enable(featureMask);
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EncryptByPrivateKey(
    const PrivateKeyDCRTPoly& privateKey, const Plaintext& plaintext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->Encrypt(
        privateKey.GetRef(), plaintext.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EncryptByPublicKey(
    const PublicKeyDCRTPoly& publicKey, const Plaintext& plaintext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->Encrypt(
        publicKey.GetRef(), plaintext.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAddByCiphertextAndConst(
    const CiphertextDCRTPoly& ciphertext, const double constant) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAdd(
        ciphertext.GetRef(), constant));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAddByCiphertextAndPlaintext(
    const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAdd(
        ciphertext.GetRef(), plaintext.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAddByCiphertexts(
    const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAdd(
        ciphertext1.GetRef(), ciphertext2.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAddByConstAndCiphertext(
    const double constant, const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAdd(constant,
        ciphertext.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAddByPlaintextAndCiphertext(
    const Plaintext& plaintext, const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAdd(
        plaintext.GetRef(), ciphertext.GetRef()));
}
void CryptoContextDCRTPoly::EvalAddInPlaceByCiphertextAndConst(CiphertextDCRTPoly& ciphertext,
    const double constant) const
{
    m_cryptoContextImplSharedPtr->EvalAddInPlace(ciphertext.GetRef(), constant);
}
void CryptoContextDCRTPoly::EvalAddInPlaceByCiphertextAndPlaintext(CiphertextDCRTPoly& ciphertext,
    const Plaintext& plaintext) const
{
    m_cryptoContextImplSharedPtr->EvalAddInPlace(ciphertext.GetRef(), plaintext.GetRef());
}
void CryptoContextDCRTPoly::EvalAddInPlaceByCiphertexts(CiphertextDCRTPoly& ciphertext1,
    const CiphertextDCRTPoly& ciphertext2) const
{
    m_cryptoContextImplSharedPtr->EvalAddInPlace(ciphertext1.GetRef(), ciphertext2.GetRef());
}
void CryptoContextDCRTPoly::EvalAddInPlaceByConstAndCiphertext(const double constant,
    CiphertextDCRTPoly& ciphertext) const
{
    m_cryptoContextImplSharedPtr->EvalAddInPlace(constant, ciphertext.GetRef());
}
void CryptoContextDCRTPoly::EvalAddInPlaceByPlaintextAndCiphertext(const Plaintext& plaintext,
    CiphertextDCRTPoly& ciphertext) const
{
    m_cryptoContextImplSharedPtr->EvalAddInPlace(plaintext.GetRef(), ciphertext.GetRef());
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAddMany(
    const VectorOfCiphertexts& ciphertextVec) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAddMany(
        ciphertextVec.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAddManyInPlace(
    VectorOfCiphertexts& ciphertextVec) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAddManyInPlace(
        ciphertextVec.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAddMutableByCiphertextAndPlaintext(
    CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAddMutable(
        ciphertext.GetRef(), plaintext.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAddMutableByCiphertexts(
    CiphertextDCRTPoly& ciphertext1, CiphertextDCRTPoly& ciphertext2) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAddMutable(
        ciphertext1.GetRef(), ciphertext2.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAddMutableByPlaintextAndCiphertext(
    const Plaintext& plaintext, CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAddMutable(
        plaintext.GetRef(), ciphertext.GetRef()));
}
void CryptoContextDCRTPoly::EvalAddMutableInPlace(CiphertextDCRTPoly& ciphertext1,
    CiphertextDCRTPoly& ciphertext2) const
{
    m_cryptoContextImplSharedPtr->EvalAddMutableInPlace(ciphertext1.GetRef(),
        ciphertext2.GetRef());
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAtIndex(
    const CiphertextDCRTPoly& ciphertext, const uint32_t index) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAtIndex(
        ciphertext.GetRef(), index));
}
void CryptoContextDCRTPoly::EvalAtIndexKeyGen(const PrivateKeyDCRTPoly& privateKey,
    const std::vector<int32_t>& indexList, const PublicKeyDCRTPoly& publicKey) const
{
    m_cryptoContextImplSharedPtr->EvalAtIndexKeyGen(privateKey.GetRef(), indexList,
        publicKey.GetRef());
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAutomorphism(
    const CiphertextDCRTPoly& ciphertext, const uint32_t i,
    const MapFromIndexToEvalKey& evalKeyMap) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAutomorphism(
        ciphertext.GetRef(), i, *evalKeyMap.GetRef()));
}
std::unique_ptr<MapFromIndexToEvalKey> CryptoContextDCRTPoly::EvalAutomorphismKeyGen(
    const PrivateKeyDCRTPoly& privateKey, const std::vector<uint32_t>& indexList) const
{
    return std::make_unique<MapFromIndexToEvalKey>(
        m_cryptoContextImplSharedPtr->EvalAutomorphismKeyGen(privateKey.GetRef(), indexList));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalBootstrap(
    const CiphertextDCRTPoly& ciphertext, const uint32_t numIterations,
    const uint32_t precision) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalBootstrap(
        ciphertext.GetRef(), numIterations, precision));
}
void CryptoContextDCRTPoly::EvalBootstrapKeyGen(const PrivateKeyDCRTPoly& privateKey,
    const uint32_t slots) const
{
    m_cryptoContextImplSharedPtr->EvalBootstrapKeyGen(privateKey.GetRef(), slots);
}
void CryptoContextDCRTPoly::EvalBootstrapPrecompute(const uint32_t slots) const
{
    m_cryptoContextImplSharedPtr->EvalBootstrapPrecompute(slots);
}
void CryptoContextDCRTPoly::EvalBootstrapSetup(const std::vector<uint32_t>& levelBudget,
    const std::vector<uint32_t>& dim1, const uint32_t slots, const uint32_t correctionFactor,
    const bool precompute) const
{
    m_cryptoContextImplSharedPtr->EvalBootstrapSetup(levelBudget, dim1, slots, correctionFactor,
        precompute);
}
std::unique_ptr<VectorOfLWECiphertexts> CryptoContextDCRTPoly::EvalCKKStoFHEW(
    const CiphertextDCRTPoly& ciphertext, const uint32_t numCtxts) const
{
    return std::make_unique<VectorOfLWECiphertexts>(m_cryptoContextImplSharedPtr->EvalCKKStoFHEW(
        ciphertext.GetRef(), numCtxts));
}
void CryptoContextDCRTPoly::EvalCKKStoFHEWKeyGen(const KeyPairDCRTPoly& keyPair,
    const LWEPrivateKey& lwesk) const
{
    m_cryptoContextImplSharedPtr->EvalCKKStoFHEWKeyGen(keyPair.GetRef(), lwesk.GetRef());
}
void CryptoContextDCRTPoly::EvalCKKStoFHEWPrecompute(const double scale) const
{
    m_cryptoContextImplSharedPtr->EvalCKKStoFHEWPrecompute(scale);
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalChebyshevFunction(
    rust::Fn<void(const double x, double& ret)> func, const CiphertextDCRTPoly& ciphertext,
    const double a, const double b, const uint32_t degree) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalChebyshevFunction([&](const double x){
        double result; func(x, result); return result; }, ciphertext.GetRef(), a, b, degree));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalChebyshevSeries(
    const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients,
    const double a, const double b) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalChebyshevSeries(
        ciphertext.GetRef(), coefficients, a, b));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalChebyshevSeriesLinear(
    const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients,
    const double a, const double b) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalChebyshevSeriesLinear(ciphertext.GetRef(), coefficients,
        a, b));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalChebyshevSeriesPS(
    const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients, const double a,
    const double b) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalChebyshevSeriesPS(ciphertext.GetRef(), coefficients, a,
        b));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalCompareSchemeSwitching(
    const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2,
    const uint32_t numCtxts, const uint32_t numSlots, const uint32_t pLWE, const double scaleSign,
    const bool unit) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalCompareSchemeSwitching(ciphertext1.GetRef(),
        ciphertext2.GetRef(), numCtxts, numSlots, pLWE, scaleSign, unit));
}
void CryptoContextDCRTPoly::EvalCompareSwitchPrecompute(const uint32_t pLWE,
    const double scaleSign, const bool unit) const
{
    m_cryptoContextImplSharedPtr->EvalCompareSwitchPrecompute(pLWE, scaleSign, unit);
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalCos(
    const CiphertextDCRTPoly& ciphertext, const double a, const double b,
    const uint32_t degree) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalCos(
        ciphertext.GetRef(), a, b, degree));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalDivide(
    const CiphertextDCRTPoly& ciphertext, const double a, const double b,
    const uint32_t degree) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalDivide(
        ciphertext.GetRef(), a, b, degree));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalFHEWtoCKKS(
    VectorOfLWECiphertexts& LWECiphertexts, const uint32_t numCtxts, const uint32_t numSlots,
    const uint32_t p, const double pmin, const double pmax, const uint32_t dim1) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalFHEWtoCKKS(
        LWECiphertexts.GetRef(), numCtxts, numSlots, p, pmin, pmax, dim1));
}
void CryptoContextDCRTPoly::EvalFHEWtoCKKSKeyGen(const KeyPairDCRTPoly& keyPair,
    const LWEPrivateKey& lwesk, const uint32_t numSlots, const uint32_t numCtxts,
    const uint32_t dim1, const uint32_t L) const
{
    m_cryptoContextImplSharedPtr->EvalFHEWtoCKKSKeyGen(keyPair.GetRef(), lwesk.GetRef(), numSlots,
        numCtxts, dim1, L);
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalFastRotation(
    const CiphertextDCRTPoly& ciphertext, const uint32_t index, const uint32_t m,
    const VectorOfDCRTPolys& digits) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalFastRotation(
        ciphertext.GetRef(), index, m, digits.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalFastRotationExt(
    const CiphertextDCRTPoly& ciphertext, const uint32_t index, const VectorOfDCRTPolys& digits,
    const bool addFirst) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalFastRotationExt(
        ciphertext.GetRef(), index, digits.GetRef(), addFirst));
}
std::unique_ptr<VectorOfDCRTPolys> CryptoContextDCRTPoly::EvalFastRotationPrecompute(
    const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<VectorOfDCRTPolys>(
        m_cryptoContextImplSharedPtr->EvalFastRotationPrecompute(ciphertext.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalInnerProductByCiphertexts(
    const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2,
    const uint32_t batchSize) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalInnerProduct(
        ciphertext1.GetRef(), ciphertext2.GetRef(), batchSize));
}
std::unique_ptr<CiphertextDCRTPoly>
    CryptoContextDCRTPoly::EvalInnerProductByCiphertextAndPlaintext(
    const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext,
    const uint32_t batchSize) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalInnerProduct(
        ciphertext.GetRef(), plaintext.GetRef(), batchSize));
}
std::unique_ptr<CiphertextDCRTPoly>
    CryptoContextDCRTPoly::EvalInnerProductByPlaintextAndCiphertext(const Plaintext& plaintext,
    const CiphertextDCRTPoly& ciphertext, const uint32_t batchSize) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalInnerProduct(
        ciphertext.GetRef(), plaintext.GetRef(), batchSize));
}
std::unique_ptr<CiphertextDCRTPoly>
    CryptoContextDCRTPoly::EvalLinearWSumMutableByConstantsAndVectorOfCiphertexts(
    const std::vector<double>& constantsVec, VectorOfCiphertexts& ciphertextVec) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalLinearWSumMutable(constantsVec, ciphertextVec.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly>
    CryptoContextDCRTPoly::EvalLinearWSumMutableByVectorOfCiphertextsAndConstants(
    VectorOfCiphertexts& ciphertextVec, const std::vector<double>& constantsVec) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalLinearWSumMutable(ciphertextVec.GetRef(), constantsVec));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalLogistic(
    const CiphertextDCRTPoly& ciphertext, const double a, const double b,
    const uint32_t degree) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalLogistic(
        ciphertext.GetRef(), a, b, degree));
}
std::unique_ptr<VectorOfCiphertexts> CryptoContextDCRTPoly::EvalMaxSchemeSwitching(
    const CiphertextDCRTPoly& ciphertext, const PublicKeyDCRTPoly& publicKey,
    const uint32_t numValues, const uint32_t numSlots, const uint32_t pLWE,
    const double scaleSign) const
{
    return std::make_unique<VectorOfCiphertexts>(
        m_cryptoContextImplSharedPtr->EvalMaxSchemeSwitching(ciphertext.GetRef(),
        publicKey.GetRef(), numValues, numSlots, pLWE, scaleSign));
}
std::unique_ptr<VectorOfCiphertexts> CryptoContextDCRTPoly::EvalMaxSchemeSwitchingAlt(
    const CiphertextDCRTPoly& ciphertext, const PublicKeyDCRTPoly& publicKey,
    const uint32_t numValues, const uint32_t numSlots, const uint32_t pLWE,
    const double scaleSign) const
{
    return std::make_unique<VectorOfCiphertexts>(
        m_cryptoContextImplSharedPtr->EvalMaxSchemeSwitchingAlt(ciphertext.GetRef(),
        publicKey.GetRef(), numValues, numSlots, pLWE, scaleSign));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMerge(
    const VectorOfCiphertexts& ciphertextVec) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMerge(
        ciphertextVec.GetRef()));
}
std::unique_ptr<VectorOfCiphertexts> CryptoContextDCRTPoly::EvalMinSchemeSwitching(
    const CiphertextDCRTPoly& ciphertext, const PublicKeyDCRTPoly& publicKey,
    const uint32_t numValues, const uint32_t numSlots, const uint32_t pLWE,
    const double scaleSign) const
{
    return std::make_unique<VectorOfCiphertexts>(
        m_cryptoContextImplSharedPtr->EvalMinSchemeSwitching(ciphertext.GetRef(),
        publicKey.GetRef(), numValues, numSlots, pLWE, scaleSign));
}
std::unique_ptr<VectorOfCiphertexts> CryptoContextDCRTPoly::EvalMinSchemeSwitchingAlt(
    const CiphertextDCRTPoly& ciphertext, const PublicKeyDCRTPoly& publicKey,
    const uint32_t numValues, const uint32_t numSlots, const uint32_t pLWE,
    const double scaleSign) const
{
    return std::make_unique<VectorOfCiphertexts>(
        m_cryptoContextImplSharedPtr->EvalMinSchemeSwitchingAlt(ciphertext.GetRef(),
        publicKey.GetRef(), numValues, numSlots, pLWE, scaleSign));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultAndRelinearize(
    const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalMultAndRelinearize(ciphertext1.GetRef(),
        ciphertext2.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultByCiphertextAndConst(
    const CiphertextDCRTPoly& ciphertext, const double constant) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMult(
        ciphertext.GetRef(), constant));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultByCiphertextAndPlaintext(
    const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMult(
        ciphertext.GetRef(), plaintext.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultByCiphertexts(
    const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMult(
        ciphertext1.GetRef(), ciphertext2.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultByConstAndCiphertext(
    const double constant, const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMult(
        constant, ciphertext.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultByPlaintextAndCiphertext(
    const Plaintext& plaintext, const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMult(
        plaintext.GetRef(), ciphertext.GetRef()));
}
void CryptoContextDCRTPoly::EvalMultInPlaceByCiphertextAndConst(CiphertextDCRTPoly& ciphertext,
    const double constant) const
{
    m_cryptoContextImplSharedPtr->EvalMultInPlace(ciphertext.GetRef(), constant);
}
void CryptoContextDCRTPoly::EvalMultInPlaceByConstAndCiphertext(const double constant,
    CiphertextDCRTPoly& ciphertext) const
{
    m_cryptoContextImplSharedPtr->EvalMultInPlace(constant, ciphertext.GetRef());
}
void CryptoContextDCRTPoly::EvalMultKeyGen(const PrivateKeyDCRTPoly& key) const
{
    m_cryptoContextImplSharedPtr->EvalMultKeyGen(key.GetRef());
}
void CryptoContextDCRTPoly::EvalMultKeysGen(const PrivateKeyDCRTPoly& key) const
{
    m_cryptoContextImplSharedPtr->EvalMultKeysGen(key.GetRef());
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultMany(
    const VectorOfCiphertexts& ciphertextVec) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMultMany(
        ciphertextVec.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultMutableByCiphertextAndPlaintext(
    CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMultMutable(
        ciphertext.GetRef(), plaintext.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultMutableByCiphertexts(
    CiphertextDCRTPoly& ciphertext1, CiphertextDCRTPoly& ciphertext2) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMultMutable(
        ciphertext1.GetRef(), ciphertext2.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultMutableByPlaintextAndCiphertext(
    const Plaintext& plaintext, CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMultMutable(
        plaintext.GetRef(), ciphertext.GetRef()));
}
void CryptoContextDCRTPoly::EvalMultMutableInPlace(CiphertextDCRTPoly& ciphertext1,
    CiphertextDCRTPoly& ciphertext2) const
{
    m_cryptoContextImplSharedPtr->EvalMultMutableInPlace(ciphertext1.GetRef(),
        ciphertext2.GetRef());
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultNoRelin(
    const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMultNoRelin(
        ciphertext1.GetRef(), ciphertext2.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalNegate(
    const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalNegate(
        ciphertext.GetRef()));
}
void CryptoContextDCRTPoly::EvalNegateInPlace(CiphertextDCRTPoly& ciphertext) const
{
    m_cryptoContextImplSharedPtr->EvalNegateInPlace(ciphertext.GetRef());
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalPoly(
    const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalPoly(
        ciphertext.GetRef(), coefficients));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalPolyLinear(
    const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalPolyLinear(
        ciphertext.GetRef(), coefficients));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalPolyPS(
    const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalPolyPS(
        ciphertext.GetRef(), coefficients));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalRotate(
    const CiphertextDCRTPoly& ciphertext, const int32_t index) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalRotate(
        ciphertext.GetRef(), index));
}
void CryptoContextDCRTPoly::EvalRotateKeyGen(const PrivateKeyDCRTPoly& privateKey,
    const std::vector<int32_t>& indexList, const PublicKeyDCRTPoly& publicKey) const
{
    m_cryptoContextImplSharedPtr->EvalRotateKeyGen(privateKey.GetRef(), indexList,
        publicKey.GetRef());
}
void CryptoContextDCRTPoly::EvalSchemeSwitchingKeyGen(const KeyPairDCRTPoly& keyPair,
    const LWEPrivateKey& lwesk) const
{
    m_cryptoContextImplSharedPtr->EvalSchemeSwitchingKeyGen(keyPair.GetRef(), lwesk.GetRef());
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSin(
    const CiphertextDCRTPoly& ciphertext, const double a, const double b,
    const uint32_t degree) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSin(
        ciphertext.GetRef(), a, b, degree));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSquare(
    const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSquare(
        ciphertext.GetRef()));
}
void CryptoContextDCRTPoly::EvalSquareInPlace(CiphertextDCRTPoly& ciphertext) const
{
    m_cryptoContextImplSharedPtr->EvalSquareInPlace(ciphertext.GetRef());
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSquareMutable(
    CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSquareMutable(
        ciphertext.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSubByCiphertextAndConst(
    const CiphertextDCRTPoly& ciphertext, const double constant) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSub(
        ciphertext.GetRef(), constant));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSubByCiphertextAndPlaintext(
    const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSub(
        ciphertext.GetRef(), plaintext.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSubByCiphertexts(
    const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSub(
        ciphertext1.GetRef(), ciphertext2.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSubByConstAndCiphertext(
    const double constant, const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSub(
        constant, ciphertext.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSubByPlaintextAndCiphertext(
    const Plaintext& plaintext, const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSub(
        plaintext.GetRef(), ciphertext.GetRef()));
}
void CryptoContextDCRTPoly::EvalSubInPlaceByCiphertextAndConst(CiphertextDCRTPoly& ciphertext,
    const double constant) const
{
    m_cryptoContextImplSharedPtr->EvalSubInPlace(ciphertext.GetRef(), constant);
}
void CryptoContextDCRTPoly::EvalSubInPlaceByCiphertexts(CiphertextDCRTPoly& ciphertext1,
    const CiphertextDCRTPoly& ciphertext2) const
{
    m_cryptoContextImplSharedPtr->EvalSubInPlace(ciphertext1.GetRef(), ciphertext2.GetRef());
}
void CryptoContextDCRTPoly::EvalSubInPlaceByConstAndCiphertext(const double constant,
    CiphertextDCRTPoly& ciphertext) const
{
    m_cryptoContextImplSharedPtr->EvalSubInPlace(constant, ciphertext.GetRef());
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSubMutableByCiphertextAndPlaintext(
    CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSubMutable(
        ciphertext.GetRef(), plaintext.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSubMutableByCiphertexts(
    CiphertextDCRTPoly& ciphertext1, CiphertextDCRTPoly& ciphertext2) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSubMutable(
        ciphertext1.GetRef(), ciphertext2.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSubMutableByPlaintextAndCiphertext(
    const Plaintext& plaintext, CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSubMutable(
        plaintext.GetRef(), ciphertext.GetRef()));
}
void CryptoContextDCRTPoly::EvalSubMutableInPlace(CiphertextDCRTPoly& ciphertext1,
    CiphertextDCRTPoly& ciphertext2) const
{
    m_cryptoContextImplSharedPtr->EvalSubMutableInPlace(ciphertext1.GetRef(),
        ciphertext2.GetRef());
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSum(
    const CiphertextDCRTPoly& ciphertext, const uint32_t batchSize) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSum(
        ciphertext.GetRef(), batchSize));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSumCols(
    const CiphertextDCRTPoly& ciphertext, const uint32_t rowSize,
    const MapFromIndexToEvalKey& evalSumKeyMap) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSumCols(
        ciphertext.GetRef(), rowSize, *evalSumKeyMap.GetRef()));
}
std::unique_ptr<MapFromIndexToEvalKey> CryptoContextDCRTPoly::EvalSumColsKeyGen(
    const PrivateKeyDCRTPoly& privateKey, const PublicKeyDCRTPoly& publicKey) const
{
    return std::make_unique<MapFromIndexToEvalKey>(m_cryptoContextImplSharedPtr->EvalSumColsKeyGen(
        privateKey.GetRef(), publicKey.GetRef()));
}
void CryptoContextDCRTPoly::EvalSumKeyGen(const PrivateKeyDCRTPoly& privateKey,
    const PublicKeyDCRTPoly& publicKey) const
{
    m_cryptoContextImplSharedPtr->EvalSumKeyGen(privateKey.GetRef(), publicKey.GetRef());
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSumRows(
    const CiphertextDCRTPoly& ciphertext, const uint32_t rowSize,
    const MapFromIndexToEvalKey& evalSumKeyMap, const uint32_t subringDim) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSumRows(
        ciphertext.GetRef(), rowSize, *evalSumKeyMap.GetRef(), subringDim));
}
std::unique_ptr<MapFromIndexToEvalKey> CryptoContextDCRTPoly::EvalSumRowsKeyGen(
    const PrivateKeyDCRTPoly& privateKey, const PublicKeyDCRTPoly& publicKey,
    const uint32_t rowSize, const uint32_t subringDim) const
{
    return std::make_unique<MapFromIndexToEvalKey>(m_cryptoContextImplSharedPtr->EvalSumRowsKeyGen(
        privateKey.GetRef(), publicKey.GetRef(), rowSize, subringDim));
}
uint32_t CryptoContextDCRTPoly::FindAutomorphismIndex(const uint32_t idx) const
{
    return m_cryptoContextImplSharedPtr->FindAutomorphismIndex(idx);
}
std::unique_ptr<std::vector<uint32_t>> CryptoContextDCRTPoly::FindAutomorphismIndices(
    const std::vector<uint32_t>& idxList) const
{
    return std::make_unique<std::vector<uint32_t>>(
        m_cryptoContextImplSharedPtr->FindAutomorphismIndices(idxList));
}
std::unique_ptr<CryptoParametersBaseDCRTPoly> CryptoContextDCRTPoly::GetCryptoParameters() const
{
    return std::make_unique<CryptoParametersBaseDCRTPoly>(
        m_cryptoContextImplSharedPtr->GetCryptoParameters());
}
uint32_t CryptoContextDCRTPoly::GetCyclotomicOrder() const
{
    return m_cryptoContextImplSharedPtr->GetCyclotomicOrder();
}
std::unique_ptr<DCRTPolyParams> CryptoContextDCRTPoly::GetElementParams() const
{
    return std::make_unique<DCRTPolyParams>(m_cryptoContextImplSharedPtr->GetElementParams());
}
std::unique_ptr<EncodingParams> CryptoContextDCRTPoly::GetEncodingParams() const
{
    return std::make_unique<EncodingParams>(m_cryptoContextImplSharedPtr->GetEncodingParams());
}
size_t CryptoContextDCRTPoly::GetKeyGenLevel() const
{
    return m_cryptoContextImplSharedPtr->GetKeyGenLevel();
}
uint64_t CryptoContextDCRTPoly::GetModulus() const
{
    return m_cryptoContextImplSharedPtr->GetModulus().ConvertToInt();
}
uint32_t CryptoContextDCRTPoly::GetRingDimension() const
{
    return m_cryptoContextImplSharedPtr->GetRingDimension();
}
uint64_t CryptoContextDCRTPoly::GetRootOfUnity() const
{
    return m_cryptoContextImplSharedPtr->GetRootOfUnity().ConvertToInt();
}
std::unique_ptr<SchemeBaseDCRTPoly> CryptoContextDCRTPoly::GetScheme() const
{
    return std::make_unique<SchemeBaseDCRTPoly>(m_cryptoContextImplSharedPtr->GetScheme());
}
SCHEME CryptoContextDCRTPoly::GetSchemeId() const
{
    return m_cryptoContextImplSharedPtr->getSchemeId();
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::GetSwkFC() const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->GetSwkFC());
}
std::unique_ptr<VectorOfCiphertexts> CryptoContextDCRTPoly::IntMPBootAdd(
    VectorOfVectorOfCiphertexts& sharesPairVec) const
{
    return std::make_unique<VectorOfCiphertexts>(m_cryptoContextImplSharedPtr->IntMPBootAdd(
        sharesPairVec.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::IntMPBootAdjustScale(
    const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->IntMPBootAdjustScale(
        ciphertext.GetRef()));
}
std::unique_ptr<VectorOfCiphertexts> CryptoContextDCRTPoly::IntMPBootDecrypt(
    const PrivateKeyDCRTPoly& privateKey, const CiphertextDCRTPoly& ciphertext,
    const CiphertextDCRTPoly& a) const
{
    return std::make_unique<VectorOfCiphertexts>(m_cryptoContextImplSharedPtr->IntMPBootDecrypt(
        privateKey.GetRef(), ciphertext.GetRef(), a.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::IntMPBootEncrypt(
    const PublicKeyDCRTPoly& publicKey, const VectorOfCiphertexts& sharesPair,
    const CiphertextDCRTPoly& a, const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->IntMPBootEncrypt(
        publicKey.GetRef(), sharesPair.GetRef(), a.GetRef(), ciphertext.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::IntMPBootRandomElementGen(
    const PublicKeyDCRTPoly& publicKey) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->IntMPBootRandomElementGen(publicKey.GetRef()));
}
std::unique_ptr<KeyPairDCRTPoly> CryptoContextDCRTPoly::KeyGen() const
{
    return std::make_unique<KeyPairDCRTPoly>(m_cryptoContextImplSharedPtr->KeyGen());
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::KeySwitch(
    const CiphertextDCRTPoly& ciphertext, const EvalKeyDCRTPoly& evalKey) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->KeySwitch(
        ciphertext.GetRef(), evalKey.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::KeySwitchDown(
    const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->KeySwitchDown(
        ciphertext.GetRef()));
}
std::unique_ptr<DCRTPoly> CryptoContextDCRTPoly::KeySwitchDownFirstElement(
    const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<DCRTPoly>(m_cryptoContextImplSharedPtr->KeySwitchDownFirstElement(
        ciphertext.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::KeySwitchExt(
    const CiphertextDCRTPoly& ciphertext, const bool addFirst) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->KeySwitchExt(
        ciphertext.GetRef(), addFirst));
}
std::unique_ptr<EvalKeyDCRTPoly> CryptoContextDCRTPoly::KeySwitchGen(
    const PrivateKeyDCRTPoly& oldPrivateKey, const PrivateKeyDCRTPoly& newPrivateKey) const
{
    return std::make_unique<EvalKeyDCRTPoly>(m_cryptoContextImplSharedPtr->KeySwitchGen(
        oldPrivateKey.GetRef(), newPrivateKey.GetRef()));
}
void CryptoContextDCRTPoly::KeySwitchInPlace(CiphertextDCRTPoly& ciphertext,
    const EvalKeyDCRTPoly& evalKey) const
{
    m_cryptoContextImplSharedPtr->KeySwitchInPlace(ciphertext.GetRef(), evalKey.GetRef());
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::LevelReduce(
    const CiphertextDCRTPoly& ciphertext, const EvalKeyDCRTPoly& evalKey,
    const size_t levels) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->LevelReduce(
        ciphertext.GetRef(), evalKey.GetRef(), levels));
}
void CryptoContextDCRTPoly::LevelReduceInPlace(CiphertextDCRTPoly& ciphertext,
    const EvalKeyDCRTPoly& evalKey, const size_t levels) const
{
    m_cryptoContextImplSharedPtr->LevelReduceInPlace(ciphertext.GetRef(), evalKey.GetRef(),
        levels);
}
std::unique_ptr<Plaintext> CryptoContextDCRTPoly::MakeCKKSPackedPlaintextByVectorOfDouble(
    const std::vector<double>& value, const size_t scaleDeg, const uint32_t level,
    const DCRTPolyParams& params, const uint32_t slots) const
{
    return std::make_unique<Plaintext>(m_cryptoContextImplSharedPtr->MakeCKKSPackedPlaintext(
        value, scaleDeg, level, params.GetRef(), slots));
}
std::unique_ptr<Plaintext> CryptoContextDCRTPoly::MakeCKKSPackedPlaintextByVectorOfComplex(
    const std::vector<ComplexPair>& value, const size_t scaleDeg, const uint32_t level,
    const DCRTPolyParams& params, const uint32_t slots) const
{
    std::vector<std::complex<double>> v;
    v.reserve(value.size());
    for (const ComplexPair& elem : value)
    {
        v.emplace_back(elem.re, elem.im);
    }
    return std::make_unique<Plaintext>(m_cryptoContextImplSharedPtr->MakeCKKSPackedPlaintext(v,
        scaleDeg, level, params.GetRef(), slots));
}
std::unique_ptr<Plaintext> CryptoContextDCRTPoly::MakeCoefPackedPlaintext(
    const std::vector<int64_t>& value, const size_t noiseScaleDeg, const uint32_t level) const
{
    return std::make_unique<Plaintext>(m_cryptoContextImplSharedPtr->MakeCoefPackedPlaintext(value,
        noiseScaleDeg, level));
}
std::unique_ptr<Plaintext> CryptoContextDCRTPoly::MakePackedPlaintext(
    const std::vector<int64_t>& value, const size_t noiseScaleDeg,
    const uint32_t level) const
{
    return std::make_unique<Plaintext>(m_cryptoContextImplSharedPtr->MakePackedPlaintext(value,
        noiseScaleDeg, level));
}
std::unique_ptr<Plaintext> CryptoContextDCRTPoly::MakeStringPlaintext(const std::string& s) const
{
    return std::make_unique<Plaintext>(m_cryptoContextImplSharedPtr->MakeStringPlaintext(s));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::ModReduce(
    const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->ModReduce(
        ciphertext.GetRef()));
}
void CryptoContextDCRTPoly::ModReduceInPlace(CiphertextDCRTPoly& ciphertext) const
{
    m_cryptoContextImplSharedPtr->ModReduceInPlace(ciphertext.GetRef());
}
std::unique_ptr<MapFromIndexToEvalKey> CryptoContextDCRTPoly::MultiAddEvalAutomorphismKeys(
    const MapFromIndexToEvalKey& evalKeyMap1, const MapFromIndexToEvalKey& evalKeyMap2,
    const std::string& keyId) const
{
    return std::make_unique<MapFromIndexToEvalKey>(
        m_cryptoContextImplSharedPtr->MultiAddEvalAutomorphismKeys(evalKeyMap1.GetRef(),
        evalKeyMap2.GetRef(), keyId));
}
std::unique_ptr<EvalKeyDCRTPoly> CryptoContextDCRTPoly::MultiAddEvalKeys(
    const EvalKeyDCRTPoly& evalKey1, const EvalKeyDCRTPoly& evalKey2,
    const std::string& keyId) const
{
    return std::make_unique<EvalKeyDCRTPoly>(m_cryptoContextImplSharedPtr->MultiAddEvalKeys(
        evalKey1.GetRef(), evalKey2.GetRef(), keyId));
}
std::unique_ptr<EvalKeyDCRTPoly> CryptoContextDCRTPoly::MultiAddEvalMultKeys(
    const EvalKeyDCRTPoly& evalKey1, const EvalKeyDCRTPoly& evalKey2,
    const std::string& keyId) const
{
    return std::make_unique<EvalKeyDCRTPoly>(m_cryptoContextImplSharedPtr->MultiAddEvalMultKeys(
        evalKey1.GetRef(), evalKey2.GetRef(), keyId));
}
std::unique_ptr<MapFromIndexToEvalKey> CryptoContextDCRTPoly::MultiAddEvalSumKeys(
    const MapFromIndexToEvalKey& evalKeyMap1, const MapFromIndexToEvalKey& evalKeyMap2,
    const std::string& keyId) const
{
    return std::make_unique<MapFromIndexToEvalKey>(
        m_cryptoContextImplSharedPtr->MultiAddEvalSumKeys(evalKeyMap1.GetRef(),
        evalKeyMap2.GetRef(), keyId));
}
std::unique_ptr<PublicKeyDCRTPoly> CryptoContextDCRTPoly::MultiAddPubKeys(
    const PublicKeyDCRTPoly& publicKey1, const PublicKeyDCRTPoly& publicKey2,
    const std::string& keyId) const
{
    return std::make_unique<PublicKeyDCRTPoly>(m_cryptoContextImplSharedPtr->MultiAddPubKeys(
        publicKey1.GetRef(), publicKey2.GetRef(), keyId));
}
std::unique_ptr<MapFromIndexToEvalKey> CryptoContextDCRTPoly::MultiEvalAtIndexKeyGen(
    const PrivateKeyDCRTPoly& privateKey, const MapFromIndexToEvalKey& evalKeyMap,
    const std::vector<int32_t>& indexList, const std::string& keyId) const
{
    return std::make_unique<MapFromIndexToEvalKey>(
        m_cryptoContextImplSharedPtr->MultiEvalAtIndexKeyGen(privateKey.GetRef(),
        evalKeyMap.GetRef(), indexList, keyId));
}
std::unique_ptr<MapFromIndexToEvalKey> CryptoContextDCRTPoly::MultiEvalAutomorphismKeyGen(
    const PrivateKeyDCRTPoly& privateKey, const MapFromIndexToEvalKey& evalKeyMap,
    const std::vector<uint32_t>& indexList, const std::string& keyId) const
{
    return std::make_unique<MapFromIndexToEvalKey>(
        m_cryptoContextImplSharedPtr->MultiEvalAutomorphismKeyGen(privateKey.GetRef(),
        evalKeyMap.GetRef(), indexList, keyId));
}
std::unique_ptr<MapFromIndexToEvalKey> CryptoContextDCRTPoly::MultiEvalSumKeyGen(
    const PrivateKeyDCRTPoly& privateKey, const MapFromIndexToEvalKey& evalKeyMap,
    const std::string& keyId) const
{
    return std::make_unique<MapFromIndexToEvalKey>(
        m_cryptoContextImplSharedPtr->MultiEvalSumKeyGen(privateKey.GetRef(),
        evalKeyMap.GetRef(), keyId));
}
std::unique_ptr<EvalKeyDCRTPoly> CryptoContextDCRTPoly::MultiKeySwitchGen(
    const PrivateKeyDCRTPoly& originalPrivateKey, const PrivateKeyDCRTPoly& newPrivateKey,
    const EvalKeyDCRTPoly& evalKey) const
{
    return std::make_unique<EvalKeyDCRTPoly>(m_cryptoContextImplSharedPtr->MultiKeySwitchGen(
        originalPrivateKey.GetRef(), newPrivateKey.GetRef(), evalKey.GetRef()));
}
std::unique_ptr<EvalKeyDCRTPoly> CryptoContextDCRTPoly::MultiMultEvalKey(
    const PrivateKeyDCRTPoly& privateKey, const EvalKeyDCRTPoly& evalKey,
    const std::string& keyId) const
{
    return std::make_unique<EvalKeyDCRTPoly>(m_cryptoContextImplSharedPtr->MultiMultEvalKey(
        privateKey.GetRef(), evalKey.GetRef(), keyId));
}
std::unique_ptr<DecryptResult> CryptoContextDCRTPoly::MultipartyDecryptFusion(
    const VectorOfCiphertexts& partialCiphertextVec, Plaintext& plaintext) const
{
    return std::make_unique<DecryptResult>(m_cryptoContextImplSharedPtr->MultipartyDecryptFusion(
        partialCiphertextVec.GetRef(), &plaintext.GetRef()));
}
std::unique_ptr<VectorOfCiphertexts> CryptoContextDCRTPoly::MultipartyDecryptLead(
    const VectorOfCiphertexts& ciphertextVec, const PrivateKeyDCRTPoly& privateKey) const
{
    return std::make_unique<VectorOfCiphertexts>(
        m_cryptoContextImplSharedPtr->MultipartyDecryptLead(ciphertextVec.GetRef(),
        privateKey.GetRef()));
}
std::unique_ptr<VectorOfCiphertexts> CryptoContextDCRTPoly::MultipartyDecryptMain(
    const VectorOfCiphertexts& ciphertextVec, const PrivateKeyDCRTPoly& privateKey) const
{
    return std::make_unique<VectorOfCiphertexts>(
        m_cryptoContextImplSharedPtr->MultipartyDecryptMain(ciphertextVec.GetRef(),
        privateKey.GetRef()));
}
std::unique_ptr<KeyPairDCRTPoly> CryptoContextDCRTPoly::MultipartyKeyGenByPublicKey(
    const PublicKeyDCRTPoly& publicKey, const bool makeSparse, const bool fresh) const
{
    return std::make_unique<KeyPairDCRTPoly>(m_cryptoContextImplSharedPtr->MultipartyKeyGen(
        publicKey.GetRef(), makeSparse, fresh));
}
std::unique_ptr<KeyPairDCRTPoly> CryptoContextDCRTPoly::MultipartyKeyGenByVectorOfPrivateKeys(
    const VectorOfPrivateKeys& privateKeyVec) const
{
    return std::make_unique<KeyPairDCRTPoly>(m_cryptoContextImplSharedPtr->MultipartyKeyGen(
        privateKeyVec.GetRef()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::ReEncrypt(
    const CiphertextDCRTPoly& ciphertext, const EvalKeyDCRTPoly& evalKey,
    const PublicKeyDCRTPoly& publicKey) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->ReEncrypt(
        ciphertext.GetRef(), evalKey.GetRef(), publicKey.GetRef()));
}
std::unique_ptr<EvalKeyDCRTPoly> CryptoContextDCRTPoly::ReKeyGen(
    const PrivateKeyDCRTPoly& oldPrivateKey, const PublicKeyDCRTPoly& newPublicKey) const
{
    return std::make_unique<EvalKeyDCRTPoly>(m_cryptoContextImplSharedPtr->ReKeyGen(
        oldPrivateKey.GetRef(), newPublicKey.GetRef()));
}
void CryptoContextDCRTPoly::RecoverSharedKey(PrivateKeyDCRTPoly& sk,
    UnorderedMapFromIndexToDCRTPoly& sk_shares, const uint32_t N, const uint32_t threshold,
    const std::string& shareType) const
{
	m_cryptoContextImplSharedPtr->RecoverSharedKey(sk.GetRef(), sk_shares.GetRef(), N, threshold,
        shareType);
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::Relinearize(
    const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->Relinearize(
        ciphertext.GetRef()));
}
void CryptoContextDCRTPoly::RelinearizeInPlace(CiphertextDCRTPoly& ciphertext) const
{
    m_cryptoContextImplSharedPtr->RelinearizeInPlace(ciphertext.GetRef());
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::Rescale(
    const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->Rescale(
        ciphertext.GetRef()));
}
void CryptoContextDCRTPoly::RescaleInPlace(CiphertextDCRTPoly& ciphertext) const
{
    m_cryptoContextImplSharedPtr->RescaleInPlace(ciphertext.GetRef());
}
void CryptoContextDCRTPoly::SetKeyGenLevel(const size_t level) const
{
    m_cryptoContextImplSharedPtr->SetKeyGenLevel(level);
}
void CryptoContextDCRTPoly::SetSchemeId(const SCHEME schemeTag) const
{
    m_cryptoContextImplSharedPtr->setSchemeId(schemeTag);
}
void CryptoContextDCRTPoly::SetSwkFC(const CiphertextDCRTPoly& FHEWtoCKKSswk) const
{
    m_cryptoContextImplSharedPtr->SetSwkFC(FHEWtoCKKSswk.GetRef());
}
std::unique_ptr<UnorderedMapFromIndexToDCRTPoly> CryptoContextDCRTPoly::ShareKeys(
    const PrivateKeyDCRTPoly& sk, const uint32_t N, const uint32_t threshold, const uint32_t index,
    const std::string& shareType) const
{
    return std::make_unique<UnorderedMapFromIndexToDCRTPoly>(
        m_cryptoContextImplSharedPtr->ShareKeys(sk.GetRef(), N, threshold, index, shareType));
}
std::unique_ptr<KeyPairDCRTPoly> CryptoContextDCRTPoly::SparseKeyGen() const
{
    return std::make_unique<KeyPairDCRTPoly>(m_cryptoContextImplSharedPtr->SparseKeyGen());
}
const std::shared_ptr<CryptoContextImpl>& CryptoContextDCRTPoly::GetRef() const noexcept
{
    return m_cryptoContextImplSharedPtr;
}
std::shared_ptr<CryptoContextImpl>& CryptoContextDCRTPoly::GetRef() noexcept
{
    return m_cryptoContextImplSharedPtr;
}

// cxx currently does not support static class methods
void DCRTPolyClearEvalAutomorphismKeys()
{
    CryptoContextImpl::ClearEvalAutomorphismKeys();
}
void DCRTPolyClearEvalAutomorphismKeysByCryptoContext(const CryptoContextDCRTPoly& cryptoContext)
{
    CryptoContextImpl::ClearEvalAutomorphismKeys(cryptoContext.GetRef());
}
void DCRTPolyClearEvalAutomorphismKeysById(const std::string& id)
{
    CryptoContextImpl::ClearEvalAutomorphismKeys(id);
}
void DCRTPolyClearEvalMultKeys()
{
    CryptoContextImpl::ClearEvalMultKeys();
}
void DCRTPolyClearEvalMultKeysByCryptoContext(const CryptoContextDCRTPoly& cryptoContext)
{
    CryptoContextImpl::ClearEvalMultKeys(cryptoContext.GetRef());
}
void DCRTPolyClearEvalMultKeysById(const std::string& id)
{
    CryptoContextImpl::ClearEvalMultKeys(id);
}
void DCRTPolyClearEvalSumKeys()
{
    CryptoContextImpl::ClearEvalSumKeys();
}
void DCRTPolyClearEvalSumKeysByCryptoContext(const CryptoContextDCRTPoly& cryptoContext)
{
    CryptoContextImpl::ClearEvalSumKeys(cryptoContext.GetRef());
}
void DCRTPolyClearEvalSumKeysById(const std::string& id)
{
    CryptoContextImpl::ClearEvalSumKeys(id);
}
std::unique_ptr<MapFromStringToMapFromIndexToEvalKey> DCRTPolyGetCopyOfAllEvalAutomorphismKeys()
{
    return std::make_unique<MapFromStringToMapFromIndexToEvalKey>(
        CryptoContextImpl::GetAllEvalAutomorphismKeys());
}
std::unique_ptr<MapFromStringToVectorOfEvalKeys> DCRTPolyGetCopyOfAllEvalMultKeys()
{
    return std::make_unique<MapFromStringToVectorOfEvalKeys>(
        CryptoContextImpl::GetAllEvalMultKeys());
}
std::unique_ptr<MapFromStringToMapFromIndexToEvalKey> DCRTPolyGetCopyOfAllEvalSumKeys()
{
    return std::make_unique<MapFromStringToMapFromIndexToEvalKey>(
        CryptoContextImpl::GetAllEvalSumKeys());
}
std::unique_ptr<VectorOfEvalKeys> DCRTPolyGetCopyOfEvalMultKeyVector(const std::string& keyID)
{
    return std::make_unique<VectorOfEvalKeys>(CryptoContextImpl::GetEvalMultKeyVector(keyID));
}
std::unique_ptr<MapFromIndexToEvalKey> DCRTPolyGetCopyOfEvalSumKeyMap(const std::string& id)
{
    return std::make_unique<MapFromIndexToEvalKey>(
        std::make_shared<std::map<uint32_t, std::shared_ptr<EvalKeyImpl>>>(
        CryptoContextImpl::GetEvalSumKeyMap(id)));
}
std::unique_ptr<MapFromIndexToEvalKey> DCRTPolyGetEvalAutomorphismKeyMap(const std::string& keyID)
{
    return std::make_unique<MapFromIndexToEvalKey>(CryptoContextImpl::GetEvalAutomorphismKeyMapPtr(
        keyID));
}
std::unique_ptr<MapFromIndexToEvalKey> DCRTPolyGetEvalAutomorphismKeyMapPtr(
    const std::string& keyID)
{
    return std::make_unique<MapFromIndexToEvalKey>(CryptoContextImpl::GetEvalAutomorphismKeyMapPtr(
        keyID));
}
std::unique_ptr<std::vector<uint32_t>> DCRTPolyGetExistingEvalAutomorphismKeyIndices(
    const std::string& keyTag)
{
    return std::make_unique<std::vector<uint32_t>>(
        CryptoContextImpl::GetExistingEvalAutomorphismKeyIndices(keyTag));
}
std::unique_ptr<Plaintext> DCRTPolyGetPlaintextForDecrypt(const PlaintextEncodings pte,
    const DCRTPolyParams& evp, const EncodingParams& ep)
{
    return std::make_unique<Plaintext>(CryptoContextImpl::GetPlaintextForDecrypt(pte,
        evp.GetRef(), ep.GetRef()));
}
std::unique_ptr<std::vector<uint32_t>> DCRTPolyGetUniqueValues(
    const std::vector<uint32_t>& oldValues, const std::vector<uint32_t>& newValues)
{
    return std::make_unique<std::vector<uint32_t>>(CryptoContextImpl::GetUniqueValues(oldValues,
        newValues));
}
void DCRTPolyInsertEvalAutomorphismKey(const MapFromIndexToEvalKey& evalKeyMap,
    const std::string& keyTag)
{
    CryptoContextImpl::InsertEvalAutomorphismKey(evalKeyMap.GetRef(), keyTag);
}
void DCRTPolyInsertEvalMultKey(const VectorOfEvalKeys& evalKeyVec)
{
    CryptoContextImpl::InsertEvalMultKey(evalKeyVec.GetRef());
}
void DCRTPolyInsertEvalSumKey(const MapFromIndexToEvalKey& mapToInsert, const std::string& keyTag)
{
    CryptoContextImpl::InsertEvalSumKey(mapToInsert.GetRef(), keyTag);
}

// Generator functions
std::unique_ptr<CryptoContextDCRTPoly> DCRTPolyGenNullCryptoContext()
{
    return std::make_unique<CryptoContextDCRTPoly>();
}
std::unique_ptr<CryptoContextDCRTPoly> DCRTPolyGenCryptoContextByParamsBFVRNS(
    const ParamsBFVRNS& params)
{
    return std::make_unique<CryptoContextDCRTPoly>(params);
}
std::unique_ptr<CryptoContextDCRTPoly> DCRTPolyGenCryptoContextByParamsBGVRNS(
    const ParamsBGVRNS& params)
{
    return std::make_unique<CryptoContextDCRTPoly>(params);
}
std::unique_ptr<CryptoContextDCRTPoly> DCRTPolyGenCryptoContextByParamsCKKSRNS(
    const ParamsCKKSRNS& params)
{
    return std::make_unique<CryptoContextDCRTPoly>(params);
}

} // openfhe
