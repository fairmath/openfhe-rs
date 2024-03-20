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

// };

#endif // OPENFHE_BINDINGS_H
