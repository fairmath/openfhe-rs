#include "CryptoContext.h"

#include "openfhe/pke/gen-cryptocontext.h"
#include "openfhe/pke/scheme/bfvrns/gen-cryptocontext-bfvrns.h"
#include "openfhe/pke/scheme/bgvrns/gen-cryptocontext-bgvrns.h"
#include "openfhe/pke/scheme/ckksrns/gen-cryptocontext-ckksrns.h"

#include "openfhe/src/lib.rs.h" // ComplexPair

#include "Ciphertext.h"
#include "KeyPair.h"
#include "Plaintext.h"
#include "PublicKey.h"

namespace openfhe
{

using PlaintextImpl = lbcrypto::PlaintextImpl;

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
    const std::vector<ComplexPair>& value, const size_t scaleDeg, const uint32_t level,
    const std::shared_ptr<DCRTPolyParams> params, const uint32_t slots) const
{
    std::vector<std::complex<double>> v;
    v.reserve(value.size());
    for (const ComplexPair& elem : value)
    {
        v.emplace_back(elem.re, elem.im);
    }
    return std::make_unique<Plaintext>(m_cryptoContextImplSharedPtr->MakeCKKSPackedPlaintext(
        v, scaleDeg, level, params, slots));
}
void CryptoContextDCRTPoly::SetSchemeId(const SCHEME schemeTag) const
{
    m_cryptoContextImplSharedPtr->setSchemeId(schemeTag);
}
SCHEME CryptoContextDCRTPoly::GetSchemeId() const
{
    return m_cryptoContextImplSharedPtr->getSchemeId();
}
size_t CryptoContextDCRTPoly::GetKeyGenLevel() const
{
    return m_cryptoContextImplSharedPtr->GetKeyGenLevel();
}
void CryptoContextDCRTPoly::SetKeyGenLevel(const size_t level) const
{
    m_cryptoContextImplSharedPtr->SetKeyGenLevel(level);
}
void CryptoContextDCRTPoly::SetSwkFC(const CiphertextDCRTPoly& FHEWtoCKKSswk) const
{
    m_cryptoContextImplSharedPtr->SetSwkFC(FHEWtoCKKSswk.GetInternal());
}
void CryptoContextDCRTPoly::EvalCompareSwitchPrecompute(const uint32_t pLWE,
    const double scaleSign, const bool unit) const
{
    m_cryptoContextImplSharedPtr->EvalCompareSwitchPrecompute(pLWE, scaleSign, unit);
}
uint32_t CryptoContextDCRTPoly::FindAutomorphismIndex(const uint32_t idx) const
{
    return m_cryptoContextImplSharedPtr->FindAutomorphismIndex(idx);
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::GetSwkFC() const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->GetSwkFC());
}
void CryptoContextDCRTPoly::Enable(const PKESchemeFeature feature) const
{
    m_cryptoContextImplSharedPtr->Enable(feature);
}
void CryptoContextDCRTPoly::EnableByMask(const uint32_t featureMask) const
{
    m_cryptoContextImplSharedPtr->Enable(featureMask);
}
std::unique_ptr<KeyPairDCRTPoly> CryptoContextDCRTPoly::KeyGen() const
{
    return std::make_unique<KeyPairDCRTPoly>(m_cryptoContextImplSharedPtr->KeyGen());
}
std::unique_ptr<KeyPairDCRTPoly> CryptoContextDCRTPoly::SparseKeyGen() const
{
    return std::make_unique<KeyPairDCRTPoly>(m_cryptoContextImplSharedPtr->SparseKeyGen());
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
void CryptoContextDCRTPoly::EvalCKKStoFHEWPrecompute(const double scale) const
{
    m_cryptoContextImplSharedPtr->EvalCKKStoFHEWPrecompute(scale);
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
std::unique_ptr<Plaintext> CryptoContextDCRTPoly::MakeCoefPackedPlaintext(
    const std::vector<int64_t>& value, const size_t noiseScaleDeg,
    const uint32_t level) const
{
    return std::make_unique<Plaintext>(m_cryptoContextImplSharedPtr->MakeCoefPackedPlaintext(value,
        noiseScaleDeg, level));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EncryptByPublicKey(
    const std::shared_ptr<PublicKeyImpl> publicKey, const Plaintext& plaintext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->Encrypt(publicKey,
        plaintext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EncryptByPrivateKey(
    const std::shared_ptr<PrivateKeyImpl> privateKey, const Plaintext& plaintext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->Encrypt(privateKey,
        plaintext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAddByCiphertexts(
    const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAdd(
        ciphertext1.GetInternal(), ciphertext2.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAddByCiphertextAndPlaintext(
    const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAdd(
        ciphertext.GetInternal(), plaintext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAddByPlaintextAndCiphertext(
    const Plaintext& plaintext, const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAdd(
        plaintext.GetInternal(), ciphertext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAddByConstAndCiphertext(
    const double constant, const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAdd(
        constant, ciphertext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAddByCiphertextAndConst(
    const CiphertextDCRTPoly& ciphertext, const double constant) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAdd(
        ciphertext.GetInternal(), constant));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSubByCiphertexts(
    const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSub(
        ciphertext1.GetInternal(), ciphertext2.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSubByCiphertextAndPlaintext(
    const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSub(
        ciphertext.GetInternal(), plaintext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSubByPlaintextAndCiphertext(
    const Plaintext& plaintext, const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSub(
        plaintext.GetInternal(), ciphertext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSubByConstAndCiphertext(
    const double constant, const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSub(
        constant, ciphertext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSubByCiphertextAndConst(
    const CiphertextDCRTPoly& ciphertext, const double constant) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSub(
        ciphertext.GetInternal(), constant));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultByCiphertexts(
    const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMult(
        ciphertext1.GetInternal(), ciphertext2.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultByCiphertextAndPlaintext(
    const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMult(
        ciphertext.GetInternal(), plaintext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultByPlaintextAndCiphertext(
    const Plaintext& plaintext, const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMult(
        plaintext.GetInternal(), ciphertext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultByConstAndCiphertext(
    const double constant, const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMult(
        constant, ciphertext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultByCiphertextAndConst(
    const CiphertextDCRTPoly& ciphertext, const double constant) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMult(
        ciphertext.GetInternal(), constant));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultNoRelin(
    const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMultNoRelin(
        ciphertext1.GetInternal(), ciphertext2.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultAndRelinearize(
    const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalMultAndRelinearize(ciphertext1.GetInternal(),
        ciphertext2.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalRotate(
    const CiphertextDCRTPoly& ciphertext, const int32_t index) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalRotate(ciphertext.GetInternal(), index));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalChebyshevSeries(
    const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients,
    const double a, const double b) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalChebyshevSeries(
        ciphertext.GetInternal(), coefficients, a, b));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalChebyshevFunction(
    rust::Fn<void(const double x, double& ret)> func, const CiphertextDCRTPoly& ciphertext,
    const double a, const double b, const uint32_t degree) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalChebyshevFunction([&](const double x){
        double result; func(x, result); return result; }, ciphertext.GetInternal(), a, b, degree));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalCompareSchemeSwitching(
    const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2,
    const uint32_t numCtxts, const uint32_t numSlots, const uint32_t pLWE, const double scaleSign,
    const bool unit) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalCompareSchemeSwitching(ciphertext1.GetInternal(),
        ciphertext2.GetInternal(), numCtxts, numSlots, pLWE, scaleSign, unit));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::Rescale(
    const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->Rescale(
        ciphertext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::ModReduce(
    const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->ModReduce(
        ciphertext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSum(
    const CiphertextDCRTPoly& ciphertext, const uint32_t batchSize) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSum(
        ciphertext.GetInternal(), batchSize));
}

std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalPolyLinear(
    const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalPolyLinear(
        ciphertext.GetInternal(), coefficients));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalPolyPS(
    const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalPolyPS(
        ciphertext.GetInternal(), coefficients));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalChebyshevSeriesLinear(
    const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients,
    const double a, const double b) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalChebyshevSeriesLinear(ciphertext.GetInternal(),
        coefficients, a, b));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalChebyshevSeriesPS(
    const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients,
    const double a, const double b) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalChebyshevSeriesPS(ciphertext.GetInternal(), coefficients,
        a, b));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalDivide(
    const CiphertextDCRTPoly& ciphertext, const double a, const double b,
    const uint32_t degree) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalDivide(
        ciphertext.GetInternal(), a, b, degree));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::IntMPBootAdjustScale(
    const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->IntMPBootAdjustScale(
        ciphertext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalLogistic(
    const CiphertextDCRTPoly& ciphertext, const double a, const double b,
    const uint32_t degree) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalLogistic(
        ciphertext.GetInternal(), a, b, degree));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::IntMPBootRandomElementGen(
    const PublicKeyDCRTPoly& publicKey) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->IntMPBootRandomElementGen(publicKey.GetInternal()));
}
void CryptoContextDCRTPoly::EvalBootstrapSetup(
    const std::vector<uint32_t>& levelBudget, const std::vector<uint32_t>& dim1,
    const uint32_t slots, const uint32_t correctionFactor, const bool precompute) const
{
    m_cryptoContextImplSharedPtr->EvalBootstrapSetup(levelBudget, dim1, slots, correctionFactor,
        precompute);
}
void CryptoContextDCRTPoly::EvalBootstrapKeyGen(const std::shared_ptr<PrivateKeyImpl> privateKey,
    const uint32_t slots) const
{
    m_cryptoContextImplSharedPtr->EvalBootstrapKeyGen(privateKey, slots);
}
void CryptoContextDCRTPoly::EvalBootstrapPrecompute(const uint32_t slots) const
{
    m_cryptoContextImplSharedPtr->EvalBootstrapPrecompute(slots);
}
std::unique_ptr<DecryptResult> CryptoContextDCRTPoly::DecryptByPrivateKeyAndCiphertext(
    const std::shared_ptr<PrivateKeyImpl> privateKey, const CiphertextDCRTPoly& ciphertext,
    Plaintext& plaintext) const
{
    std::shared_ptr<PlaintextImpl> res;
    std::unique_ptr<DecryptResult> result = std::make_unique<DecryptResult>(
    m_cryptoContextImplSharedPtr->Decrypt(privateKey, ciphertext.GetInternal(), &res));
    plaintext = res;
    return result;
}
std::unique_ptr<DecryptResult> CryptoContextDCRTPoly::DecryptByCiphertextAndPrivateKey(
    const CiphertextDCRTPoly& ciphertext, const std::shared_ptr<PrivateKeyImpl> privateKey,
    Plaintext& plaintext) const
{
    std::shared_ptr<PlaintextImpl> res;
    std::unique_ptr<DecryptResult> result = std::make_unique<DecryptResult>(
    m_cryptoContextImplSharedPtr->Decrypt(ciphertext.GetInternal(), privateKey, &res));
    plaintext = res;
    return result;
}
uint32_t CryptoContextDCRTPoly::GetRingDimension() const
{
    return m_cryptoContextImplSharedPtr->GetRingDimension();
}
uint32_t CryptoContextDCRTPoly::GetCyclotomicOrder() const
{
    return m_cryptoContextImplSharedPtr->GetCyclotomicOrder();
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSin(
    const CiphertextDCRTPoly& ciphertext,
    const double a, const double b, const uint32_t degree) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSin(
        ciphertext.GetInternal(), a, b, degree));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalCos(
    const CiphertextDCRTPoly& ciphertext,
    const double a, const double b, const uint32_t degree) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalCos(
        ciphertext.GetInternal(), a, b, degree));
}
std::unique_ptr<Plaintext> CryptoContextDCRTPoly::MakeCKKSPackedPlaintext(
    const std::vector<double>& value, const size_t scaleDeg, const uint32_t level,
    const std::shared_ptr<DCRTPolyParams> params, const uint32_t slots) const
{
    return std::make_unique<Plaintext>(m_cryptoContextImplSharedPtr->MakeCKKSPackedPlaintext(
        value, scaleDeg, level, params, slots));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalPoly(
    const CiphertextDCRTPoly& ciphertext, const std::vector<double>& coefficients) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalPoly(ciphertext.GetInternal(), coefficients));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::KeySwitchDown(
    const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->KeySwitchDown(
        ciphertext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::KeySwitchExt(
    const CiphertextDCRTPoly& ciphertext, const bool addFirst) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->KeySwitchExt(
        ciphertext.GetInternal(), addFirst));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::Compress(
    const CiphertextDCRTPoly& ciphertext, const uint32_t towersLeft) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->Compress(
        ciphertext.GetInternal(), towersLeft));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalNegate(
    const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalNegate(ciphertext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSquare(
    const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalSquare(ciphertext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAtIndex(
    const CiphertextDCRTPoly& ciphertext, const uint32_t index) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalAtIndex(ciphertext.GetInternal(), index));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::ComposedEvalMult(
    const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->ComposedEvalMult(ciphertext1.GetInternal(),
        ciphertext2.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::Relinearize(
    const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->Relinearize(ciphertext.GetInternal()));
}
std::unique_ptr<std::vector<uint32_t>> CryptoContextDCRTPoly::FindAutomorphismIndices(
    const std::vector<uint32_t>& idxList) const
{
    return std::make_unique<std::vector<uint32_t>>(
        m_cryptoContextImplSharedPtr->FindAutomorphismIndices(idxList));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalInnerProductByCiphertexts(
    const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2,
    const uint32_t batchSize) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalInnerProduct(
        ciphertext1.GetInternal(), ciphertext2.GetInternal(), batchSize));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalInnerProductByPlaintext(
    const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext,
    const uint32_t batchSize) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalInnerProduct(
        ciphertext.GetInternal(), plaintext.GetInternal(), batchSize));
}
std::shared_ptr<CryptoContextImpl> CryptoContextDCRTPoly::GetInternal() const
{
    return m_cryptoContextImplSharedPtr;
}

// cxx currently does not support static class methods
void ClearEvalMultKeys()
{
    CryptoContextImpl::ClearEvalMultKeys();
}
void ClearEvalMultKeysById(const std::string& id)
{
    CryptoContextImpl::ClearEvalMultKeys(id);
}
void ClearEvalMultKeysByCryptoContext(const CryptoContextDCRTPoly& cryptoContext)
{
    CryptoContextImpl::ClearEvalMultKeys(cryptoContext.GetInternal());
}
void ClearEvalSumKeys()
{
    CryptoContextImpl::ClearEvalSumKeys();
}
void ClearEvalSumKeysById(const std::string& id)
{
    CryptoContextImpl::ClearEvalSumKeys(id);
}
void ClearEvalSumKeysByCryptoContext(const CryptoContextDCRTPoly& cryptoContext)
{
    CryptoContextImpl::ClearEvalSumKeys(cryptoContext.GetInternal());
}
void ClearEvalAutomorphismKeys()
{
    CryptoContextImpl::ClearEvalAutomorphismKeys();
}
void ClearEvalAutomorphismKeysById(const std::string& id)
{
    CryptoContextImpl::ClearEvalAutomorphismKeys(id);
}
void ClearEvalAutomorphismKeysByCryptoContext(const CryptoContextDCRTPoly& cryptoContext)
{
    CryptoContextImpl::ClearEvalAutomorphismKeys(cryptoContext.GetInternal());
}
std::unique_ptr<std::vector<uint32_t>> GetExistingEvalAutomorphismKeyIndices(
    const std::string& keyTag)
{
    return std::make_unique<std::vector<uint32_t>>(
        CryptoContextImpl::GetExistingEvalAutomorphismKeyIndices(keyTag));
}
std::unique_ptr<std::vector<uint32_t>> GetUniqueValues(const std::vector<uint32_t>& oldValues,
    const std::vector<uint32_t>& newValues)
{
    return std::make_unique<std::vector<uint32_t>>(
        CryptoContextImpl::GetUniqueValues(oldValues, newValues));
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

} // openfhe
