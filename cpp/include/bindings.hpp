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
#include "constants-fwd.h"

// forward declarations
class FFIPublicKeyImpl;
class FFIPrivateKeyImpl;
class FFIKeyPair;
class FFIParams;
class FFICryptoContextImpl;

typedef std::uint32_t usint;
typedef std::uint64_t FFIPlaintextModulus;

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

// KeyPair FFI forwad declaration

class FFIKeyPair;

// PublicKeyImpl FFI

class FFIPublicKeyImpl {
protected:
    void* pubkey_ptr;
public:
    FFIPublicKeyImpl();

    explicit FFIPublicKeyImpl(void* new_pubkey_ptr);

    void SetKeyTag(const char*& tag);

    const char* GetKeyTag() const;

    friend class FFIKeyPair;
    friend class FFICryptoContextImpl;
};

// PrivateKeyImpl FFI

class FFIPrivateKeyImpl {
protected:
    void* privkey_ptr;
public:
    FFIPrivateKeyImpl();

    explicit FFIPrivateKeyImpl(void* new_privkey_ptr);

    void SetKeyTag(const char*& tag);

    const char* GetKeyTag() const;

    friend class FFIKeyPair;
    friend class FFICryptoContextImpl;
};

// KeyPair FFI

class FFIKeyPair {
protected:
    void* keypair_ptr;
public:
    FFIKeyPair();
    
    explicit FFIKeyPair(void* new_keypair_ptr){
        keypair_ptr = new_keypair_ptr;
    }

    explicit FFIKeyPair(const FFIPublicKeyImpl& publicKey, const FFIPrivateKeyImpl& privateKey);
    
    bool is_allocated() const;

    FFIPublicKeyImpl GetPublicKey() const;

    FFIPrivateKeyImpl GetPrivateKey() const;
};

// Plaintext FFI

class FFIPlaintext {
protected:
    void* plaintext_ptr;
public:
    explicit FFIPlaintext(void* new_plaintext_ptr){
        plaintext_ptr = new_plaintext_ptr;
    }

    double GetScalingFactor() const;

    void SetScalingFactor(double sf);

    FFISCHEME GetSchemeID() const;

    std::size_t GetLength() const;

    void SetLength(std::size_t newSize);

    bool IsEncoded() const;

    double GetLogPrecision() const;

    void Encode();

    void Decode();

    std::int64_t LowBound() const;

    std::int64_t HighBound() const;
};

// Ciphertext FFI

class FFICiphertext {
protected:
    void* ciphertext_ptr;
public:
    FFICiphertext();

    explicit FFICiphertext(void* new_ciphertext_ptr){
        ciphertext_ptr = new_ciphertext_ptr;
    }

    std::size_t GetLevel() const;

    void SetLevel(std::size_t level);

   FFICiphertext Clone() const;

//  TODO add RemoveElement method from wrappers

    std::size_t GetSlots() const;

    void SetSlots(std::size_t slots);

    friend class FFICryptoContextImpl;
};

// Params FFI
class FFIParams{
protected:
    void* params_ptr;
public:
    FFIParams();

    FFIParams(FFISCHEME scheme);

    FFIPlaintextModulus GetPlaintextModulus() const;

    FFISCHEME GetScheme() const;

    usint GetDigitSize() const;

    float GetStandardDeviation() const;

    FFISecretKeyDist GetSecretKeyDist() const;

    usint GetMaxRelinSkDeg() const;

    lbcrypto::ProxyReEncryptionMode GetPREMode() const;

    lbcrypto::MultipartyMode GetMultipartyMode() const;

    lbcrypto::ExecutionMode GetExecutionMode() const;

    lbcrypto::DecryptionNoiseMode GetDecryptionNoiseMode() const;

    double GetNoiseEstimate() const;

    double GetDesiredPrecision() const;

    double GetStatisticalSecurity() const;

    double GetNumAdversarialQueries() const;

    usint GetThresholdNumOfParties() const;

    lbcrypto::KeySwitchTechnique GetKeySwitchTechnique() const;

    lbcrypto::ScalingTechnique GetScalingTechnique() const;

    usint GetBatchSize() const;

    usint GetFirstModSize() const;

    uint32_t GetNumLargeDigits() const;

    usint GetMultiplicativeDepth() const;

    usint GetScalingModSize() const;

    FFISecurityLevel GetSecurityLevel() const;

    usint GetRingDim() const;

    usint GetEvalAddCount() const;

    usint GetKeySwitchCount() const;

    lbcrypto::EncryptionTechnique GetEncryptionTechnique() const;

    lbcrypto::MultiplicationTechnique GetMultiplicationTechnique() const;

    usint GetMultiHopModSize() const;

    lbcrypto::COMPRESSION_LEVEL GetInteractiveBootCompressionLevel() const;

    void SetPlaintextModulus(FFIPlaintextModulus ptModulus);

    void SetDigitSize(usint digitSize);

    void SetStandardDeviation(float standardDeviation);

    void SetSecretKeyDist(FFISecretKeyDist secretKeyDist);

    void SetMaxRelinSkDeg(usint maxRelinSkDeg);

    void SetPREMode(lbcrypto::ProxyReEncryptionMode preMode);

    void SetMultipartyMode(lbcrypto::MultipartyMode multipartyMode);

    void SetExecutionMode(lbcrypto::ExecutionMode executionMode);

    void SetDecryptionNoiseMode(lbcrypto::DecryptionNoiseMode decryptionNoiseMode);

    void SetNoiseEstimate(double noiseEstimate);

    void SetDesiredPrecision(double desiredPrecision);

    void SetStatisticalSecurity(uint32_t statisticalSecurity);

    void SetNumAdversarialQueries(uint32_t numAdversarialQueries);

    void SetThresholdNumOfParties(uint32_t thresholdNumOfParties);

    void SetKeySwitchTechnique(lbcrypto::KeySwitchTechnique keySwitchTechnique);

    void SetScalingTechnique(lbcrypto::ScalingTechnique scalingTechnique);

    void SetBatchSize(usint batchSize);

    void SetFirstModSize(usint firstModSize);

    void SetNumLargeDigits(uint32_t numLargeDigits);

    void SetMultiplicativeDepth(usint multiplicativeDepth);

    void SetScalingModSize(usint scalingModSize);

    void SetSecurityLevel(FFISecurityLevel securityLevel);

    void SetRingDim(usint ringDim);

    void SetEvalAddCount(usint evalAddCount);

    void SetKeySwitchCount(usint keySwitchCount);

    void SetEncryptionTechnique(lbcrypto::EncryptionTechnique encryptionTechnique);

    void SetMultiplicationTechnique(lbcrypto::MultiplicationTechnique multiplicationTechnique);

    void SetMultiHopModSize(usint multiHopModSize);

    void SetInteractiveBootCompressionLevel(lbcrypto::COMPRESSION_LEVEL interactiveBootCompressionLevel);

//     std::stream str();  

    friend FFICryptoContextImpl GenCryptoContext(FFIParams params);
};

// class CryptoContextBFVRNSCCParams : public FFIParams {
// public:
//     // CryptoContextBFVRNSCCParams();
//     CryptoContextBFVRNSCCParams():FFIParams(BFVRNS_SCHEME){};
// };

// class CryptoContextBGVRNSCCParams : public FFIParams {
// public:
//     // CryptoContextBGVRNSCCParams();
//     CryptoContextBGVRNSCCParams():FFIParams(BGVRNS_SCHEME){};
// };

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

    lbcrypto::ScalingTechnique GetScalingTechnique() const;

    usint GetDigitSize() const;

    usint GetCyclotomicOrder() const;

    void Enable(lbcrypto::PKESchemeFeature feature);

    FFIKeyPair KeyGen() const;

    void EvalMultKeyGen(const FFIPrivateKeyImpl key);

    void EvalMultKeysGen(const FFIPrivateKeyImpl key);

//     void EvalRotateKeyGen(const FFIPrivateKeyImpl privateKey, const std::vector<int32_t>& indexList,
//      const FFIPublicKey publicKey = nullptr);

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

    FFICiphertext EvalRotate(const FFICiphertext ciphertext, std::int32_t index) const;

// // const?
//     Ciphertext<DCRTPoly> EvalFastRotationPrecompute(ConstCiphertext<DCRTPoly> ciphertext);
// // const?
//     Ciphertext<DCRTPoly> EvalFastRotation(ConstCiphertext<DCRTPoly> ciphertext, const usint index, const usint m,ConstCiphertext<DCRTPoly> digits);
// // const?
//     Ciphertext<DCRTPoly> EvalFastRotationExt(ConstCiphertext<DCRTPoly> ciphertext, const usint index, ConstCiphertext<DCRTPoly> digits, bool addFirst);

//     void EvalAtIndexKeyGen(const PrivateKey<Element> privateKey, const std::vector<int32_t>& indexList,
//                            const PublicKey<Element> publicKey = nullptr);

//     Ciphertext<Element> EvalAtIndex(ConstCiphertext<Element> ciphertext, int32_t index) const;

    // FFICiphertext Encrypt(const FFIPublicKeyImpl publicKey, FFIPlaintext plaintext) const;

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
    friend FFICryptoContextImpl GenCryptoContext(FFIParams params);
};

FFICryptoContextImpl GenCryptoContext(FFIParams params);

#endif // OPENFHE_BINDINGS_H
