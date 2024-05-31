#include "CryptoContext.h"

#include "openfhe/pke/gen-cryptocontext.h"
#include "openfhe/pke/scheme/bfvrns/gen-cryptocontext-bfvrns.h"
#include "openfhe/pke/scheme/bgvrns/gen-cryptocontext-bgvrns.h"
#include "openfhe/pke/scheme/ckksrns/gen-cryptocontext-ckksrns.h"

#include "openfhe/src/lib.rs.h" // ComplexPair

#include "Ciphertext.h"
#include "KeyPair.h"
#include "Plaintext.h"
#include "PrivateKey.h"
#include "PublicKey.h"
#include "EvalKey.h"
#include "LWEPrivateKey.h"
#include "VectorOfCiphertexts.h"

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
std::unique_ptr<KeyPairDCRTPoly> CryptoContextDCRTPoly::MultipartyKeyGen(
    const PublicKeyDCRTPoly& publicKey, const bool makeSparse, const bool fresh) const
{
    return std::make_unique<KeyPairDCRTPoly>(m_cryptoContextImplSharedPtr->MultipartyKeyGen(
        publicKey.GetInternal(), makeSparse, fresh));
}
std::unique_ptr<PublicKeyDCRTPoly> CryptoContextDCRTPoly::MultiAddPubKeys(
    const PublicKeyDCRTPoly& publicKey1, const PublicKeyDCRTPoly& publicKey2,
    const std::string& keyId) const
{
    return std::make_unique<PublicKeyDCRTPoly>(m_cryptoContextImplSharedPtr->MultiAddPubKeys(
        publicKey1.GetInternal(), publicKey2.GetInternal(), keyId));
}
std::unique_ptr<KeyPairDCRTPoly> CryptoContextDCRTPoly::SparseKeyGen() const
{
    return std::make_unique<KeyPairDCRTPoly>(m_cryptoContextImplSharedPtr->SparseKeyGen());
}
void CryptoContextDCRTPoly::EvalMultKeyGen(const PrivateKeyDCRTPoly& key) const
{
    m_cryptoContextImplSharedPtr->EvalMultKeyGen(key.GetInternal());
}
void CryptoContextDCRTPoly::EvalMultKeysGen(const PrivateKeyDCRTPoly& key) const
{
    m_cryptoContextImplSharedPtr->EvalMultKeysGen(key.GetInternal());
}
void CryptoContextDCRTPoly::EvalRotateKeyGen(const PrivateKeyDCRTPoly& privateKey,
    const std::vector<int32_t>& indexList, const PublicKeyDCRTPoly& publicKey) const
{
    m_cryptoContextImplSharedPtr->EvalRotateKeyGen(privateKey.GetInternal(), indexList,
    publicKey.GetInternal());
}
void CryptoContextDCRTPoly::EvalAtIndexKeyGen(const PrivateKeyDCRTPoly& privateKey,
    const std::vector<int32_t>& indexList, const PublicKeyDCRTPoly& publicKey) const
{
    m_cryptoContextImplSharedPtr->EvalAtIndexKeyGen(privateKey.GetInternal(), indexList,
    publicKey.GetInternal());
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
    const std::vector<int64_t>& value, const size_t noiseScaleDeg, const uint32_t level) const
{
    return std::make_unique<Plaintext>(m_cryptoContextImplSharedPtr->MakeCoefPackedPlaintext(value,
        noiseScaleDeg, level));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EncryptByPublicKey(
    const PublicKeyDCRTPoly& publicKey, const Plaintext& plaintext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->Encrypt(
        publicKey.GetInternal(), plaintext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EncryptByPrivateKey(
    const PrivateKeyDCRTPoly& privateKey, const Plaintext& plaintext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->Encrypt(
        privateKey.GetInternal(), plaintext.GetInternal()));
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
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAddMutableByCiphertexts(
    const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const
{
    std::shared_ptr<CiphertextImpl> c1 = ciphertext1.GetInternal();
    std::shared_ptr<CiphertextImpl> c2 = ciphertext2.GetInternal();
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAddMutable(
        c1, c2));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAddMutableByCiphertextAndPlaintext(
    const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAddMutable(c,
        plaintext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAddMutableByPlaintextAndCiphertext(
    const Plaintext& plaintext, const CiphertextDCRTPoly& ciphertext) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAddMutable(
        plaintext.GetInternal(), c));
}
void CryptoContextDCRTPoly::EvalAddInPlaceByCiphertexts(const CiphertextDCRTPoly& ciphertext1,
    const CiphertextDCRTPoly& ciphertext2) const
{
    std::shared_ptr<CiphertextImpl> c1 = ciphertext1.GetInternal();
    m_cryptoContextImplSharedPtr->EvalAddInPlace(c1, ciphertext2.GetInternal());
}
void CryptoContextDCRTPoly::EvalAddInPlaceByCiphertextAndPlaintext(
    const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    m_cryptoContextImplSharedPtr->EvalAddInPlace(c, plaintext.GetInternal());
}
void CryptoContextDCRTPoly::EvalAddInPlaceByPlaintextAndCiphertext(const Plaintext& plaintext,
    const CiphertextDCRTPoly& ciphertext) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    m_cryptoContextImplSharedPtr->EvalAddInPlace(plaintext.GetInternal(), c);
}
void CryptoContextDCRTPoly::EvalAddInPlaceByCiphertextAndConst(
    const CiphertextDCRTPoly& ciphertext, const double constant) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    m_cryptoContextImplSharedPtr->EvalAddInPlace(c, constant);
}
void CryptoContextDCRTPoly::EvalAddInPlaceByConstAndCiphertext(const double constant,
    const CiphertextDCRTPoly& ciphertext) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    m_cryptoContextImplSharedPtr->EvalAddInPlace(constant, c);
}
void CryptoContextDCRTPoly::EvalAddMutableInPlace(const CiphertextDCRTPoly& ciphertext1,
    const CiphertextDCRTPoly& ciphertext2) const
{
    std::shared_ptr<CiphertextImpl> c1 = ciphertext1.GetInternal();
    std::shared_ptr<CiphertextImpl> c2 = ciphertext2.GetInternal();
    m_cryptoContextImplSharedPtr->EvalAddMutableInPlace(c1, c2);
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
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSubMutableByCiphertexts(
    const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const
{
    std::shared_ptr<CiphertextImpl> c1 = ciphertext1.GetInternal();
    std::shared_ptr<CiphertextImpl> c2 = ciphertext2.GetInternal();
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSubMutable(
        c1, c2));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSubMutableByCiphertextAndPlaintext(
    const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSubMutable(c,
        plaintext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSubMutableByPlaintextAndCiphertext(
    const Plaintext& plaintext, const CiphertextDCRTPoly& ciphertext) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalSubMutable(
        plaintext.GetInternal(), c));
}
void CryptoContextDCRTPoly::EvalSubInPlaceByCiphertexts(const CiphertextDCRTPoly& ciphertext1,
    const CiphertextDCRTPoly& ciphertext2) const
{
    std::shared_ptr<CiphertextImpl> c1 = ciphertext1.GetInternal();
    m_cryptoContextImplSharedPtr->EvalSubInPlace(c1, ciphertext2.GetInternal());
}
void CryptoContextDCRTPoly::EvalSubInPlaceByCiphertextAndConst(
    const CiphertextDCRTPoly& ciphertext, const double constant) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    m_cryptoContextImplSharedPtr->EvalSubInPlace(c, constant);
}
void CryptoContextDCRTPoly::EvalSubInPlaceByConstAndCiphertext(const double constant,
    const CiphertextDCRTPoly& ciphertext) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    m_cryptoContextImplSharedPtr->EvalSubInPlace(constant, c);
}
void CryptoContextDCRTPoly::EvalSubMutableInPlace(const CiphertextDCRTPoly& ciphertext1,
    const CiphertextDCRTPoly& ciphertext2) const
{
    std::shared_ptr<CiphertextImpl> c1 = ciphertext1.GetInternal();
    std::shared_ptr<CiphertextImpl> c2 = ciphertext2.GetInternal();
    m_cryptoContextImplSharedPtr->EvalSubMutableInPlace(c1, c2);
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
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultMutableByCiphertexts(
    const CiphertextDCRTPoly& ciphertext1, const CiphertextDCRTPoly& ciphertext2) const
{
    std::shared_ptr<CiphertextImpl> c1 = ciphertext1.GetInternal();
    std::shared_ptr<CiphertextImpl> c2 = ciphertext2.GetInternal();
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMultMutable(
        c1, c2));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultMutableByCiphertextAndPlaintext(
    const CiphertextDCRTPoly& ciphertext, const Plaintext& plaintext) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMultMutable(c,
        plaintext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultMutableByPlaintextAndCiphertext(
    const Plaintext& plaintext, const CiphertextDCRTPoly& ciphertext) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMultMutable(
        plaintext.GetInternal(), c));
}
void CryptoContextDCRTPoly::EvalMultInPlaceByCiphertextAndConst(
    const CiphertextDCRTPoly& ciphertext, const double constant) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    m_cryptoContextImplSharedPtr->EvalMultInPlace(c, constant);
}
void CryptoContextDCRTPoly::EvalMultInPlaceByConstAndCiphertext(const double constant,
    const CiphertextDCRTPoly& ciphertext) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    m_cryptoContextImplSharedPtr->EvalMultInPlace(constant, c);
}
void CryptoContextDCRTPoly::EvalMultMutableInPlace(const CiphertextDCRTPoly& ciphertext1,
    const CiphertextDCRTPoly& ciphertext2) const
{
    std::shared_ptr<CiphertextImpl> c1 = ciphertext1.GetInternal();
    std::shared_ptr<CiphertextImpl> c2 = ciphertext2.GetInternal();
    m_cryptoContextImplSharedPtr->EvalMultMutableInPlace(c1, c2);
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
void CryptoContextDCRTPoly::RescaleInPlace(const CiphertextDCRTPoly& ciphertext) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    m_cryptoContextImplSharedPtr->RescaleInPlace(c);
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::ModReduce(
    const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->ModReduce(
        ciphertext.GetInternal()));
}
void CryptoContextDCRTPoly::ModReduceInPlace(const CiphertextDCRTPoly& ciphertext) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    m_cryptoContextImplSharedPtr->ModReduceInPlace(c);
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
void CryptoContextDCRTPoly::EvalBootstrapKeyGen(const PrivateKeyDCRTPoly& privateKey,
    const uint32_t slots) const
{
    m_cryptoContextImplSharedPtr->EvalBootstrapKeyGen(privateKey.GetInternal(), slots);
}
void CryptoContextDCRTPoly::EvalBootstrapPrecompute(const uint32_t slots) const
{
    m_cryptoContextImplSharedPtr->EvalBootstrapPrecompute(slots);
}
std::unique_ptr<DecryptResult> CryptoContextDCRTPoly::DecryptByPrivateKeyAndCiphertext(
    const PrivateKeyDCRTPoly& privateKey, const CiphertextDCRTPoly& ciphertext,
    Plaintext& plaintext) const
{
    std::shared_ptr<PlaintextImpl> p;
    std::unique_ptr<DecryptResult> res = std::make_unique<DecryptResult>(
    m_cryptoContextImplSharedPtr->Decrypt(privateKey.GetInternal(), ciphertext.GetInternal(), &p));
    plaintext = p;
    return res;
}
std::unique_ptr<DecryptResult> CryptoContextDCRTPoly::DecryptByCiphertextAndPrivateKey(
    const CiphertextDCRTPoly& ciphertext, const PrivateKeyDCRTPoly& privateKey,
    Plaintext& plaintext) const
{
    std::shared_ptr<PlaintextImpl> p;
    std::unique_ptr<DecryptResult> res = std::make_unique<DecryptResult>(
    m_cryptoContextImplSharedPtr->Decrypt(ciphertext.GetInternal(), privateKey.GetInternal(), &p));
    plaintext = p;
    return res;
}
std::unique_ptr<DecryptResult> CryptoContextDCRTPoly::MultipartyDecryptFusion(
    const VectorOfCiphertexts& partialCiphertextVec, Plaintext& plaintext) const
{
    std::shared_ptr<PlaintextImpl> p;
    std::unique_ptr<DecryptResult> res = std::make_unique<DecryptResult>(
    m_cryptoContextImplSharedPtr->MultipartyDecryptFusion(partialCiphertextVec.GetInternal(), &p));
    plaintext = p;
    return res;
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
void CryptoContextDCRTPoly::EvalNegateInPlace(const CiphertextDCRTPoly& ciphertext) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    m_cryptoContextImplSharedPtr->EvalNegateInPlace(c);
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSquare(
    const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalSquare(ciphertext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalSquareMutable(
    const CiphertextDCRTPoly& ciphertext) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalSquareMutable(c));
}
void CryptoContextDCRTPoly::EvalSquareInPlace(const CiphertextDCRTPoly& ciphertext) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    m_cryptoContextImplSharedPtr->EvalSquareInPlace(c);
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
void CryptoContextDCRTPoly::RelinearizeInPlace(const CiphertextDCRTPoly& ciphertext) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    m_cryptoContextImplSharedPtr->RelinearizeInPlace(c);
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
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::KeySwitch(
    const CiphertextDCRTPoly& ciphertext, const EvalKeyDCRTPoly& evalKey) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->KeySwitch(
        ciphertext.GetInternal(), evalKey.GetInternal()));
}
void CryptoContextDCRTPoly::KeySwitchInPlace(const CiphertextDCRTPoly& ciphertext,
    const EvalKeyDCRTPoly& evalKey) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    m_cryptoContextImplSharedPtr->KeySwitchInPlace(c, evalKey.GetInternal());
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::LevelReduce(
    const CiphertextDCRTPoly& ciphertext, const EvalKeyDCRTPoly& evalKey,
    const size_t levels) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->LevelReduce(
        ciphertext.GetInternal(), evalKey.GetInternal(), levels));
}
void CryptoContextDCRTPoly::LevelReduceInPlace(const CiphertextDCRTPoly& ciphertext,
    const EvalKeyDCRTPoly& evalKey, const size_t levels) const
{
    std::shared_ptr<CiphertextImpl> c = ciphertext.GetInternal();
    m_cryptoContextImplSharedPtr->LevelReduceInPlace(c, evalKey.GetInternal(), levels);
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::ReEncrypt(
    const CiphertextDCRTPoly& ciphertext, const EvalKeyDCRTPoly& evalKey,
    const PublicKeyDCRTPoly& publicKey) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->ReEncrypt(
        ciphertext.GetInternal(), evalKey.GetInternal(), publicKey.GetInternal()));
}
std::unique_ptr<EvalKeyDCRTPoly> CryptoContextDCRTPoly::KeySwitchGen(
    const PrivateKeyDCRTPoly& oldPrivateKey, const PrivateKeyDCRTPoly& newPrivateKey) const
{
    return std::make_unique<EvalKeyDCRTPoly>(m_cryptoContextImplSharedPtr->KeySwitchGen(
        oldPrivateKey.GetInternal(), newPrivateKey.GetInternal()));
}
std::unique_ptr<EvalKeyDCRTPoly> CryptoContextDCRTPoly::ReKeyGen(
    const PrivateKeyDCRTPoly& oldPrivateKey, const PublicKeyDCRTPoly& newPublicKey) const
{
    return std::make_unique<EvalKeyDCRTPoly>(m_cryptoContextImplSharedPtr->ReKeyGen(
        oldPrivateKey.GetInternal(), newPublicKey.GetInternal()));
}
std::unique_ptr<EvalKeyDCRTPoly> CryptoContextDCRTPoly::MultiKeySwitchGen(
    const PrivateKeyDCRTPoly& originalPrivateKey, const PrivateKeyDCRTPoly& newPrivateKey,
    const EvalKeyDCRTPoly& evalKey) const
{
    return std::make_unique<EvalKeyDCRTPoly>(m_cryptoContextImplSharedPtr->MultiKeySwitchGen(
        originalPrivateKey.GetInternal(), newPrivateKey.GetInternal(), evalKey.GetInternal()));
}
std::unique_ptr<EvalKeyDCRTPoly> CryptoContextDCRTPoly::MultiAddEvalKeys(
    const EvalKeyDCRTPoly& evalKey1, const EvalKeyDCRTPoly& evalKey2,
    const std::string& keyId) const
{
    return std::make_unique<EvalKeyDCRTPoly>(m_cryptoContextImplSharedPtr->MultiAddEvalKeys(
        evalKey1.GetInternal(), evalKey2.GetInternal(), keyId));
}
std::unique_ptr<EvalKeyDCRTPoly> CryptoContextDCRTPoly::MultiMultEvalKey(
    const PrivateKeyDCRTPoly& privateKey, const EvalKeyDCRTPoly& evalKey,
    const std::string& keyId) const
{
    return std::make_unique<EvalKeyDCRTPoly>(m_cryptoContextImplSharedPtr->MultiMultEvalKey(
        privateKey.GetInternal(), evalKey.GetInternal(), keyId));
}
std::unique_ptr<EvalKeyDCRTPoly> CryptoContextDCRTPoly::MultiAddEvalMultKeys(
    const EvalKeyDCRTPoly& evalKey1, const EvalKeyDCRTPoly& evalKey2,
    const std::string& keyId) const
{
    return std::make_unique<EvalKeyDCRTPoly>(m_cryptoContextImplSharedPtr->MultiAddEvalMultKeys(
        evalKey1.GetInternal(), evalKey2.GetInternal(), keyId));
}
void CryptoContextDCRTPoly::EvalSumKeyGen(const PrivateKeyDCRTPoly& privateKey,
    const PublicKeyDCRTPoly& publicKey) const
{
    m_cryptoContextImplSharedPtr->EvalSumKeyGen(privateKey.GetInternal(), publicKey.GetInternal());
}
void CryptoContextDCRTPoly::EvalCKKStoFHEWKeyGen(const KeyPairDCRTPoly& keyPair,
    const LWEPrivateKey& lwesk) const
{
    m_cryptoContextImplSharedPtr->EvalCKKStoFHEWKeyGen({keyPair.GetPublicKey()->GetInternal(),
        keyPair.GetPrivateKey()->GetInternal()}, lwesk.GetInternal());
}
void CryptoContextDCRTPoly::EvalFHEWtoCKKSKeyGen(const KeyPairDCRTPoly& keyPair,
    const LWEPrivateKey& lwesk, const uint32_t numSlots, const uint32_t numCtxts,
    const uint32_t dim1, const uint32_t L) const
{
    m_cryptoContextImplSharedPtr->EvalFHEWtoCKKSKeyGen({keyPair.GetPublicKey()->GetInternal(),
        keyPair.GetPrivateKey()->GetInternal()}, lwesk.GetInternal(), numSlots, numCtxts, dim1, L);
}
void CryptoContextDCRTPoly::EvalSchemeSwitchingKeyGen(const KeyPairDCRTPoly& keyPair,
    const LWEPrivateKey& lwesk) const
{
    m_cryptoContextImplSharedPtr->EvalSchemeSwitchingKeyGen({keyPair.GetPublicKey()->GetInternal(),
        keyPair.GetPrivateKey()->GetInternal()}, lwesk.GetInternal());
}
uint64_t CryptoContextDCRTPoly::GetModulus() const
{
    return m_cryptoContextImplSharedPtr->GetModulus().ConvertToInt();
}
uint64_t CryptoContextDCRTPoly::GetRootOfUnity() const
{
    return m_cryptoContextImplSharedPtr->GetRootOfUnity().ConvertToInt();
}
std::unique_ptr<VectorOfCiphertexts> CryptoContextDCRTPoly::MultipartyDecryptLead(
    const VectorOfCiphertexts& ciphertextVec, const PrivateKeyDCRTPoly& privateKey) const
{
    return std::make_unique<VectorOfCiphertexts>(
        m_cryptoContextImplSharedPtr->MultipartyDecryptLead(ciphertextVec.GetInternal(),
        privateKey.GetInternal()));
}
std::unique_ptr<VectorOfCiphertexts> CryptoContextDCRTPoly::MultipartyDecryptMain(
    const VectorOfCiphertexts& ciphertextVec, const PrivateKeyDCRTPoly& privateKey) const
{
    return std::make_unique<VectorOfCiphertexts>(
        m_cryptoContextImplSharedPtr->MultipartyDecryptMain(ciphertextVec.GetInternal(),
        privateKey.GetInternal()));
}
std::unique_ptr<VectorOfCiphertexts> CryptoContextDCRTPoly::IntMPBootDecrypt(
    const PrivateKeyDCRTPoly& privateKey, const CiphertextDCRTPoly& ciphertext,
    const CiphertextDCRTPoly& a) const
{
    return std::make_unique<VectorOfCiphertexts>(m_cryptoContextImplSharedPtr->IntMPBootDecrypt(
        privateKey.GetInternal(), ciphertext.GetInternal(), a.GetInternal()));
}
std::unique_ptr<VectorOfCiphertexts> CryptoContextDCRTPoly::EvalMinSchemeSwitching(
    const CiphertextDCRTPoly& ciphertext, const PublicKeyDCRTPoly& publicKey,
    const uint32_t numValues, const uint32_t numSlots, const uint32_t pLWE,
    const double scaleSign) const
{
    return std::make_unique<VectorOfCiphertexts>(
        m_cryptoContextImplSharedPtr->EvalMinSchemeSwitching(ciphertext.GetInternal(),
        publicKey.GetInternal(), numValues, numSlots, pLWE, scaleSign));
}
std::unique_ptr<VectorOfCiphertexts> CryptoContextDCRTPoly::EvalMinSchemeSwitchingAlt(
    const CiphertextDCRTPoly& ciphertext, const PublicKeyDCRTPoly& publicKey,
    const uint32_t numValues, const uint32_t numSlots, const uint32_t pLWE,
    const double scaleSign) const
{
    return std::make_unique<VectorOfCiphertexts>(
        m_cryptoContextImplSharedPtr->EvalMinSchemeSwitchingAlt(ciphertext.GetInternal(),
        publicKey.GetInternal(), numValues, numSlots, pLWE, scaleSign));
}
std::unique_ptr<VectorOfCiphertexts> CryptoContextDCRTPoly::EvalMaxSchemeSwitching(
    const CiphertextDCRTPoly& ciphertext, const PublicKeyDCRTPoly& publicKey,
    const uint32_t numValues, const uint32_t numSlots, const uint32_t pLWE,
    const double scaleSign) const
{
    return std::make_unique<VectorOfCiphertexts>(
        m_cryptoContextImplSharedPtr->EvalMaxSchemeSwitching(ciphertext.GetInternal(),
        publicKey.GetInternal(), numValues, numSlots, pLWE, scaleSign));
}
std::unique_ptr<VectorOfCiphertexts> CryptoContextDCRTPoly::EvalMaxSchemeSwitchingAlt(
    const CiphertextDCRTPoly& ciphertext, const PublicKeyDCRTPoly& publicKey,
    const uint32_t numValues, const uint32_t numSlots, const uint32_t pLWE,
    const double scaleSign) const
{
    return std::make_unique<VectorOfCiphertexts>(
        m_cryptoContextImplSharedPtr->EvalMaxSchemeSwitchingAlt(ciphertext.GetInternal(),
        publicKey.GetInternal(), numValues, numSlots, pLWE, scaleSign));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAddMany(
    const VectorOfCiphertexts& ciphertextVec) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAddMany(
        ciphertextVec.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMultMany(
    const VectorOfCiphertexts& ciphertextVec) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMultMany(
        ciphertextVec.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalMerge(
    const VectorOfCiphertexts& ciphertextVec) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalMerge(
        ciphertextVec.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::IntMPBootEncrypt(
    const PublicKeyDCRTPoly& publicKey, const VectorOfCiphertexts& sharesPair,
    const CiphertextDCRTPoly& a, const CiphertextDCRTPoly& ciphertext) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->IntMPBootEncrypt(
        publicKey.GetInternal(), sharesPair.GetInternal(), a.GetInternal(),
        ciphertext.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalAddManyInPlace(
    VectorOfCiphertexts& ciphertextVec) const
{
    return std::make_unique<CiphertextDCRTPoly>(m_cryptoContextImplSharedPtr->EvalAddManyInPlace(
        ciphertextVec.GetInternal()));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalLinearWSumMutable(
    VectorOfCiphertexts& ciphertextVec, const std::vector<double>& constantsVec) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalLinearWSumMutable(ciphertextVec.GetInternal(),
        constantsVec));
}
std::unique_ptr<CiphertextDCRTPoly> CryptoContextDCRTPoly::EvalLinearWSumMutable(
    const std::vector<double>& constantsVec, VectorOfCiphertexts& ciphertextVec) const
{
    return std::make_unique<CiphertextDCRTPoly>(
        m_cryptoContextImplSharedPtr->EvalLinearWSumMutable(constantsVec,
        ciphertextVec.GetInternal()));
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
    return std::make_unique<std::vector<uint32_t>>(CryptoContextImpl::GetUniqueValues(oldValues,
        newValues));
}
std::unique_ptr<CryptoContextDCRTPoly> GenNullCryptoContext()
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
