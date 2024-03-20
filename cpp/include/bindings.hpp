// BSD 2-Clause License

// Copyright (c) 2023, OpenFHE

// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.

// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef OPENFHE_BINDINGS_H
#define OPENFHE_BINDINGS_H

#include <cstdint>

typedef std::uint32_t usint;
typedef std::uint64_t FFIPlaintextModulus;

// enums from constants.h

enum FFIMultipartyMode {
    INVALID_MULTIPARTY_MODE = 0,
    FIXED_NOISE_MULTIPARTY,
    NOISE_FLOODING_MULTIPARTY,
};

enum FFIProxyReEncryptionMode {
    NOT_SET = 0,
    INDCPA,
    FIXED_NOISE_HRA,
    NOISE_FLOODING_HRA,
    DIVIDE_AND_ROUND_HRA,
};

enum FFIExecutionMode {
    EXEC_EVALUATION = 0,
    EXEC_NOISE_ESTIMATION,
};

enum FFIDecryptionNoiseMode {
    FIXED_NOISE_DECRYPT = 0,
    NOISE_FLOODING_DECRYPT,
};

enum FFIKeySwitchTechnique {
    INVALID_KS_TECH = 0,
    BV,
    HYBRID,
};

enum FFIScalingTechnique {
    FIXEDMANUAL = 0,
    FIXEDAUTO,
    FLEXIBLEAUTO,
    FLEXIBLEAUTOEXT,
    NORESCALE,
    INVALID_RS_TECHNIQUE,  // TODO (dsuponit): make this the first value
};

enum FFIEncryptionTechnique {
    STANDARD = 0,
    EXTENDED,
};

enum FFIMultiplicationTechnique {
    BEHZ = 0,
    HPS,
    HPSPOVERQ,
    HPSPOVERQLEVELED,
};

enum FFICOMPRESSION_LEVEL {
    // we don't support 0 or 1 compression levels
    // do not change values here

    COMPACT = 2,  // more efficient with stronger security assumption
    SLACK   = 3   // less efficient with weaker security assumption
};

enum FFIPKESchemeFeature {
    PKE          = 0x01,
    KEYSWITCH    = 0x02,
    PRE          = 0x04,
    LEVELEDSHE   = 0x08,
    ADVANCEDSHE  = 0x10,
    MULTIPARTY   = 0x20,
    FHE          = 0x40,
    SCHEMESWITCH = 0x80,
};

// enums from stdlatticeparms.h

enum FFISecurityLevel {
    HEStd_128_classic,
    HEStd_192_classic,
    HEStd_256_classic,
    HEStd_128_quantum,
    HEStd_192_quantum,
    HEStd_256_quantum,
    HEStd_NotSet,
};

// enums from constants-lattice.h

enum FFISecretKeyDist {
    GAUSSIAN        = 0,
    UNIFORM_TERNARY = 1,  // Default value, all schemes support this key distribution
    SPARSE_TERNARY  = 2,
    // BINARY = 3, // Future implementation
};

// enums from scheme-id.h

enum FFISCHEME {
    INVALID_SCHEME = 0,
    CKKSRNS_SCHEME,
    BFVRNS_SCHEME,
    BGVRNS_SCHEME,
};

enum CryptoContextType {
    BFVRNS,
    BGVRNS,
    // Add other types as needed
};

// PublicKeyImpl FFI

class FFIPublicKeyImpl {
protected:
    void* pubkey_ptr;
public:
    FFIPublicKeyImpl();

    void SetKeyTag(const std::string& tag);

    const std::string GetKeyTag() const;
};

using FFIPublicKey = std::shared_ptr<FFIPublicKeyImpl>;

// PrivateKeyImpl FFI

class FFIPrivateKeyImpl {
protected:
    void* privkey_ptr;
public:
    FFIPrivateKeyImpl();

    void SetKeyTag(const std::string& tag);

    const std::string GetKeyTag() const;
};

using FFIPrivateKey = std::shared_ptr<FFIPrivateKeyImpl>;

// Params FFI
class FFIParams{
protected:
    void* params_ptr;
public:
    FFIParams();

    FFIParams(FFISCHEME scheme);

    virtual FFIPlaintextModulus GetPlaintextModulus() const;

    virtual FFISCHEME GetScheme() const;

    usint GetDigitSize() const;

    float GetStandardDeviation() const;

    FFISecretKeyDist GetSecretKeyDist() const;

    usint GetMaxRelinSkDeg() const;

    FFIProxyReEncryptionMode GetPREMode() const;

    FFIMultipartyMode GetMultipartyMode() const;

    FFIExecutionMode GetExecutionMode() const;

    FFIDecryptionNoiseMode GetDecryptionNoiseMode() const;

    double GetNoiseEstimate() const;

    double GetDesiredPrecision() const;

    double GetStatisticalSecurity() const;

    double GetNumAdversarialQueries() const;

    usint GetThresholdNumOfParties() const;

    FFIKeySwitchTechnique GetKeySwitchTechnique() const;

    FFIScalingTechnique GetScalingTechnique() const;

    usint GetBatchSize() const;

    usint GetFirstModSize() const;

    uint32_t GetNumLargeDigits() const;

    usint GetMultiplicativeDepth() const;

    usint GetScalingModSize() const;

    FFISecurityLevel GetSecurityLevel() const;

    usint GetRingDim() const;

    usint GetEvalAddCount() const;

    usint GetKeySwitchCount() const;

    FFIEncryptionTechnique GetEncryptionTechnique() const;

    FFIMultiplicationTechnique GetMultiplicationTechnique() const;

    usint GetMultiHopModSize() const;

    FFICOMPRESSION_LEVEL GetInteractiveBootCompressionLevel() const;

    void SetPlaintextModulus(FFIPlaintextModulus ptModulus);

    void SetDigitSize(usint digitSize);

    void SetStandardDeviation(float standardDeviation);

    void SetSecretKeyDist(FFISecretKeyDist secretKeyDist);

    void SetMaxRelinSkDeg(usint maxRelinSkDeg);

    void SetPREMode(FFIProxyReEncryptionMode preMode);

    void SetMultipartyMode(FFIMultipartyMode multipartyMode);

    void SetExecutionMode(FFIExecutionMode executionMode);

    void SetDecryptionNoiseMode(FFIDecryptionNoiseMode decryptionNoiseMode);

    void SetNoiseEstimate(double noiseEstimate);

    void SetDesiredPrecision(double desiredPrecision);

    void SetStatisticalSecurity(uint32_t statisticalSecurity);

    void SetNumAdversarialQueries(uint32_t numAdversarialQueries);

    void SetThresholdNumOfParties(uint32_t thresholdNumOfParties);

    void SetKeySwitchTechnique(FFIKeySwitchTechnique keySwitchTechnique);

    void SetScalingTechnique(FFIScalingTechnique scalingTechnique);

    void SetBatchSize(usint batchSize);

    void SetFirstModSize(usint firstModSize);

    void SetNumLargeDigits(uint32_t numLargeDigits);

    void SetMultiplicativeDepth(usint multiplicativeDepth);

    void SetScalingModSize(usint scalingModSize);

    void SetSecurityLevel(FFISecurityLevel securityLevel);

    void SetRingDim(usint ringDim);

    void SetEvalAddCount(usint evalAddCount);

    void SetKeySwitchCount(usint keySwitchCount);

    void SetEncryptionTechnique(FFIEncryptionTechnique encryptionTechnique);

    void SetMultiplicationTechnique(FFIMultiplicationTechnique multiplicationTechnique);

    void SetMultiHopModSize(usint multiHopModSize);

    void SetInteractiveBootCompressionLevel(FFICOMPRESSION_LEVEL interactiveBootCompressionLevel);

//     std::stream str();  
};

class CryptoContextBFVRNSCCParams : public FFIParams {
public:
    // CryptoContextBFVRNSCCParams();
    CryptoContextBFVRNSCCParams():FFIParams(BFVRNS_SCHEME){};
};

class CryptoContextBGVRNSCCParams : public FFIParams {
public:
    // CryptoContextBGVRNSCCParams();
    CryptoContextBGVRNSCCParams():FFIParams(BGVRNS_SCHEME){};
};

// CryptoContext FFI

class FFICryptoContextImpl {
protected:
    void* cc_ptr;
public:
    FFICryptoContextImpl();

    std::size_t GetKeyGenLevel() const;

    void SetKeyGenLevel(std::size_t level);

    usint GetRingDimension() const;

    FFIPlaintextModulus GetPlaintextModulus() const;

    double GetModulus() const;

    const uint64_t GetModulusCKKS() const;

    double GetScalingFactorReal(uint32_t level) const;

    FFIScalingTechnique GetScalingTechnique() const;

    usint GetDigitSize() const;

    usint GetCyclotomicOrder() const;

    void Enable(FFIPKESchemeFeature feature);

//     KeyPair<Element> KeyGen();

//     void EvalMultKeyGen(const FFIPrivateKey key);

//     void EvalMultKeysGen(const FFIPrivateKey key);

//     void EvalRotateKeyGen(const FFIPrivateKey privateKey, const std::vector<int32_t>& indexList,
//                           const FFIPublicKey publicKey = nullptr);

//     FFIPlaintext MakeStringPlaintext(const std::string& str) const;

//     FFIPlaintext MakePackedPlaintext(const std::vector<int64_t>& value, std::size_t noiseScaleDeg = 1,
//                                   uint32_t level = 0) const;

//     FFIPlaintext MakeCoefPackedPlaintext(const std::vector<int64_t>& value, std::size_t noiseScaleDeg = 1,
//                                       uint32_t level = 0) const;

//     Plaintext MakeCKKSPackedPlaintext(const std::vector<std::complex<double>>& value, std::size_t scaleDeg = 1,
//                                       uint32_t level = 0, const std::shared_ptr<ParmType> params = nullptr,
//                                       usint slots = 0) const;

//     Plaintext MakeCKKSPackedPlaintext(const std::vector<double>& value, std::size_t scaleDeg = 1, uint32_t level = 0,
//                                       const std::shared_ptr<ParmType> params = nullptr, usint slots = 0) const;

//     Ciphertext<Element> EvalRotate(ConstCiphertext<Element> ciphertext, int32_t index) const;

// // const?
//     Ciphertext<DCRTPoly> EvalFastRotationPrecompute(ConstCiphertext<DCRTPoly> ciphertext);
// // const?
//     Ciphertext<DCRTPoly> EvalFastRotation(ConstCiphertext<DCRTPoly> ciphertext, const usint index, const usint m,ConstCiphertext<DCRTPoly> digits);
// // const?
//     Ciphertext<DCRTPoly> EvalFastRotationExt(ConstCiphertext<DCRTPoly> ciphertext, const usint index, ConstCiphertext<DCRTPoly> digits, bool addFirst);

//     void EvalAtIndexKeyGen(const PrivateKey<Element> privateKey, const std::vector<int32_t>& indexList,
//                            const PublicKey<Element> publicKey = nullptr);

//     Ciphertext<Element> EvalAtIndex(ConstCiphertext<Element> ciphertext, int32_t index) const;

//     Ciphertext<Element> Encrypt(const PublicKey<Element> publicKey, Plaintext plaintext) const;

//     DecryptResult Decrypt(ConstCiphertext<Element> ciphertext, const PrivateKey<Element> privateKey,
//                           Plaintext* plaintext);

//     inline DecryptResult Decrypt(const PrivateKey<Element> privateKey, ConstCiphertext<Element> ciphertext,
//                                  Plaintext* plaintext);

//     EvalKey<Element> KeySwitchGen(const PrivateKey<Element> oldPrivateKey,
//                                   const PrivateKey<Element> newPrivateKey) const;
                                  
//     Ciphertext<Element> EvalAdd(ConstCiphertext<Element> ciphertext, double constant) const;

//     Ciphertext<Element> EvalAdd(ConstCiphertext<Element> ciphertext1, ConstCiphertext<Element> ciphertext2) const;

//     Ciphertext<Element> EvalAdd(ConstCiphertext<Element> ciphertext, ConstPlaintext plaintext) const;

//     void EvalAddInPlace(Ciphertext<Element>& ciphertext, ConstPlaintext plaintext) const;

//     void EvalAddInPlace(ConstPlaintext plaintext, Ciphertext<Element>& ciphertext) const;

//     void EvalAddInPlace(Ciphertext<Element>& ciphertext1, ConstCiphertext<Element> ciphertext2) const;

//     Ciphertext<Element> EvalAddMutable(Ciphertext<Element>& ciphertext1, Ciphertext<Element>& ciphertext2) const;

//     Ciphertext<Element> EvalAddMutable(Ciphertext<Element>& ciphertext, Plaintext plaintext) const;

//     Ciphertext<Element> EvalAddMutable(Plaintext plaintext, Ciphertext<Element>& ciphertext) const;

//     void EvalAddMutableInPlace(Ciphertext<Element>& ciphertext1, Ciphertext<Element>& ciphertext2) const;

//     Ciphertext<Element> EvalSub(ConstCiphertext<Element> ciphertext1, ConstCiphertext<Element> ciphertext2) const;

//     Ciphertext<Element> EvalSub(ConstCiphertext<Element> ciphertext, ConstPlaintext plaintext) const;

//     Ciphertext<Element> EvalSub(ConstPlaintext plaintext, ConstCiphertext<Element> ciphertext) const;

//     Ciphertext<Element> EvalSub(ConstCiphertext<Element> ciphertext, double constant) const;

//     Ciphertext<Element> EvalSub(double constant, ConstCiphertext<Element> ciphertext) const;

//     void EvalSubInPlace(Ciphertext<Element>& ciphertext, double constant) const;

//     void EvalSubInPlace(double constant, Ciphertext<Element>& ciphertext) const;

//     void EvalSubInPlace(Ciphertext<Element>& ciphertext1, ConstCiphertext<Element> ciphertext2) const;

//     Ciphertext<Element> EvalSubMutable(Ciphertext<Element>& ciphertext1, Ciphertext<Element>& ciphertext2) const;

//     Ciphertext<Element> EvalSubMutable(Ciphertext<Element>& ciphertext, Plaintext plaintext) const;

//     Ciphertext<Element> EvalSubMutable(Plaintext plaintext, Ciphertext<Element>& ciphertext) const;

//     void EvalSubMutableInPlace(Ciphertext<Element>& ciphertext1, Ciphertext<Element>& ciphertext2) const;
};


#endif // OPENFHE_BINDINGS_H
