#include <iostream>
#include <map>
#include "openfhe.h"
#include "key/key-ser.h"
#include "bindings.hpp"
#include "pke/cryptocontext_wrapper.hpp"
// #include "binfhe_bindings.h"
// #include "cryptocontext_docs.h"
// #include "cryptoparameters_docs.h"
// #include "plaintext_docs.h"
// #include "ciphertext_docs.h"
#include "pke/scheme/bfvrns/gen-cryptocontext-bfvrns-params.h"
#include "pke/serialization.hpp"
#include "constants.h"

using namespace lbcrypto;

namespace {
    struct ParamsHolder{
           std::shared_ptr<Params> ptr;
    };

    struct CryptoContextImplHolder{
           std::shared_ptr<CryptoContextImpl<DCRTPoly>> ptr;
    };
}

FFIParams::FFIParams(){
    params_ptr = reinterpret_cast<void*>(
        new ParamsHolder{std::make_shared<Params>()});
}

FFIParams::FFIParams(FFISCHEME scheme){
    params_ptr = reinterpret_cast<void*>(
        new ParamsHolder{std::make_shared<Params>(lbcrypto::SCHEME(scheme))});
}

// getters

FFIPlaintextModulus FFIParams::GetPlaintextModulus() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return FFISCHEME(cc_params->GetPlaintextModulus());
}

FFISCHEME FFIParams::GetScheme() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return FFISCHEME(cc_params->GetScheme());
}

usint FFIParams::GetDigitSize() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return cc_params->GetDigitSize();
}

float FFIParams::GetStandardDeviation() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return cc_params->GetStandardDeviation();
}

FFISecretKeyDist FFIParams::GetSecretKeyDist() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return FFISecretKeyDist(cc_params->GetSecretKeyDist());
}

usint FFIParams::GetMaxRelinSkDeg() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return cc_params->GetMaxRelinSkDeg();
}

FFIProxyReEncryptionMode FFIParams::GetPREMode() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return FFIProxyReEncryptionMode(cc_params->GetPREMode());
}

FFIMultipartyMode FFIParams::GetMultipartyMode() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return FFIMultipartyMode(cc_params->GetMultipartyMode());
}

FFIExecutionMode FFIParams::GetExecutionMode() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return FFIExecutionMode(cc_params->GetExecutionMode());
}

FFIDecryptionNoiseMode FFIParams::GetDecryptionNoiseMode() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return FFIDecryptionNoiseMode(cc_params->GetDecryptionNoiseMode());
}

double FFIParams::GetNoiseEstimate() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return cc_params->GetNoiseEstimate();
}

double FFIParams::GetDesiredPrecision() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return cc_params->GetDesiredPrecision();
}

double FFIParams::GetStatisticalSecurity() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return cc_params->GetStatisticalSecurity();
}

double FFIParams::GetNumAdversarialQueries() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return cc_params->GetNumAdversarialQueries();
}

usint FFIParams::GetThresholdNumOfParties() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return cc_params->GetThresholdNumOfParties();
}

FFIKeySwitchTechnique FFIParams::GetKeySwitchTechnique() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return FFIKeySwitchTechnique(cc_params->GetKeySwitchTechnique());
}

FFIScalingTechnique FFIParams::GetScalingTechnique() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return FFIScalingTechnique(cc_params->GetScalingTechnique());
}

usint FFIParams::GetBatchSize() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return cc_params->GetBatchSize();
}

usint FFIParams::GetFirstModSize() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return cc_params->GetFirstModSize();
}

uint32_t FFIParams::GetNumLargeDigits() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return static_cast<uint32_t>(cc_params->GetNumLargeDigits());
}

usint FFIParams::GetMultiplicativeDepth() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return static_cast<usint>(cc_params->GetMultiplicativeDepth());
}

usint FFIParams::GetScalingModSize() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return static_cast<usint>(cc_params->GetScalingModSize());
}

FFISecurityLevel FFIParams::GetSecurityLevel() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return FFISecurityLevel(cc_params->GetSecurityLevel());
}

usint FFIParams::GetRingDim() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return cc_params->GetRingDim();
}

usint FFIParams::GetEvalAddCount() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return cc_params->GetEvalAddCount();
}

usint FFIParams::GetKeySwitchCount() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return cc_params->GetKeySwitchCount();
}

FFIEncryptionTechnique FFIParams::GetEncryptionTechnique() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return FFIEncryptionTechnique(cc_params->GetEncryptionTechnique());
}

FFIMultiplicationTechnique FFIParams::GetMultiplicationTechnique() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return FFIMultiplicationTechnique(cc_params->GetMultiplicationTechnique());
}

usint FFIParams::GetMultiHopModSize() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return cc_params->GetMultiHopModSize();
}

FFICOMPRESSION_LEVEL FFIParams::GetInteractiveBootCompressionLevel() const{
    std::shared_ptr<const Params> cc_params =
        reinterpret_cast<const ParamsHolder*>(params_ptr)->ptr;
    return FFICOMPRESSION_LEVEL(cc_params->GetInteractiveBootCompressionLevel());
}

// setters

void FFIParams::SetPlaintextModulus(FFIPlaintextModulus ptModulus){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetPlaintextModulus(ptModulus);
}

void FFIParams::SetDigitSize(usint digitSize){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetDigitSize(digitSize);
}

void FFIParams::SetStandardDeviation(float standardDeviation){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetStandardDeviation(standardDeviation);
}

void FFIParams::SetSecretKeyDist(FFISecretKeyDist secretKeyDist){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetSecretKeyDist(lbcrypto::SecretKeyDist(secretKeyDist));
}

void FFIParams::SetMaxRelinSkDeg(usint maxRelinSkDeg){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetMaxRelinSkDeg(maxRelinSkDeg);
}

void FFIParams::SetPREMode(FFIProxyReEncryptionMode preMode){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetPREMode(lbcrypto::ProxyReEncryptionMode(preMode));
}

void FFIParams::SetMultipartyMode(FFIMultipartyMode multipartyMode){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetMultipartyMode(lbcrypto::MultipartyMode(multipartyMode));
}

void FFIParams::SetExecutionMode(FFIExecutionMode executionMode){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetExecutionMode(lbcrypto::ExecutionMode(executionMode));
}

void FFIParams::SetDecryptionNoiseMode(FFIDecryptionNoiseMode decryptionNoiseMode){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetDecryptionNoiseMode(lbcrypto::DecryptionNoiseMode(decryptionNoiseMode));
}

void FFIParams::SetNoiseEstimate(double noiseEstimate){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetNoiseEstimate(noiseEstimate);
}

void FFIParams::SetDesiredPrecision(double desiredPrecision){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetDesiredPrecision(desiredPrecision);
}

void FFIParams::SetStatisticalSecurity(uint32_t statisticalSecurity){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetStatisticalSecurity(statisticalSecurity);
}

void FFIParams::SetNumAdversarialQueries(uint32_t numAdversarialQueries){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetNumAdversarialQueries(numAdversarialQueries);
}

void FFIParams::SetThresholdNumOfParties(uint32_t thresholdNumOfParties){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetThresholdNumOfParties(thresholdNumOfParties);
}

void FFIParams::SetKeySwitchTechnique(FFIKeySwitchTechnique keySwitchTechnique){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetKeySwitchTechnique(lbcrypto::KeySwitchTechnique(keySwitchTechnique));
}

void FFIParams::SetScalingTechnique(FFIScalingTechnique scalingTechnique){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetScalingTechnique(lbcrypto::ScalingTechnique(scalingTechnique));
}

void FFIParams::SetBatchSize(usint batchSize){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetBatchSize(batchSize);
}

void FFIParams::SetFirstModSize(usint firstModSize){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetFirstModSize(firstModSize);
}

void FFIParams::SetNumLargeDigits(usint numLargeDigits){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetNumLargeDigits(numLargeDigits);
}

void FFIParams::SetMultiplicativeDepth(usint multiplicativeDepth){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetMultiplicativeDepth(multiplicativeDepth);
}

void FFIParams::SetScalingModSize(usint scalingModSize){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetScalingModSize(scalingModSize);
}

void FFIParams::SetSecurityLevel(FFISecurityLevel securityLevel){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetSecurityLevel(lbcrypto::SecurityLevel(securityLevel));
}

void FFIParams::SetRingDim(usint ringDim){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetRingDim(ringDim);
}

void FFIParams::SetEvalAddCount(usint evalAddCount){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetEvalAddCount(evalAddCount);
}

void FFIParams::SetKeySwitchCount(usint keySwitchCount){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetKeySwitchCount(keySwitchCount);
}

void FFIParams::SetEncryptionTechnique(FFIEncryptionTechnique encryptionTechnique){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetEncryptionTechnique(lbcrypto::EncryptionTechnique(encryptionTechnique));
}

void FFIParams::SetMultiplicationTechnique(FFIMultiplicationTechnique multiplicationTechnique){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetMultiplicationTechnique(lbcrypto::MultiplicationTechnique(multiplicationTechnique));
}

void FFIParams::SetMultiHopModSize(usint multiHopModSize){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetMultiHopModSize(multiHopModSize);
}

void FFIParams::SetInteractiveBootCompressionLevel(FFICOMPRESSION_LEVEL interactiveBootCompressionLevel){
    std::shared_ptr<Params> cc_params =
        reinterpret_cast<ParamsHolder*>(params_ptr)->ptr;
    cc_params->SetInteractiveBootCompressionLevel(lbcrypto::COMPRESSION_LEVEL(interactiveBootCompressionLevel));
}

FFICryptoContextImpl::FFICryptoContextImpl(){
    cc_ptr = reinterpret_cast<void*>(
        new CryptoContextImplHolder{std::make_shared<CryptoContextImpl<DCRTPoly>>()});
}

std::size_t FFICryptoContextImpl::GetKeyGenLevel() const{
    std::shared_ptr<const CryptoContextImpl<DCRTPoly>> cc =
        reinterpret_cast<const CryptoContextImplHolder*>(cc_ptr)->ptr;
    return cc->GetKeyGenLevel();
}

void FFICryptoContextImpl::SetKeyGenLevel(std::size_t level){
    std::shared_ptr<CryptoContextImpl<DCRTPoly>> cc =
        reinterpret_cast<CryptoContextImplHolder*>(cc_ptr)->ptr;
    cc->SetKeyGenLevel(level);
}

usint FFICryptoContextImpl::GetRingDimension() const{
    std::shared_ptr<const CryptoContextImpl<DCRTPoly>> cc =
        reinterpret_cast<const CryptoContextImplHolder*>(cc_ptr)->ptr;
    return cc->GetRingDimension();
}

FFIPlaintextModulus FFICryptoContextImpl::GetPlaintextModulus() const{
    std::shared_ptr<CryptoContextImpl<DCRTPoly>> cc =
        reinterpret_cast<const CryptoContextImplHolder*>(cc_ptr)->ptr;
    return FFIPlaintextModulus(GetPlaintextModulusWrapper(cc));
}

double FFICryptoContextImpl::GetModulus() const {
    std::shared_ptr<CryptoContextImpl<DCRTPoly>> cc =
        reinterpret_cast<const CryptoContextImplHolder*>(cc_ptr)->ptr;
    return GetModulusWrapper(cc);
}

const uint64_t FFICryptoContextImpl::GetModulusCKKS() const{
    std::shared_ptr<CryptoContextImpl<DCRTPoly>> cc =
        reinterpret_cast<const CryptoContextImplHolder*>(cc_ptr)->ptr;
    return GetModulusCKKSWrapper(cc);
}

double FFICryptoContextImpl::GetScalingFactorReal(uint32_t level) const{
    std::shared_ptr<CryptoContextImpl<DCRTPoly>> cc =
        reinterpret_cast<const CryptoContextImplHolder*>(cc_ptr)->ptr;
    return GetScalingFactorRealWrapper(cc, level);
}

FFIScalingTechnique FFICryptoContextImpl::GetScalingTechnique() const{
    std::shared_ptr<CryptoContextImpl<DCRTPoly>> cc =
        reinterpret_cast<const CryptoContextImplHolder*>(cc_ptr)->ptr;
    return FFIScalingTechnique(GetScalingTechniqueWrapper(cc));
}

usint FFICryptoContextImpl::GetDigitSize() const{
    std::shared_ptr<CryptoContextImpl<DCRTPoly>> cc =
        reinterpret_cast<const CryptoContextImplHolder*>(cc_ptr)->ptr;
    return GetDigitSizeWrapper(cc);
}

usint FFICryptoContextImpl::GetCyclotomicOrder() const{
    std::shared_ptr<const CryptoContextImpl<DCRTPoly>> cc =
        reinterpret_cast<const CryptoContextImplHolder*>(cc_ptr)->ptr;
    return cc->GetCyclotomicOrder();
}

void FFICryptoContextImpl::Enable(FFIPKESchemeFeature feature) {
    std::shared_ptr<CryptoContextImpl<DCRTPoly>> cc =
        reinterpret_cast<CryptoContextImplHolder*>(cc_ptr)->ptr;
    cc->Enable(PKESchemeFeature(feature));
}

// void bind_crypto_context(py::module &m)
// {
//     py::class_<CryptoContextImpl<DCRTPoly>, std::shared_ptr<CryptoContextImpl<DCRTPoly>>>(m, "CryptoContext")
//         .def("KeyGen", &CryptoContextImpl<DCRTPoly>::KeyGen, cc_KeyGen_docs)
//         .def("EvalMultKeyGen", &CryptoContextImpl<DCRTPoly>::EvalMultKeyGen,
//              cc_EvalMultKeyGen_docs,
//              py::arg("privateKey"))
//         .def("EvalMultKeysGen", &CryptoContextImpl<DCRTPoly>::EvalMultKeysGen,
//              cc_EvalMultKeysGen_docs,
//              py::arg("privateKey"))
//         .def("EvalRotateKeyGen", &CryptoContextImpl<DCRTPoly>::EvalRotateKeyGen,
//              cc_EvalRotateKeyGen_docs,
//              py::arg("privateKey"),
//              py::arg("indexList"),
//              py::arg("publicKey") = nullptr)
//         .def("MakeStringPlaintext", &CryptoContextImpl<DCRTPoly>::MakeStringPlaintext,
//              cc_MakeStringPlaintext_docs,
//              py::arg("str"))
//         .def("MakePackedPlaintext", &CryptoContextImpl<DCRTPoly>::MakePackedPlaintext,
//              cc_MakePackedPlaintext_docs,
//              py::arg("value"),
//              py::arg("noiseScaleDeg") = 1,
//              py::arg("level") = 0)
//         .def("MakeCoefPackedPlaintext", &CryptoContextImpl<DCRTPoly>::MakeCoefPackedPlaintext,
//             cc_MakeCoefPackedPlaintext_docs,
//             py::arg("value"),
//             py::arg("noiseScaleDeg ") = 1,
//             py::arg("level") = 0)
//         // TODO (Oliveira): allow user to specify different params values
//         .def("MakeCKKSPackedPlaintext", static_cast<Plaintext (CryptoContextImpl<DCRTPoly>::*)(const std::vector<std::complex<double>> &, size_t, uint32_t, const std::shared_ptr<ParmType>, usint) const>(&CryptoContextImpl<DCRTPoly>::MakeCKKSPackedPlaintext), cc_MakeCKKSPackedPlaintextComplex_docs,
//              py::arg("value"),
//              py::arg("scaleDeg") = static_cast<size_t>(1),
//              py::arg("level") = static_cast<uint32_t>(0),
//              py::arg("params") = py::none(),
//              py::arg("slots") = 0)
//         .def("MakeCKKSPackedPlaintext", static_cast<Plaintext (CryptoContextImpl<DCRTPoly>::*)(const std::vector<double> &, size_t, uint32_t, const std::shared_ptr<ParmType>, usint) const>(&CryptoContextImpl<DCRTPoly>::MakeCKKSPackedPlaintext), cc_MakeCKKSPlaintextReal_docs,
//              py::arg("value"),
//              py::arg("scaleDeg") = static_cast<size_t>(1),
//              py::arg("level") = static_cast<uint32_t>(0),
//              py::arg("params") = py::none(),
//              py::arg("slots") = 0)
//         .def("EvalRotate", &CryptoContextImpl<DCRTPoly>::EvalRotate,
//             cc_EvalRotate_docs,
//             py::arg("ciphertext"),
//             py::arg("index"))
//         .def("EvalFastRotationPrecompute", &EvalFastRotationPrecomputeWrapper,
//             cc_EvalFastRotationPreCompute_docs,
//             py::arg("ciphertext"))
//         .def("EvalFastRotation", &EvalFastRotationWrapper,
//             cc_EvalFastRotation_docs,
//             py::arg("ciphertext"),
//             py::arg("index"),
//             py::arg("m"),
//             py::arg("digits"))
//         .def("EvalFastRotationExt", &EvalFastRotationExtWrapper, 
//             cc_EvalFastRotationExt_docs,
//             py::arg("ciphertext"),
//             py::arg("index"),
//             py::arg("digits"),
//             py::arg("addFirst"))
//         .def("EvalAtIndexKeyGen", &CryptoContextImpl<DCRTPoly>::EvalAtIndexKeyGen,
//             cc_EvalAtIndexKeyGen_docs,
//             py::arg("privateKey"),
//             py::arg("indexList"),
//             py::arg("publicKey") = nullptr)
//         .def("EvalAtIndex", &CryptoContextImpl<DCRTPoly>::EvalAtIndex,
//             cc_EvalAtIndex_docs,
//             py::arg("ciphertext"),
//             py::arg("index"))
//         .def("Encrypt", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(const PublicKey<DCRTPoly>, Plaintext) const>
//             (&CryptoContextImpl<DCRTPoly>::Encrypt),
//             cc_Encrypt_docs,
//             py::arg("publicKey"),
//             py::arg("plaintext"))
//         .def("Decrypt", static_cast<Plaintext (*)(CryptoContext<DCRTPoly> &, const PrivateKey<DCRTPoly>, ConstCiphertext<DCRTPoly>)>
//             (&DecryptWrapper), cc_Decrypt_docs,
//             py::arg("privateKey"),
//             py::arg("ciphertext"))
//         .def("Decrypt", static_cast<Plaintext (*)(CryptoContext<DCRTPoly> &, ConstCiphertext<DCRTPoly>, const PrivateKey<DCRTPoly>)>
//             (&DecryptWrapper), cc_Decrypt_docs,
//             py::arg("ciphertext"),
//             py::arg("privateKey"))
//         .def("KeySwitchGen", &CryptoContextImpl<DCRTPoly>::KeySwitchGen,
//             cc_KeySwitchGen_docs,
//             py::arg("oldPrivateKey"),
//             py::arg("newPrivateKey"))
//         .def("EvalAdd", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(ConstCiphertext<DCRTPoly>, ConstCiphertext<DCRTPoly>) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalAdd), 
//             cc_EvalAdd_docs,
//             py::arg("ciphertext1"),
//             py::arg("ciphertext2"))
//         .def("EvalAdd", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(ConstCiphertext<DCRTPoly>, double) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalAdd), 
//             cc_EvalAddfloat_docs,
//             py::arg("ciphertext"),
//             py::arg("constant"))
//         //inline Ciphertext<Element> EvalAdd(ConstCiphertext<Element> ciphertext, ConstPlaintext plaintext) const
//         .def("EvalAdd", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(ConstCiphertext<DCRTPoly>, ConstPlaintext) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalAdd),
//             cc_EvalAddPlaintext_docs,
//             py::arg("ciphertext"),
//             py::arg("plaintext"))
//         .def("EvalAddInPlace", static_cast<void (CryptoContextImpl<DCRTPoly>::*)(Ciphertext<DCRTPoly> &, ConstCiphertext<DCRTPoly>) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalAddInPlace),
//             cc_EvalAddInPlace_docs,
//             py::arg("ciphertext1"),
//             py::arg("ciphertext2"))
//         .def("EvalAddInPlace", static_cast<void (CryptoContextImpl<DCRTPoly>::*)(Ciphertext<DCRTPoly> &, ConstPlaintext) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalAddInPlace),
//             cc_EvalAddInPlacePlaintext_docs,
//             py::arg("ciphertext"),
//             py::arg("plaintext"))
//         .def("EvalAddInPlace", static_cast<void (CryptoContextImpl<DCRTPoly>::*)(ConstPlaintext, Ciphertext<DCRTPoly> &) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalAddInPlace),
//             "",
//             py::arg("plaintext"),
//             py::arg("ciphertext"))
//         .def("EvalAddMutable", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(Ciphertext<DCRTPoly> &, Ciphertext<DCRTPoly> &) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalAddMutable),
//             cc_EvalAddMutable_docs,
//             py::arg("ciphertext1"),
//             py::arg("ciphertext2"))
//         .def("EvalAddMutable", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(Ciphertext<DCRTPoly> &, Plaintext) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalAddMutable),
//             cc_EvalAddMutablePlaintext_docs,
//             py::arg("ciphertext"),
//             py::arg("plaintext"))
//         .def("EvalAddMutable", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(Plaintext, Ciphertext<DCRTPoly> &) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalAddMutable),
//             "",
//             py::arg("plaintext"),
//             py::arg("ciphertext"))
//         .def("EvalAddMutableInPlace", &CryptoContextImpl<DCRTPoly>::EvalAddMutableInPlace,
//             cc_EvalAddMutableInPlace_docs,
//             py::arg("ciphertext1"),
//             py::arg("ciphertext2"))
//         .def("EvalSub", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(ConstCiphertext<DCRTPoly>, ConstCiphertext<DCRTPoly>) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalSub),
//             cc_EvalSub_docs,
//             py::arg("ciphertext1"),
//             py::arg("ciphertext2"))
//         .def("EvalSub", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(ConstCiphertext<DCRTPoly>, double) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalSub),
//             cc_EvalSubfloat_docs,
//             py::arg("ciphertext"),
//             py::arg("constant"))
//         .def("EvalSub", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(double, ConstCiphertext<DCRTPoly>) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalSub),
//             "",
//             py::arg("constant"),
//             py::arg("ciphertext"))
//         .def("EvalSub", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(ConstCiphertext<DCRTPoly>, ConstPlaintext) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalSub),
//             cc_EvalSubPlaintext_docs,
//             py::arg("ciphertext"),
//             py::arg("plaintext"))
//         .def("EvalSub", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(ConstPlaintext, ConstCiphertext<DCRTPoly>) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalSub),
//             "",
//             py::arg("plaintext"),
//             py::arg("ciphertext"))
//         .def("EvalSubInPlace", static_cast<void (CryptoContextImpl<DCRTPoly>::*)(Ciphertext<DCRTPoly> &, ConstCiphertext<DCRTPoly>) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalSubInPlace),
//             cc_EvalSubInPlace_docs,
//             py::arg("ciphertext1"),
//             py::arg("ciphertext2"))
//         .def("EvalSubInPlace", static_cast<void (CryptoContextImpl<DCRTPoly>::*)(Ciphertext<DCRTPoly> &, double) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalSubInPlace),
//             cc_EvalSubInPlacefloat_docs,
//             py::arg("ciphertext"),
//             py::arg("constant"))
//         .def("EvalSubInPlace", static_cast<void (CryptoContextImpl<DCRTPoly>::*)(double, Ciphertext<DCRTPoly> &) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalSubInPlace),
//             "",
//             py::arg("constant"),
//             py::arg("ciphertext"))
//         .def("EvalSubMutable", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(Ciphertext<DCRTPoly> &, Ciphertext<DCRTPoly> &) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalSubMutable),
//             cc_EvalSubMutable_docs,
//             py::arg("ciphertext1"),
//             py::arg("ciphertext2"))
//         .def("EvalSubMutable", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(Ciphertext<DCRTPoly> &, Plaintext) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalSubMutable),
//             cc_EvalSubMutablePlaintext_docs,
//             py::arg("ciphertext"),
//             py::arg("plaintext"))
//         .def("EvalSubMutable", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(Plaintext, Ciphertext<DCRTPoly> &) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalSubMutable),
//             "",
//             py::arg("plaintext"),
//             py::arg("ciphertext"))
//IAMHERE:         .def("EvalSubMutableInPlace", &CryptoContextImpl<DCRTPoly>::EvalSubMutableInPlace,
//             cc_EvalSubMutableInPlace_docs,
//             py::arg("ciphertext1"),
//             py::arg("ciphertext2"))
//         .def("EvalMult", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(ConstCiphertext<DCRTPoly>, ConstCiphertext<DCRTPoly>) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalMult),
//             cc_EvalMult_docs,
//             py::arg("ciphertext1"),
//             py::arg("ciphertext2"))
//         .def("EvalMult", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(ConstCiphertext<DCRTPoly>, double) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalMult),
//             cc_EvalMultfloat_docs,
//             py::arg("ciphertext"),
//             py::arg("constant"))
//         .def("EvalMult", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(ConstCiphertext<DCRTPoly>, ConstPlaintext) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalMult),
//             cc_EvalMultPlaintext_docs,
//             py::arg("ciphertext"),
//             py::arg("plaintext"))
//         .def("EvalMult", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(ConstPlaintext, ConstCiphertext<DCRTPoly>) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalMult),
//             "",
//             py::arg("plaintext"),
//             py::arg("ciphertext"))
//         .def("EvalMult", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(double, ConstCiphertext<DCRTPoly>) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalMult),
//             "",
//             py::arg("constant"),
//             py::arg("ciphertext"))
//         .def("EvalMultMutable", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(Ciphertext<DCRTPoly> &, Ciphertext<DCRTPoly> &) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalMultMutable),
//             cc_EvalMultMutable_docs,
//             py::arg("ciphertext1"),
//             py::arg("ciphertext2"))
//         .def("EvalMultMutable", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(Ciphertext<DCRTPoly> &, Plaintext) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalMultMutable),
//             cc_EvalMultMutablePlaintext_docs,
//             py::arg("ciphertext"),
//             py::arg("plaintext"))
//         .def("EvalMultMutable", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(Plaintext, Ciphertext<DCRTPoly> &) const>
//             (&CryptoContextImpl<DCRTPoly>::EvalMultMutable),
//             "",
//             py::arg("plaintext"),
//             py::arg("ciphertext"))
//         .def("EvalMultMutableInPlace", &CryptoContextImpl<DCRTPoly>::EvalMultMutableInPlace,
//             cc_EvalMultMutableInPlace_docs,
//             py::arg("ciphertext1"),
//             py::arg("ciphertext2"))
//         .def("EvalSquare", &CryptoContextImpl<DCRTPoly>::EvalSquare,
//             cc_EvalSquare_docs,
//             py::arg("ciphertext"))
//         .def("EvalSquareMutable", &CryptoContextImpl<DCRTPoly>::EvalSquareMutable,
//             cc_EvalSquareMutable_docs,
//             py::arg("ciphertext"))
//         .def("EvalSquareInPlace", &CryptoContextImpl<DCRTPoly>::EvalSquareInPlace,
//             cc_EvalSquareInPlace_docs,
//             py::arg("ciphertext"))
//         .def("EvalMultNoRelin", &CryptoContextImpl<DCRTPoly>::EvalMultNoRelin,
//             cc_EvalMultNoRelin_docs,
//             py::arg("ciphertext1"),
//             py::arg("ciphertext2"))
//         .def("Relinearize", &CryptoContextImpl<DCRTPoly>::Relinearize,
//             cc_Relinearize_docs,
//             py::arg("ciphertext"))
//         .def("RelinearizeInPlace", &CryptoContextImpl<DCRTPoly>::RelinearizeInPlace,
//             cc_RelinearizeInPlace_docs,
//             py::arg("ciphertext"))
//         .def("EvalMultAndRelinearize", &CryptoContextImpl<DCRTPoly>::EvalMultAndRelinearize,
//             cc_EvalMultAndRelinearize_docs,
//             py::arg("ciphertext1"),
//             py::arg("ciphertext2"))
//         .def("EvalNegate", &CryptoContextImpl<DCRTPoly>::EvalNegate,
//             cc_EvalNegate_docs,
//             py::arg("ciphertext"))
//         .def("EvalNegateInPlace", &CryptoContextImpl<DCRTPoly>::EvalNegateInPlace,
//             cc_EvalNegateInPlace_docs,
//             py::arg("ciphertext"))
//         .def("EvalLogistic", &CryptoContextImpl<DCRTPoly>::EvalLogistic,
//             cc_EvalLogistic_docs,
//             py::arg("ciphertext"),
//             py::arg("a"),
//             py::arg("b"),
//             py::arg("degree"))
//         .def("EvalChebyshevSeries", &CryptoContextImpl<DCRTPoly>::EvalChebyshevSeries,
//             cc_EvalChebyshevSeries_docs,
//             py::arg("ciphertext"),
//             py::arg("coefficients"),
//             py::arg("a"),
//             py::arg("b"))
//         .def("EvalChebyshevSeriesLinear", &CryptoContextImpl<DCRTPoly>::EvalChebyshevSeriesLinear,
//             cc_EvalChebyshevSeriesLinear_docs,
//             py::arg("ciphertext"),
//             py::arg("coefficients"),
//             py::arg("a"),
//             py::arg("b"))
//         .def("EvalChebyshevSeriesPS", &CryptoContextImpl<DCRTPoly>::EvalChebyshevSeriesPS,
//             cc_EvalChebyshevSeriesPS_docs,
//             py::arg("ciphertext"),
//             py::arg("coefficients"),
//             py::arg("a"),
//             py::arg("b"))
//         .def("EvalChebyshevFunction", &CryptoContextImpl<DCRTPoly>::EvalChebyshevFunction,
//             cc_EvalChebyshevFunction_docs,
//              py::arg("func"),
//              py::arg("ciphertext"),
//              py::arg("a"),
//              py::arg("b"),
//              py::arg("degree"))
//         .def("EvalSin", &CryptoContextImpl<DCRTPoly>::EvalSin,
//              cc_EvalSin_docs,
//              py::arg("ciphertext"),
//              py::arg("a"),
//              py::arg("b"),
//              py::arg("degree"))
//         .def("EvalCos", &CryptoContextImpl<DCRTPoly>::EvalCos,
//              cc_EvalCos_docs,
//              py::arg("ciphertext"),
//              py::arg("a"),
//              py::arg("b"),
//              py::arg("degree"))
//         .def("EvalDivide", &CryptoContextImpl<DCRTPoly>::EvalDivide,
//              cc_EvalDivide_docs,
//              py::arg("ciphertext"),
//              py::arg("a"),
//              py::arg("b"),
//              py::arg("degree"))
//         .def("EvalSumKeyGen", &CryptoContextImpl<DCRTPoly>::EvalSumKeyGen,
//              cc_EvalSumKeyGen_docs,
//              py::arg("privateKey"),
//              py::arg("publicKey") = py::none())
//         //TODO (Oliveira, R.): Solve pointer handling bug when dealing with EvalKeyMap object for the next functions 
//         .def("EvalSumRowsKeyGen", &CryptoContextImpl<DCRTPoly>::EvalSumRowsKeyGen,
//              cc_EvalSumRowsKeyGen_docs,
//              py::arg("privateKey"),
//              py::arg("publicKey") = py::none(),
//              py::arg("rowSize") = 0,
//              py::arg("subringDim") = 0)
//         .def("EvalSumColsKeyGen", &CryptoContextImpl<DCRTPoly>::EvalSumColsKeyGen,
//              cc_EvalSumColsKeyGen_docs,
//              py::arg("privateKey"),
//              py::arg("publicKey") = py::none())
//         .def("EvalSum", &CryptoContextImpl<DCRTPoly>::EvalSum,
//              cc_EvalSum_docs,
//              py::arg("ciphertext"),
//              py::arg("batchSize"))
//         .def("EvalSumRows", &CryptoContextImpl<DCRTPoly>::EvalSumRows,
//              cc_EvalSumRows_docs,
//              py::arg("ciphertext"),
//              py::arg("rowSize"),
//              py::arg("evalSumKeyMap"),
//              py::arg("subringDim") = 0)
//         .def("EvalSumCols", &CryptoContextImpl<DCRTPoly>::EvalSumCols,
//              cc_EvalSumCols_docs,
//              py::arg("ciphertext"),
//              py::arg("rowSize"),
//              py::arg("evalSumKeyMap"))
//         .def("EvalInnerProduct", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(ConstCiphertext<DCRTPoly>, ConstCiphertext<DCRTPoly>, usint) const>(&CryptoContextImpl<DCRTPoly>::EvalInnerProduct),
//              cc_EvalInnerProduct_docs,
//              py::arg("ciphertext1"),
//              py::arg("ciphertext2"),
//              py::arg("batchSize"))
//         .def("EvalInnerProduct", static_cast<Ciphertext<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(ConstCiphertext<DCRTPoly>, ConstPlaintext, usint) const>(&CryptoContextImpl<DCRTPoly>::EvalInnerProduct),
//              cc_EvalInnerProductPlaintext_docs,
//              py::arg("ciphertext"),
//              py::arg("plaintext"),
//              py::arg("batchSize"))
//         .def("MultipartyKeyGen", static_cast<KeyPair<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(const PublicKey<DCRTPoly>, bool, bool)>(&CryptoContextImpl<DCRTPoly>::MultipartyKeyGen),
//              cc_MultipartyKeyGen_docs,
//              py::arg("publicKey"),
//              py::arg("makeSparse") = false,
//              py::arg("fresh") = false)
//         .def("MultipartyKeyGen", static_cast<KeyPair<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(const std::vector<PrivateKey<DCRTPoly>> &)>(&CryptoContextImpl<DCRTPoly>::MultipartyKeyGen),
//              cc_MultipartyKeyGen_vector_docs,
//              py::arg("privateKeyVec"))
//         .def("MultipartyDecryptLead", &CryptoContextImpl<DCRTPoly>::MultipartyDecryptLead,
//              cc_MultipartyDecryptLead_docs,
//              py::arg("ciphertextVec"),
//              py::arg("privateKey"))
//         .def("MultipartyDecryptMain", &CryptoContextImpl<DCRTPoly>::MultipartyDecryptMain,
//             cc_MultipartyDecryptMain_docs,
//             py::arg("ciphertextVec"),
//             py::arg("privateKey"))
//         .def("MultipartyDecryptFusion", &MultipartyDecryptFusionWrapper,
//             cc_MultipartyDecryptFusion_docs,
//             py::arg("ciphertextVec"))
//         .def("MultiKeySwitchGen", &CryptoContextImpl<DCRTPoly>::MultiKeySwitchGen,
//              cc_MultiKeySwitchGen_docs,
//              py::arg("originalPrivateKey"),
//              py::arg("newPrivateKey"),
//              py::arg("evalKey"))
//         .def("MultiEvalSumKeyGen", &CryptoContextImpl<DCRTPoly>::MultiEvalSumKeyGen,
//              cc_MultiEvalSumKeyGen_docs,
//              py::arg("privateKey"),
//              py::arg("evalKeyMap"),
//              py::arg("keyId") = "")
//         .def("MultiAddEvalKeys", &CryptoContextImpl<DCRTPoly>::MultiAddEvalKeys,
//              cc_MultiAddEvalKeys_docs,
//              py::arg("evalKey1"),
//              py::arg("evalKey2"),
//              py::arg("keyId") = "")
//         .def("MultiAddEvalMultKeys", &CryptoContextImpl<DCRTPoly>::MultiAddEvalMultKeys,
//              cc_MultiAddEvalMultKeys_docs,
//              py::arg("evalKey1"),
//              py::arg("evalKey2"),
//              py::arg("keyId") = "")
//         .def("IntMPBootAdjustScale",&CryptoContextImpl<DCRTPoly>::IntMPBootAdjustScale,
//              cc_IntMPBootAdjustScale_docs,
//              py::arg("ciphertext"))
//         .def("IntMPBootRandomElementGen", &CryptoContextImpl<DCRTPoly>::IntMPBootRandomElementGen,
//              cc_IntMPBootRandomElementGen_docs,
//              py::arg("publicKey"))
//         .def("IntMPBootDecrypt", &CryptoContextImpl<DCRTPoly>::IntMPBootDecrypt,
//              cc_IntMPBootDecrypt_docs,
//              py::arg("privateKey"),
//              py::arg("ciphertext"),
//              py::arg("a"))
//         .def("IntMPBootAdd", &CryptoContextImpl<DCRTPoly>::IntMPBootAdd,
//              cc_IntMPBootAdd_docs,
//              py::arg("sharePairVec"))
//         .def("IntMPBootEncrypt", &CryptoContextImpl<DCRTPoly>::IntMPBootEncrypt,
//              cc_IntMPBootEncrypt_docs,
//              py::arg("publicKey"),
//              py::arg("sharePair"),
//              py::arg("a"),
//              py::arg("ciphertext"))             
//         .def("MultiMultEvalKey", &CryptoContextImpl<DCRTPoly>::MultiMultEvalKey,
//              cc_MultiMultEvalKey_docs,
//              py::arg("privateKey"),
//              py::arg("evalKey"),
//              py::arg("keyId") = "")
//         .def("MultiAddEvalSumKeys", &CryptoContextImpl<DCRTPoly>::MultiAddEvalSumKeys,
//              cc_MultiAddEvalSumKeys_docs,
//              py::arg("evalKeyMap1"),
//              py::arg("evalKeyMap2"),
//              py::arg("keyId") = "")
//         .def("EvalMerge", &CryptoContextImpl<DCRTPoly>::EvalMerge,
//              cc_EvalMerge_docs,
//              py::arg("ciphertextVec"))
//              // use static_cast: inline EvalKey<Element> ReKeyGen(const PrivateKey<Element> oldPrivateKey, const PublicKey<Element> newPublicKey) const;
//         .def("ReKeyGen", static_cast<EvalKey<DCRTPoly> (CryptoContextImpl<DCRTPoly>::*)(const PrivateKey<DCRTPoly>, const PublicKey<DCRTPoly>) const>(&CryptoContextImpl<DCRTPoly>::ReKeyGen),
//              cc_ReKeyGen_docs,
//              py::arg("oldPrivateKey"),
//              py::arg("newPublicKey"))
//         .def("ReEncrypt", &CryptoContextImpl<DCRTPoly>::ReEncrypt,
//              cc_ReEncrypt_docs,
//              py::arg("ciphertext"),
//              py::arg("evalKey"),
//              py::arg("publicKey") = nullptr)
//         .def("EvalPoly", &CryptoContextImpl<DCRTPoly>::EvalPoly,
//              cc_EvalPoly_docs,
//              py::arg("ciphertext"),
//              py::arg("coefficients"))
//         .def("EvalPolyLinear", &CryptoContextImpl<DCRTPoly>::EvalPolyLinear,
//              cc_EvalPolyLinear_docs,
//              py::arg("ciphertext"),
//              py::arg("coefficients"))
//         .def("EvalPolyPS", &CryptoContextImpl<DCRTPoly>::EvalPolyPS,
//              cc_EvalPolyPS_docs,
//              py::arg("ciphertext"),
//              py::arg("coefficients"))
//         .def("Rescale", &CryptoContextImpl<DCRTPoly>::Rescale,
//              cc_Rescale_docs,
//              py::arg("ciphertext"))
//         .def("RescaleInPlace", &CryptoContextImpl<DCRTPoly>::RescaleInPlace,
//              cc_RescaleInPlace_docs,
//              py::arg("ciphertext"))
//         .def("ModReduce", &CryptoContextImpl<DCRTPoly>::ModReduce,
//              cc_ModReduce_docs,
//              py::arg("ciphertext"))
//         .def("ModReduceInPlace", &CryptoContextImpl<DCRTPoly>::ModReduceInPlace,
//              cc_ModReduceInPlace_docs,
//              py::arg("ciphertext"))
//         .def("EvalBootstrapSetup", &CryptoContextImpl<DCRTPoly>::EvalBootstrapSetup,
//              cc_EvalBootstrapSetup_docs,
//              py::arg("levelBudget") = std::vector<uint32_t>({5, 4}),
//              py::arg("dim1") = std::vector<uint32_t>({0, 0}),
//              py::arg("slots") = 0,
//              py::arg("correctionFactor") = 0,
//              py::arg("precompute")= true)
//         .def("EvalBootstrapKeyGen", &CryptoContextImpl<DCRTPoly>::EvalBootstrapKeyGen,
//              cc_EvalBootstrapKeyGen_docs,
//              py::arg("privateKey"),
//              py::arg("slots"))
//         .def("EvalBootstrap", &CryptoContextImpl<DCRTPoly>::EvalBootstrap,
//              cc_EvalBootstrap_docs,
//              py::arg("ciphertext"),
//              py::arg("numIterations") = 1,
//              py::arg("precision") = 0)
//         .def("EvalCKKStoFHEWSetup", &CryptoContextImpl<DCRTPoly>::EvalCKKStoFHEWSetup,
//             cc_EvalCKKStoFHEWSetup_docs,
//             py::arg("schswchparams"))
//         .def("EvalCKKStoFHEWKeyGen", &CryptoContextImpl<DCRTPoly>::EvalCKKStoFHEWKeyGen,
//              cc_EvalCKKStoFHEWKeyGen_docs,
//              py::arg("keyPair"),
//              py::arg("lwesk"))
//         .def("EvalCKKStoFHEWPrecompute", &CryptoContextImpl<DCRTPoly>::EvalCKKStoFHEWPrecompute,
//              cc_EvalCKKStoFHEWPrecompute_docs,
//              py::arg("scale") = 1.0)
//         .def("EvalCKKStoFHEW", &CryptoContextImpl<DCRTPoly>::EvalCKKStoFHEW,
//              cc_EvalCKKStoFHEW_docs,
//              py::arg("ciphertext"),
//              py::arg("numCtxts") = 0)
//         .def("EvalFHEWtoCKKSSetup", &CryptoContextImpl<DCRTPoly>::EvalFHEWtoCKKSSetup,
//              cc_EvalFHEWtoCKKSSetup_docs,
//              py::arg("ccLWE"),
//              py::arg("numSlotsCKKS") = 0,
//              py::arg("logQ") = 25)
//         .def("EvalFHEWtoCKKSKeyGen", &CryptoContextImpl<DCRTPoly>::EvalFHEWtoCKKSKeyGen,
//              cc_EvalFHEWtoCKKSKeyGen_docs,
//              py::arg("keyPair"),
//              py::arg("lwesk"),
//              py::arg("numSlots") = 0,
//              py::arg("numCtxts") = 0,
//              py::arg("dim1") = 0,
//              py::arg("L") = 0)
//         .def("EvalFHEWtoCKKS", &CryptoContextImpl<DCRTPoly>::EvalFHEWtoCKKS,
//              cc_EvalFHEWtoCKKS_docs,
//              py::arg("LWECiphertexts"),
//              py::arg("numCtxts") = 0,
//              py::arg("numSlots") = 0,
//              py::arg("p") = 4,
//              py::arg("pmin") = 0.0,
//              py::arg("pmax") = 2.0,
//              py::arg("dim1") = 0)
//         .def("EvalSchemeSwitchingSetup", &CryptoContextImpl<DCRTPoly>::EvalSchemeSwitchingSetup,
//              cc_EvalSchemeSwitchingSetup_docs,
//              py::arg("schswchparams"))
//         //void EvalSchemeSwitchingKeyGen(const KeyPair<Element> &keyPair, ConstLWEPrivateKey &lwesk, uint32_t numValues = 0, bool oneHot = true, bool alt = false, uint32_t dim1CF = 0, uint32_t dim1FC = 0, uint32_t LCF = 1, uint32_t LFC = 0)
//         .def("EvalSchemeSwitchingKeyGen", &CryptoContextImpl<DCRTPoly>::EvalSchemeSwitchingKeyGen,
//              cc_EvalSchemeSwitchingKeyGen_docs,
//              py::arg("keyPair"),
//              py::arg("lwesk"))
//         .def("EvalCompareSwitchPrecompute", &CryptoContextImpl<DCRTPoly>::EvalCompareSwitchPrecompute,
//              cc_EvalCompareSwitchPrecompute_docs,
//              py::arg("pLWE") = 0,
//              py::arg("scaleSign") = 1.0,
//              py::arg("unit") = false)
//         .def("EvalCompareSchemeSwitching", &CryptoContextImpl<DCRTPoly>::EvalCompareSchemeSwitching,
//              cc_EvalCompareSchemeSwitching_docs,
//              py::arg("ciphertext1"),
//              py::arg("ciphertext2"),
//              py::arg("numCtxts") = 0,
//              py::arg("numSlots") = 0,
//              py::arg("pLWE") = 0,
//              py::arg("scaleSign") = 1.0,
//              py::arg("unit") = false)
//         .def("EvalMinSchemeSwitching", &CryptoContextImpl<DCRTPoly>::EvalMinSchemeSwitching,
//              cc_EvalMinSchemeSwitching_docs,
//              py::arg("ciphertext"),
//              py::arg("publicKey"),
//              py::arg("numValues") = 0,
//              py::arg("numSlots") = 0,
//              py::arg("pLWE") = 0,
//              py::arg("scaleSign") = 1.0)
//         .def("EvalMinSchemeSwitchingAlt", &CryptoContextImpl<DCRTPoly>::EvalMinSchemeSwitchingAlt,
//              cc_EvalMinSchemeSwitchingAlt_docs,
//              py::arg("ciphertext"),
//              py::arg("publicKey"),
//              py::arg("numValues") = 0,
//              py::arg("numSlots") = 0,
//              py::arg("pLWE") = 0,
//              py::arg("scaleSign") = 1.0)
//         .def("EvalMaxSchemeSwitching", &CryptoContextImpl<DCRTPoly>::EvalMaxSchemeSwitching,
//              cc_EvalMaxSchemeSwitching_docs,
//              py::arg("ciphertext"),
//              py::arg("publicKey"),
//              py::arg("numValues") = 0,
//              py::arg("numSlots") = 0,
//              py::arg("pLWE") = 0,
//              py::arg("scaleSign") = 1.0)
//         .def("EvalMaxSchemeSwitchingAlt", &CryptoContextImpl<DCRTPoly>::EvalMaxSchemeSwitchingAlt,
//              cc_EvalMaxSchemeSwitchingAlt_docs,
//              py::arg("ciphertext"),
//              py::arg("publicKey"),
//              py::arg("numValues") = 0,
//              py::arg("numSlots") = 0,
//              py::arg("pLWE") = 0,
//              py::arg("scaleSign") = 1.0)
//         //TODO (Oliveira, R.): Solve pointer handling bug when returning EvalKeyMap objects for the next functions
//         .def("EvalAutomorphismKeyGen", &EvalAutomorphismKeyGenWrapper, 
//             cc_EvalAutomorphismKeyGen_docs,
//             py::arg("privateKey"),
//             py::arg("indexList"),
//             py::return_value_policy::reference_internal)
//         .def("FindAutomorphismIndex", &CryptoContextImpl<DCRTPoly>::FindAutomorphismIndex,
//             cc_FindAutomorphismIndex_docs,
//             py::arg("idx"))
//         .def("FindAutomorphismIndices", &CryptoContextImpl<DCRTPoly>::FindAutomorphismIndices,
//             cc_FindAutomorphismIndices_docs,
//             py::arg("idxList"))
//         .def_static(
//             "ClearEvalMultKeys", []()
//             { CryptoContextImpl<DCRTPoly>::ClearEvalMultKeys(); },
//             cc_ClearEvalMultKeys_docs)
//         .def_static(
//             "InsertEvalSumKey", &CryptoContextImpl<DCRTPoly>::InsertEvalSumKey,
//             cc_InsertEvalSumKey_docs,
//             py::arg("evalKeyMap"),
//             py::arg("keyTag") = "")
//         .def_static(
//             "InsertEvalMultKey", &CryptoContextImpl<DCRTPoly>::InsertEvalMultKey,
//             cc_InsertEvalMultKey_docs,
//             py::arg("evalKeyVec"))
//         .def_static(
//             "ClearEvalAutomorphismKeys", []()
//             { CryptoContextImpl<DCRTPoly>::ClearEvalAutomorphismKeys(); },
//             cc_ClearEvalAutomorphismKeys_docs)
//         .def("GetEvalSumKeyMap", &GetEvalSumKeyMapWrapper,
//             cc_GetEvalSumKeyMap_docs,
//             py::return_value_policy::reference)
//         .def("GetBinCCForSchemeSwitch", &CryptoContextImpl<DCRTPoly>::GetBinCCForSchemeSwitch,
//         		py::return_value_policy::reference_internal)
//         .def_static(
//             "SerializeEvalMultKey", [](const std::string &filename, const SerType::SERBINARY &sertype, std::string id = "")
//             {
//                 std::ofstream outfile(filename,std::ios::out | std::ios::binary);
//                 bool res;
//                 res = CryptoContextImpl<DCRTPoly>::SerializeEvalMultKey<SerType::SERBINARY>(outfile, sertype, id);
//                 outfile.close();
//                 return res; },
//             cc_SerializeEvalMultKey_docs,
//             py::arg("filename"), py::arg("sertype"), py::arg("id") = "")
//         .def_static( // SerializeEvalMultKey - JSON
//             "SerializeEvalMultKey", [](const std::string &filename, const SerType::SERJSON &sertype, std::string id = "")
//             {
//                 std::ofstream outfile(filename,std::ios::out | std::ios::binary);
//                 bool res;
//                 res = CryptoContextImpl<DCRTPoly>::SerializeEvalMultKey<SerType::SERJSON>(outfile, sertype, id);
//                 outfile.close();
//                 return res; },
//             cc_SerializeEvalMultKey_docs,
//             py::arg("filename"), py::arg("sertype"), py::arg("id") = "")
//         .def_static( // SerializeEvalAutomorphismKey - Binary
//             "SerializeEvalAutomorphismKey", [](const std::string &filename, const SerType::SERBINARY &sertype, std::string id = "")
//             {
//                 std::ofstream outfile(filename,std::ios::out | std::ios::binary);
//                 bool res;
//                 res = CryptoContextImpl<DCRTPoly>::SerializeEvalAutomorphismKey<SerType::SERBINARY>(outfile, sertype, id);
//                 outfile.close();
//                 return res; },
//             cc_SerializeEvalAutomorphismKey_docs,
//             py::arg("filename"), py::arg("sertype"), py::arg("id") = "")
//         .def_static( // SerializeEvalAutomorphismKey - JSON
//             "SerializeEvalAutomorphismKey", [](const std::string &filename, const SerType::SERJSON &sertype, std::string id = "")
//             {
//                 std::ofstream outfile(filename,std::ios::out | std::ios::binary);
//                 bool res;
//                 res = CryptoContextImpl<DCRTPoly>::SerializeEvalAutomorphismKey<SerType::SERJSON>(outfile, sertype, id);
//                 outfile.close();
//                 return res; },
//             cc_SerializeEvalAutomorphismKey_docs,
//             py::arg("filename"), py::arg("sertype"), py::arg("id") = "")
//         .def_static("DeserializeEvalMultKey", // DeserializeEvalMultKey - Binary
//         [](const std::string &filename, const SerType::SERBINARY &sertype)
//                     {
//                         std::ifstream emkeys(filename, std::ios::in | std::ios::binary);
//                          if (!emkeys.is_open()) {
//                             std::cerr << "I cannot read serialization from " << filename << std::endl;
//                          }
//                         bool res;
//                         res = CryptoContextImpl<DCRTPoly>::DeserializeEvalMultKey<SerType::SERBINARY>(emkeys, sertype);
//                         return res; 
                        
//                         },
//                         cc_DeserializeEvalMultKey_docs,
//                         py::arg("filename"), py::arg("sertype"))
//         .def_static("DeserializeEvalMultKey", // DeserializeEvalMultKey - JSON
//         [](const std::string &filename, const SerType::SERJSON &sertype)
//                     {
//                         std::ifstream emkeys(filename, std::ios::in | std::ios::binary);
//                          if (!emkeys.is_open()) {
//                             std::cerr << "I cannot read serialization from " << filename << std::endl;
//                          }
//                         bool res;
//                         res = CryptoContextImpl<DCRTPoly>::DeserializeEvalMultKey<SerType::SERJSON>(emkeys, sertype);
//                         return res; },
//                         cc_DeserializeEvalMultKey_docs,
//                         py::arg("filename"), py::arg("sertype"))
//         .def_static("DeserializeEvalAutomorphismKey", // DeserializeEvalAutomorphismKey - Binary
//         [](const std::string &filename, const SerType::SERBINARY &sertype)
//                     {
//                         std::ifstream erkeys(filename, std::ios::in | std::ios::binary);
//                          if (!erkeys.is_open()) {
//                             std::cerr << "I cannot read serialization from " << filename << std::endl;
//                          }
//                         bool res;
//                         res = CryptoContextImpl<DCRTPoly>::DeserializeEvalAutomorphismKey<SerType::SERBINARY>(erkeys, sertype);
//                         return res; },
//                         cc_DeserializeEvalAutomorphismKey_docs,
//                         py::arg("filename"), py::arg("sertype"))
//         .def_static("DeserializeEvalAutomorphismKey", // DeserializeEvalAutomorphismKey - JSON
//         [](const std::string &filename, const SerType::SERJSON &sertype)
//                     {
//                         std::ifstream erkeys(filename, std::ios::in | std::ios::binary);
//                          if (!erkeys.is_open()) {
//                             std::cerr << "I cannot read serialization from " << filename << std::endl;
//                          }
//                         bool res;
//                         res = CryptoContextImpl<DCRTPoly>::DeserializeEvalAutomorphismKey<SerType::SERJSON>(erkeys, sertype);
//                         return res; },
//                         cc_DeserializeEvalAutomorphismKey_docs,
//                         py::arg("filename"), py::arg("sertype"));

//     // Generator Functions
//     m.def("GenCryptoContext", &GenCryptoContext<CryptoContextBFVRNS>,
//         py::arg("params"));
//     m.def("GenCryptoContext", &GenCryptoContext<CryptoContextBGVRNS>,
//         py::arg("params"));
//     m.def("GenCryptoContext", &GenCryptoContext<CryptoContextCKKSRNS>,
//         py::arg("params"));
//     m.def("ReleaseAllContexts", &CryptoContextFactory<DCRTPoly>::ReleaseAllContexts);
//     m.def("GetAllContexts", &CryptoContextFactory<DCRTPoly>::GetAllContexts);
// }

// int get_native_int(){
//     #if NATIVEINT == 128 && !defined(__EMSCRIPTEN__)
//         return 128;
//     #else
//         return 64;    
//     #endif
// }

// void bind_enums_and_constants(py::module &m)
// {
//     /* ---- PKE enums ---- */ 
//     // Plaintext enums
//     py::enum_<Format>(m, "Format")
//         .value("EVALUATION", Format::EVALUATION)
//         .value("COEFFICIENT", Format::COEFFICIENT);
//     m.attr("EVALUATION") = py::cast(Format::EVALUATION);
//     m.attr("COEFFICIENT") = py::cast(Format::COEFFICIENT);
//     // Serialization Types
//     py::class_<SerType::SERJSON>(m, "SERJSON");
//     py::class_<SerType::SERBINARY>(m, "SERBINARY");
//     m.attr("JSON") = py::cast(SerType::JSON);
//     m.attr("BINARY") = py::cast(SerType::BINARY);

//     /* ---- CORE enums ---- */     
//     //Parameters Type
//     /*TODO (Oliveira): If we expose Poly's and ParmType, this block will go somewhere else */
//     using ParmType = typename DCRTPoly::Params;
//     py::class_<ParmType, std::shared_ptr<ParmType>>(m, "ParmType");

//     //NATIVEINT function
//     m.def("get_native_int", &get_native_int);
  
    
// }

// void bind_keys(py::module &m)
// {
//     py::class_<PublicKeyImpl<DCRTPoly>, std::shared_ptr<PublicKeyImpl<DCRTPoly>>>(m, "PublicKey")
//         .def(py::init<>())
//         .def("GetKeyTag", &PublicKeyImpl<DCRTPoly>::GetKeyTag)
//         .def("SetKeyTag", &PublicKeyImpl<DCRTPoly>::SetKeyTag);
//     py::class_<PrivateKeyImpl<DCRTPoly>, std::shared_ptr<PrivateKeyImpl<DCRTPoly>>>(m, "PrivateKey")
//         .def(py::init<>())
//         .def("GetKeyTag", &PrivateKeyImpl<DCRTPoly>::GetKeyTag)
//         .def("SetKeyTag", &PrivateKeyImpl<DCRTPoly>::SetKeyTag);
//     py::class_<KeyPair<DCRTPoly>>(m, "KeyPair")
//         .def_readwrite("publicKey", &KeyPair<DCRTPoly>::publicKey)
//         .def_readwrite("secretKey", &KeyPair<DCRTPoly>::secretKey)
//         .def("good", &KeyPair<DCRTPoly>::good,kp_good_docs);
//     py::class_<EvalKeyImpl<DCRTPoly>, std::shared_ptr<EvalKeyImpl<DCRTPoly>>>(m, "EvalKey")
//     .def(py::init<>())
//         .def("GetKeyTag", &EvalKeyImpl<DCRTPoly>::GetKeyTag)
//         .def("SetKeyTag", &EvalKeyImpl<DCRTPoly>::SetKeyTag);
//     py::class_<std::map<usint, EvalKey<DCRTPoly>>, std::shared_ptr<std::map<usint, EvalKey<DCRTPoly>>>>(m, "EvalKeyMap")
//         .def(py::init<>());
// }

// void bind_encodings(py::module &m)
// {
//     py::class_<PlaintextImpl, std::shared_ptr<PlaintextImpl>>(m, "Plaintext")
//         .def("GetScalingFactor", &PlaintextImpl::GetScalingFactor,
//             ptx_GetScalingFactor_docs)
//         .def("SetScalingFactor", &PlaintextImpl::SetScalingFactor,
//             ptx_SetScalingFactor_docs,
//             py::arg("sf"))
//         .def("GetSchemeID", &PlaintextImpl::GetSchemeID,
//             ptx_GetSchemeID_docs)
//         .def("GetLength", &PlaintextImpl::GetLength,
//             ptx_GetLength_docs)
//         .def("GetSchemeID", &PlaintextImpl::GetSchemeID,
//             ptx_GetSchemeID_docs)
//         .def("SetLength", &PlaintextImpl::SetLength,
//             ptx_SetLength_docs,
//             py::arg("newSize"))
//         .def("IsEncoded", &PlaintextImpl::IsEncoded,
//             ptx_IsEncoded_docs)
//         .def("GetLogPrecision", &PlaintextImpl::GetLogPrecision,
//             ptx_GetLogPrecision_docs)
//         .def("Encode", &PlaintextImpl::Encode,
//             ptx_Encode_docs)
//         .def("Decode", &PlaintextImpl::Decode,
//             ptx_Decode_docs)
//         .def("LowBound", &PlaintextImpl::LowBound,
//             ptx_LowBound_docs)
//         .def("HighBound", &PlaintextImpl::HighBound,
//             ptx_HighBound_docs)
//         .def("SetFormat", &PlaintextImpl::SetFormat,
//             ptx_SetFormat_docs,
//             py::arg("fmt"))
//         .def("GetPackedValue", &PlaintextImpl::GetPackedValue)
//         .def("GetCKKSPackedValue", &PlaintextImpl::GetCKKSPackedValue,
//             ptx_GetCKKSPackedValue_docs)
//         .def("GetRealPackedValue", &PlaintextImpl::GetRealPackedValue,
//             ptx_GetRealPackedValue_docs)
//         .def("GetLevel", &PlaintextImpl::GetLevel)
//         .def("SetLevel", &PlaintextImpl::SetLevel)
//         .def("GetNoiseScaleDeg", &PlaintextImpl::GetNoiseScaleDeg)
//         .def("SetNoiseScaleDeg", &PlaintextImpl::SetNoiseScaleDeg)
//         .def("GetSlots", &PlaintextImpl::GetSlots)
//         .def("SetSlots", &PlaintextImpl::SetSlots)
//         .def("GetLogError", &PlaintextImpl::GetLogError)
//         .def("GetLogPrecision", &PlaintextImpl::GetLogPrecision)
//         .def("GetStringValue", &PlaintextImpl::GetStringValue)
//         .def("SetStringValue", &PlaintextImpl::SetStringValue)
//         .def("SetIntVectorValue", &PlaintextImpl::SetIntVectorValue)
//         .def("__repr__", [](const PlaintextImpl &p)
//              {
//         std::stringstream ss;
//         ss << "<Plaintext Object: ";
//         p.PrintValue(ss);
//         ss << ">";
//         return ss.str(); })
//         .def("__str__", [](const PlaintextImpl &p)
//              {
//         std::stringstream ss;
//         p.PrintValue(ss);
//         return ss.str(); });
// }

// void bind_ciphertext(py::module &m)
// {
//     py::class_<CiphertextImpl<DCRTPoly>, std::shared_ptr<CiphertextImpl<DCRTPoly>>>(m, "Ciphertext")
//         .def(py::init<>())
//         .def("__add__", [](const Ciphertext<DCRTPoly> &a, const Ciphertext<DCRTPoly> &b)
//              {return a + b; },py::is_operator(),pybind11::keep_alive<0, 1>())
//        // .def(py::self + py::self);
//     // .def("GetDepth", &CiphertextImpl<DCRTPoly>::GetDepth)
//     // .def("SetDepth", &CiphertextImpl<DCRTPoly>::SetDepth)
//      .def("GetLevel", &CiphertextImpl<DCRTPoly>::GetLevel,
//         ctx_GetLevel_docs)
//      .def("SetLevel", &CiphertextImpl<DCRTPoly>::SetLevel,
//         ctx_SetLevel_docs,
//         py::arg("level"))
//      .def("Clone", &CiphertextImpl<DCRTPoly>::Clone)
//      .def("RemoveElement", &RemoveElementWrapper, cc_RemoveElement_docs)
//     // .def("GetHopLevel", &CiphertextImpl<DCRTPoly>::GetHopLevel)
//     // .def("SetHopLevel", &CiphertextImpl<DCRTPoly>::SetHopLevel)
//     // .def("GetScalingFactor", &CiphertextImpl<DCRTPoly>::GetScalingFactor)
//     // .def("SetScalingFactor", &CiphertextImpl<DCRTPoly>::SetScalingFactor)
//      .def("GetSlots", &CiphertextImpl<DCRTPoly>::GetSlots)
//      .def("SetSlots", &CiphertextImpl<DCRTPoly>::SetSlots);
// }

// void bind_schemes(py::module &m){
//     /*Bind schemes specific functionalities like bootstrapping functions and multiparty*/
//     py::class_<FHECKKSRNS>(m, "FHECKKSRNS")
//         .def(py::init<>())
//         //.def_static("GetBootstrapDepth", &FHECKKSRNS::GetBootstrapDepth)
//         .def_static("GetBootstrapDepth", static_cast<uint32_t (*)(uint32_t, const std::vector<uint32_t>&, SecretKeyDist)>(&FHECKKSRNS::GetBootstrapDepth))
//         .def_static("GetBootstrapDepth", static_cast<uint32_t (*)(const std::vector<uint32_t>&, SecretKeyDist)>(&FHECKKSRNS::GetBootstrapDepth));                               
    
// }

// void bind_sch_swch_params(py::module &m)
// {
//     py::class_<SchSwchParams>(m, "SchSwchParams")
//         .def(py::init<>())
//         .def("GetSecurityLevelCKKS", &SchSwchParams::GetSecurityLevelCKKS)
//         .def("GetSecurityLevelFHEW", &SchSwchParams::GetSecurityLevelFHEW)
//         .def("GetArbitraryFunctionEvaluation", &SchSwchParams::GetArbitraryFunctionEvaluation)
//         .def("GetUseDynamicModeFHEW", &SchSwchParams::GetUseDynamicModeFHEW)
//         .def("GetComputeArgmin", &SchSwchParams::GetComputeArgmin)
//         .def("GetOneHotEncoding", &SchSwchParams::GetOneHotEncoding)
//         .def("GetUseAltArgmin", &SchSwchParams::GetUseAltArgmin)
//         .def("GetNumSlotsCKKS", &SchSwchParams::GetNumSlotsCKKS)
//         .def("GetNumValues", &SchSwchParams::GetNumValues)
//         .def("GetCtxtModSizeFHEWLargePrec", &SchSwchParams::GetCtxtModSizeFHEWLargePrec)
//         .def("GetCtxtModSizeFHEWIntermedSwch", &SchSwchParams::GetCtxtModSizeFHEWIntermedSwch)
//         .def("GetBStepLTrCKKStoFHEW", &SchSwchParams::GetBStepLTrCKKStoFHEW)
//         .def("GetBStepLTrFHEWtoCKKS", &SchSwchParams::GetBStepLTrFHEWtoCKKS)
//         .def("GetLevelLTrCKKStoFHEW", &SchSwchParams::GetLevelLTrCKKStoFHEW)
//         .def("GetLevelLTrFHEWtoCKKS", &SchSwchParams::GetLevelLTrFHEWtoCKKS)
//         .def("GetInitialCKKSModulus", &SchSwchParams::GetInitialCKKSModulus)
//         .def("GetRingDimension", &SchSwchParams::GetRingDimension)
//         .def("GetScalingModSize", &SchSwchParams::GetScalingModSize)
//         .def("GetBatchSize", &SchSwchParams::GetBatchSize)
//         .def("SetSecurityLevelCKKS", &SchSwchParams::SetSecurityLevelCKKS)
//         .def("SetSecurityLevelFHEW", &SchSwchParams::SetSecurityLevelFHEW)
//         .def("SetArbitraryFunctionEvaluation", &SchSwchParams::SetArbitraryFunctionEvaluation)
//         .def("SetUseDynamicModeFHEW", &SchSwchParams::SetUseDynamicModeFHEW)
//         .def("SetComputeArgmin", &SchSwchParams::SetComputeArgmin)
//         .def("SetOneHotEncoding", &SchSwchParams::SetOneHotEncoding)
//         .def("SetUseAltArgmin", &SchSwchParams::SetUseAltArgmin)
//         .def("SetNumSlotsCKKS", &SchSwchParams::SetNumSlotsCKKS)
//         .def("SetNumValues", &SchSwchParams::SetNumValues)
//         .def("SetCtxtModSizeFHEWLargePrec", &SchSwchParams::SetCtxtModSizeFHEWLargePrec)
//         .def("SetCtxtModSizeFHEWIntermedSwch", &SchSwchParams::SetCtxtModSizeFHEWIntermedSwch)
//         .def("SetBStepLTrCKKStoFHEW", &SchSwchParams::SetBStepLTrCKKStoFHEW)
//         .def("SetBStepLTrFHEWtoCKKS", &SchSwchParams::SetBStepLTrFHEWtoCKKS)
//         .def("SetLevelLTrCKKStoFHEW", &SchSwchParams::SetLevelLTrCKKStoFHEW)
//         .def("SetLevelLTrFHEWtoCKKS", &SchSwchParams::SetLevelLTrFHEWtoCKKS)
//         .def("SetInitialCKKSModulus", &SchSwchParams::SetInitialCKKSModulus)
//         .def("SetRingDimension", &SchSwchParams::SetRingDimension)
//         .def("SetScalingModSize", &SchSwchParams::SetScalingModSize)
//         .def("SetBatchSize", &SchSwchParams::SetBatchSize)
//         .def("__str__",[](const SchSwchParams &params) {
//             std::stringstream stream;
//             stream << params;
//             return stream.str();
//         });
// }
