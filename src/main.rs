#![allow(non_snake_case)]
#![allow(dead_code)]

use cxx::{CxxVector, SharedPtr, let_cxx_string};
use std::time::Instant;

#[cxx::bridge(namespace = "openfhe_rs_dev")]
mod ffi
{
    #[repr(i32)]
    enum SCHEME
    {
        INVALID_SCHEME = 0,
        CKKSRNS_SCHEME,
        BFVRNS_SCHEME,
        BGVRNS_SCHEME,
    }
    #[repr(i32)]
    enum SecretKeyDist
    {
        GAUSSIAN        = 0,
        UNIFORM_TERNARY = 1,
        SPARSE_TERNARY  = 2,
    }
    #[repr(i32)]
    enum ProxyReEncryptionMode
    {
        NOT_SET = 0,
        INDCPA,
        FIXED_NOISE_HRA,
        NOISE_FLOODING_HRA,
        DIVIDE_AND_ROUND_HRA,
    }
    #[repr(i32)]
    enum MultipartyMode
    {
        INVALID_MULTIPARTY_MODE = 0,
        FIXED_NOISE_MULTIPARTY,
        NOISE_FLOODING_MULTIPARTY,
    }
    #[repr(i32)]
    enum ExecutionMode
    {
        EXEC_EVALUATION = 0,
        EXEC_NOISE_ESTIMATION,
    }
    #[repr(i32)]
    enum DecryptionNoiseMode
    {
        FIXED_NOISE_DECRYPT = 0,
        NOISE_FLOODING_DECRYPT,
    }
    #[repr(i32)]    
    enum KeySwitchTechnique
    {
        INVALID_KS_TECH = 0,
        BV,
        HYBRID,
    }
    #[repr(i32)]
    enum ScalingTechnique
    {
        FIXEDMANUAL = 0,
        FIXEDAUTO,
        FLEXIBLEAUTO,
        FLEXIBLEAUTOEXT,
        NORESCALE,
        INVALID_RS_TECHNIQUE,
    }
    #[repr(i32)]
    enum SecurityLevel
    {
        HEStd_128_classic,
        HEStd_192_classic,
        HEStd_256_classic,
        HEStd_128_quantum,
        HEStd_192_quantum,
        HEStd_256_quantum,
        HEStd_NotSet,
    }
    #[repr(i32)]
    enum EncryptionTechnique
    {
        STANDARD = 0,
        EXTENDED,
    }
    #[repr(i32)]
    enum MultiplicationTechnique
    {
        BEHZ = 0,
        HPS,
        HPSPOVERQ,
        HPSPOVERQLEVELED,
    }
    #[repr(i32)]
    enum COMPRESSION_LEVEL
    {
        COMPACT = 2,
        SLACK   = 3,
    }
    #[repr(i32)]
    enum PKESchemeFeature
    {
        PKE          = 0x01,
        KEYSWITCH    = 0x02,
        PRE          = 0x04,
        LEVELEDSHE   = 0x08,
        ADVANCEDSHE  = 0x10,
        MULTIPARTY   = 0x20,
        FHE          = 0x40,
        SCHEMESWITCH = 0x80,
    }
    #[repr(i32)]
    enum SerialMode
    {
        BINARY = 0,
        JSON = 1,
    }

    unsafe extern "C++"
    {
        include!("openfhe_rs_dev/src/direct.hpp");
        type SCHEME;
        type Params;
        type SecretKeyDist;
        type ProxyReEncryptionMode;
        type MultipartyMode;
        type ExecutionMode;
        type DecryptionNoiseMode;
        type KeySwitchTechnique;
        type ScalingTechnique;
        type SecurityLevel;
        type EncryptionTechnique;
        type MultiplicationTechnique;
        type COMPRESSION_LEVEL;
        type ParamsBFVRNS;
        type ParamsBGVRNS;
        type ParamsCKKSRNS;
        type CryptoContextDCRTPoly;
        type PKESchemeFeature;
        type KeyPairDCRTPoly;
        type PrivateKeyImpl;
        type PublicKeyImpl;
        type PlaintextImpl;
        type Plaintext;
        type CiphertextImpl;
        type CiphertextDCRTPoly;
        type DecryptResult;
        type DCRTPolyParams;
        type SerialMode;
        type PublicKeyDCRTPoly;
    }

    // Params
    unsafe extern "C++"
    {
        fn GetParamsByScheme(scheme: SCHEME) -> UniquePtr<Params>;
        fn GetParamsByVectorOfString(vals: &CxxVector<CxxString>) -> UniquePtr<Params>;

        // getters
        fn GetScheme(self: &Params) -> SCHEME;
        fn GetPlaintextModulus(self: &Params) -> u64; // PlaintextModulus
        fn GetDigitSize(self: &Params) -> u32; // usint
        fn GetStandardDeviation(self: &Params) -> f32;
        fn GetSecretKeyDist(self: &Params) -> SecretKeyDist;
        fn GetMaxRelinSkDeg(self: &Params) -> u32;
        fn GetPREMode(self: &Params) -> ProxyReEncryptionMode;
        fn GetMultipartyMode(self: &Params) -> MultipartyMode;
        fn GetExecutionMode(self: &Params) -> ExecutionMode;
        fn GetDecryptionNoiseMode(self: &Params) -> DecryptionNoiseMode;
        fn GetNoiseEstimate(self: &Params) -> f64;
        fn GetDesiredPrecision(self: &Params) -> f64;
        fn GetStatisticalSecurity(self: &Params) -> f64;
        fn GetNumAdversarialQueries(self: &Params) -> f64;
        fn GetThresholdNumOfParties(self: &Params) -> u32;
        fn GetKeySwitchTechnique(self: &Params) -> KeySwitchTechnique;
        fn GetScalingTechnique(self: &Params) -> ScalingTechnique;
        fn GetBatchSize(self: &Params) -> u32;
        fn GetFirstModSize(self: &Params) -> u32;
        fn GetNumLargeDigits(self: &Params) -> u32;
        fn GetMultiplicativeDepth(self: &Params) -> u32;
        fn GetScalingModSize(self: &Params) -> u32;
        fn GetSecurityLevel(self: &Params) -> SecurityLevel;
        fn GetRingDim(self: &Params) -> u32;
        fn GetEvalAddCount(self: &Params) -> u32;
        fn GetKeySwitchCount(self: &Params) -> u32;
        fn GetEncryptionTechnique(self: &Params) -> EncryptionTechnique;
        fn GetMultiplicationTechnique(self: &Params) -> MultiplicationTechnique;
        fn GetMultiHopModSize(self: &Params) -> u32;
        fn GetInteractiveBootCompressionLevel(self: &Params) -> COMPRESSION_LEVEL;
        // setters
        fn SetPlaintextModulus(self: Pin<&mut Params>, ptModulus0: u64); // PlaintextModulus
        fn SetDigitSize(self: Pin<&mut Params>, digitSize0: u32);
        fn SetStandardDeviation(self: Pin<&mut Params>, standardDeviation0: f32);
        fn SetSecretKeyDist(self: Pin<&mut Params>, secretKeyDist0: SecretKeyDist);
        fn SetMaxRelinSkDeg(self: Pin<&mut Params>, maxRelinSkDeg0: u32);
        fn SetPREMode(self: Pin<&mut Params>, PREMode0: ProxyReEncryptionMode);
        fn SetMultipartyMode(self: Pin<&mut Params>, multipartyMode0: MultipartyMode);
        fn SetExecutionMode(self: Pin<&mut Params>, executionMode0: ExecutionMode);
        fn SetDecryptionNoiseMode(self: Pin<&mut Params>, decryptionNoiseMode0: DecryptionNoiseMode);
        fn SetNoiseEstimate(self: Pin<&mut Params>, noiseEstimate0: f64);
        fn SetDesiredPrecision(self: Pin<&mut Params>, desiredPrecision0: f64);
        fn SetStatisticalSecurity(self: Pin<&mut Params>, statisticalSecurity0: u32);
        fn SetNumAdversarialQueries(self: Pin<&mut Params>, numAdversarialQueries0: u32);
        fn SetThresholdNumOfParties(self: Pin<&mut Params>, thresholdNumOfParties0: u32);
        fn SetKeySwitchTechnique(self: Pin<&mut Params>, ksTech0: KeySwitchTechnique);
        fn SetScalingTechnique(self: Pin<&mut Params>, scalTech0: ScalingTechnique);
        fn SetBatchSize(self: Pin<&mut Params>, batchSize0: u32);
        fn SetFirstModSize(self: Pin<&mut Params>, firstModSize0: u32);
        fn SetNumLargeDigits(self: Pin<&mut Params>, numLargeDigits0: u32);
        fn SetMultiplicativeDepth(self: Pin<&mut Params>, multiplicativeDepth0: u32);
        fn SetScalingModSize(self: Pin<&mut Params>, scalingModSize0: u32);
        fn SetSecurityLevel(self: Pin<&mut Params>, securityLevel0: SecurityLevel);
        fn SetRingDim(self: Pin<&mut Params>, ringDim0: u32);
        fn SetEvalAddCount(self: Pin<&mut Params>, evalAddCount0: u32);
        fn SetKeySwitchCount(self: Pin<&mut Params>, keySwitchCount0: u32);
        fn SetEncryptionTechnique(self: Pin<&mut Params>, encryptionTechnique0: EncryptionTechnique);
        fn SetMultiplicationTechnique(self: Pin<&mut Params>, multiplicationTechnique0: MultiplicationTechnique);
        fn SetMultiHopModSize(self: Pin<&mut Params>, multiHopModSize0: u32);
        fn SetInteractiveBootCompressionLevel(self: Pin<&mut Params>, interactiveBootCompressionLevel0: COMPRESSION_LEVEL);
    }

    // ParamsBFVRNS
    unsafe extern "C++"
    {
        fn GetParamsBFVRNS() -> UniquePtr<ParamsBFVRNS>;
        fn GetParamsBFVRNSbyVectorOfString(vals: &CxxVector<CxxString>) -> UniquePtr<ParamsBFVRNS>;
        // getters
        fn GetScheme(self: &ParamsBFVRNS) -> SCHEME;
        fn GetPlaintextModulus(self: &ParamsBFVRNS) -> u64; // PlaintextModulus
        fn GetDigitSize(self: &ParamsBFVRNS) -> u32; // usint
        fn GetStandardDeviation(self: &ParamsBFVRNS) -> f32;
        fn GetSecretKeyDist(self: &ParamsBFVRNS) -> SecretKeyDist;
        fn GetMaxRelinSkDeg(self: &ParamsBFVRNS) -> u32;
        fn GetPREMode(self: &ParamsBFVRNS) -> ProxyReEncryptionMode;
        fn GetMultipartyMode(self: &ParamsBFVRNS) -> MultipartyMode;
        fn GetExecutionMode(self: &ParamsBFVRNS) -> ExecutionMode;
        fn GetDecryptionNoiseMode(self: &ParamsBFVRNS) -> DecryptionNoiseMode;
        fn GetNoiseEstimate(self: &ParamsBFVRNS) -> f64;
        fn GetDesiredPrecision(self: &ParamsBFVRNS) -> f64;
        fn GetStatisticalSecurity(self: &ParamsBFVRNS) -> f64;
        fn GetNumAdversarialQueries(self: &ParamsBFVRNS) -> f64;
        fn GetThresholdNumOfParties(self: &ParamsBFVRNS) -> u32;
        fn GetKeySwitchTechnique(self: &ParamsBFVRNS) -> KeySwitchTechnique;
        fn GetScalingTechnique(self: &ParamsBFVRNS) -> ScalingTechnique;
        fn GetBatchSize(self: &ParamsBFVRNS) -> u32;
        fn GetFirstModSize(self: &ParamsBFVRNS) -> u32;
        fn GetNumLargeDigits(self: &ParamsBFVRNS) -> u32;
        fn GetMultiplicativeDepth(self: &ParamsBFVRNS) -> u32;
        fn GetScalingModSize(self: &ParamsBFVRNS) -> u32;
        fn GetSecurityLevel(self: &ParamsBFVRNS) -> SecurityLevel;
        fn GetRingDim(self: &ParamsBFVRNS) -> u32;
        fn GetEvalAddCount(self: &ParamsBFVRNS) -> u32;
        fn GetKeySwitchCount(self: &ParamsBFVRNS) -> u32;
        fn GetEncryptionTechnique(self: &ParamsBFVRNS) -> EncryptionTechnique;
        fn GetMultiplicationTechnique(self: &ParamsBFVRNS) -> MultiplicationTechnique;
        fn GetMultiHopModSize(self: &ParamsBFVRNS) -> u32;
        fn GetInteractiveBootCompressionLevel(self: &ParamsBFVRNS) -> COMPRESSION_LEVEL;
        // setters
        fn SetPlaintextModulus(self: Pin<&mut ParamsBFVRNS>, ptModulus0: u64); // PlaintextModulus
        fn SetDigitSize(self: Pin<&mut ParamsBFVRNS>, digitSize0: u32);
        fn SetStandardDeviation(self: Pin<&mut ParamsBFVRNS>, standardDeviation0: f32);
        fn SetSecretKeyDist(self: Pin<&mut ParamsBFVRNS>, secretKeyDist0: SecretKeyDist);
        fn SetMaxRelinSkDeg(self: Pin<&mut ParamsBFVRNS>, maxRelinSkDeg0: u32);
        fn SetPREMode(self: Pin<&mut ParamsBFVRNS>, PREMode0: ProxyReEncryptionMode);
        fn SetMultipartyMode(self: Pin<&mut ParamsBFVRNS>, multipartyMode0: MultipartyMode);
        fn SetExecutionMode(self: Pin<&mut ParamsBFVRNS>, executionMode0: ExecutionMode);
        fn SetDecryptionNoiseMode(self: Pin<&mut ParamsBFVRNS>, decryptionNoiseMode0: DecryptionNoiseMode);
        fn SetNoiseEstimate(self: Pin<&mut ParamsBFVRNS>, noiseEstimate0: f64);
        fn SetDesiredPrecision(self: Pin<&mut ParamsBFVRNS>, desiredPrecision0: f64);
        fn SetStatisticalSecurity(self: Pin<&mut ParamsBFVRNS>, statisticalSecurity0: u32);
        fn SetNumAdversarialQueries(self: Pin<&mut ParamsBFVRNS>, numAdversarialQueries0: u32);
        fn SetThresholdNumOfParties(self: Pin<&mut ParamsBFVRNS>, thresholdNumOfParties0: u32);
        fn SetKeySwitchTechnique(self: Pin<&mut ParamsBFVRNS>, ksTech0: KeySwitchTechnique);
        fn SetScalingTechnique(self: Pin<&mut ParamsBFVRNS>, scalTech0: ScalingTechnique);
        fn SetBatchSize(self: Pin<&mut ParamsBFVRNS>, batchSize0: u32);
        fn SetFirstModSize(self: Pin<&mut ParamsBFVRNS>, firstModSize0: u32);
        fn SetNumLargeDigits(self: Pin<&mut ParamsBFVRNS>, numLargeDigits0: u32);
        fn SetMultiplicativeDepth(self: Pin<&mut ParamsBFVRNS>, multiplicativeDepth0: u32);
        fn SetScalingModSize(self: Pin<&mut ParamsBFVRNS>, scalingModSize0: u32);
        fn SetSecurityLevel(self: Pin<&mut ParamsBFVRNS>, securityLevel0: SecurityLevel);
        fn SetRingDim(self: Pin<&mut ParamsBFVRNS>, ringDim0: u32);
        fn SetEvalAddCount(self: Pin<&mut ParamsBFVRNS>, evalAddCount0: u32);
        fn SetKeySwitchCount(self: Pin<&mut ParamsBFVRNS>, keySwitchCount0: u32);
        fn SetEncryptionTechnique(self: Pin<&mut ParamsBFVRNS>, encryptionTechnique0: EncryptionTechnique);
        fn SetMultiplicationTechnique(self: Pin<&mut ParamsBFVRNS>, multiplicationTechnique0: MultiplicationTechnique);
        fn SetMultiHopModSize(self: Pin<&mut ParamsBFVRNS>, multiHopModSize0: u32);
        fn SetInteractiveBootCompressionLevel(self: Pin<&mut ParamsBFVRNS>, interactiveBootCompressionLevel0: COMPRESSION_LEVEL);
    }

    // ParamsBGVRNS
    unsafe extern "C++"
    {
        fn GetParamsBGVRNS() -> UniquePtr<ParamsBGVRNS>;
        fn GetParamsBGVRNSbyVectorOfString(vals: &CxxVector<CxxString>) -> UniquePtr<ParamsBGVRNS>;
        // getters
        fn GetScheme(self: &ParamsBGVRNS) -> SCHEME;
        fn GetPlaintextModulus(self: &ParamsBGVRNS) -> u64; // PlaintextModulus
        fn GetDigitSize(self: &ParamsBGVRNS) -> u32; // usint
        fn GetStandardDeviation(self: &ParamsBGVRNS) -> f32;
        fn GetSecretKeyDist(self: &ParamsBGVRNS) -> SecretKeyDist;
        fn GetMaxRelinSkDeg(self: &ParamsBGVRNS) -> u32;
        fn GetPREMode(self: &ParamsBGVRNS) -> ProxyReEncryptionMode;
        fn GetMultipartyMode(self: &ParamsBGVRNS) -> MultipartyMode;
        fn GetExecutionMode(self: &ParamsBGVRNS) -> ExecutionMode;
        fn GetDecryptionNoiseMode(self: &ParamsBGVRNS) -> DecryptionNoiseMode;
        fn GetNoiseEstimate(self: &ParamsBGVRNS) -> f64;
        fn GetDesiredPrecision(self: &ParamsBGVRNS) -> f64;
        fn GetStatisticalSecurity(self: &ParamsBGVRNS) -> f64;
        fn GetNumAdversarialQueries(self: &ParamsBGVRNS) -> f64;
        fn GetThresholdNumOfParties(self: &ParamsBGVRNS) -> u32;
        fn GetKeySwitchTechnique(self: &ParamsBGVRNS) -> KeySwitchTechnique;
        fn GetScalingTechnique(self: &ParamsBGVRNS) -> ScalingTechnique;
        fn GetBatchSize(self: &ParamsBGVRNS) -> u32;
        fn GetFirstModSize(self: &ParamsBGVRNS) -> u32;
        fn GetNumLargeDigits(self: &ParamsBGVRNS) -> u32;
        fn GetMultiplicativeDepth(self: &ParamsBGVRNS) -> u32;
        fn GetScalingModSize(self: &ParamsBGVRNS) -> u32;
        fn GetSecurityLevel(self: &ParamsBGVRNS) -> SecurityLevel;
        fn GetRingDim(self: &ParamsBGVRNS) -> u32;
        fn GetEvalAddCount(self: &ParamsBGVRNS) -> u32;
        fn GetKeySwitchCount(self: &ParamsBGVRNS) -> u32;
        fn GetEncryptionTechnique(self: &ParamsBGVRNS) -> EncryptionTechnique;
        fn GetMultiplicationTechnique(self: &ParamsBGVRNS) -> MultiplicationTechnique;
        fn GetMultiHopModSize(self: &ParamsBGVRNS) -> u32;
        fn GetInteractiveBootCompressionLevel(self: &ParamsBGVRNS) -> COMPRESSION_LEVEL;
        // setters
        fn SetPlaintextModulus(self: Pin<&mut ParamsBGVRNS>, ptModulus0: u64); // PlaintextModulus
        fn SetDigitSize(self: Pin<&mut ParamsBGVRNS>, digitSize0: u32);
        fn SetStandardDeviation(self: Pin<&mut ParamsBGVRNS>, standardDeviation0: f32);
        fn SetSecretKeyDist(self: Pin<&mut ParamsBGVRNS>, secretKeyDist0: SecretKeyDist);
        fn SetMaxRelinSkDeg(self: Pin<&mut ParamsBGVRNS>, maxRelinSkDeg0: u32);
        fn SetPREMode(self: Pin<&mut ParamsBGVRNS>, PREMode0: ProxyReEncryptionMode);
        fn SetMultipartyMode(self: Pin<&mut ParamsBGVRNS>, multipartyMode0: MultipartyMode);
        fn SetExecutionMode(self: Pin<&mut ParamsBGVRNS>, executionMode0: ExecutionMode);
        fn SetDecryptionNoiseMode(self: Pin<&mut ParamsBGVRNS>, decryptionNoiseMode0: DecryptionNoiseMode);
        fn SetNoiseEstimate(self: Pin<&mut ParamsBGVRNS>, noiseEstimate0: f64);
        fn SetDesiredPrecision(self: Pin<&mut ParamsBGVRNS>, desiredPrecision0: f64);
        fn SetStatisticalSecurity(self: Pin<&mut ParamsBGVRNS>, statisticalSecurity0: u32);
        fn SetNumAdversarialQueries(self: Pin<&mut ParamsBGVRNS>, numAdversarialQueries0: u32);
        fn SetThresholdNumOfParties(self: Pin<&mut ParamsBGVRNS>, thresholdNumOfParties0: u32);
        fn SetKeySwitchTechnique(self: Pin<&mut ParamsBGVRNS>, ksTech0: KeySwitchTechnique);
        fn SetScalingTechnique(self: Pin<&mut ParamsBGVRNS>, scalTech0: ScalingTechnique);
        fn SetBatchSize(self: Pin<&mut ParamsBGVRNS>, batchSize0: u32);
        fn SetFirstModSize(self: Pin<&mut ParamsBGVRNS>, firstModSize0: u32);
        fn SetNumLargeDigits(self: Pin<&mut ParamsBGVRNS>, numLargeDigits0: u32);
        fn SetMultiplicativeDepth(self: Pin<&mut ParamsBGVRNS>, multiplicativeDepth0: u32);
        fn SetScalingModSize(self: Pin<&mut ParamsBGVRNS>, scalingModSize0: u32);
        fn SetSecurityLevel(self: Pin<&mut ParamsBGVRNS>, securityLevel0: SecurityLevel);
        fn SetRingDim(self: Pin<&mut ParamsBGVRNS>, ringDim0: u32);
        fn SetEvalAddCount(self: Pin<&mut ParamsBGVRNS>, evalAddCount0: u32);
        fn SetKeySwitchCount(self: Pin<&mut ParamsBGVRNS>, keySwitchCount0: u32);
        fn SetEncryptionTechnique(self: Pin<&mut ParamsBGVRNS>, encryptionTechnique0: EncryptionTechnique);
        fn SetMultiplicationTechnique(self: Pin<&mut ParamsBGVRNS>, multiplicationTechnique0: MultiplicationTechnique);
        fn SetMultiHopModSize(self: Pin<&mut ParamsBGVRNS>, multiHopModSize0: u32);
        fn SetInteractiveBootCompressionLevel(self: Pin<&mut ParamsBGVRNS>, interactiveBootCompressionLevel0: COMPRESSION_LEVEL);
    }

    // ParamsCKKSRNS
    unsafe extern "C++"
    {
        fn GetParamsCKKSRNS() -> UniquePtr<ParamsCKKSRNS>;
        fn GetParamsCKKSRNSbyVectorOfString(vals: &CxxVector<CxxString>) -> UniquePtr<ParamsCKKSRNS>;
        // getters
        fn GetScheme(self: &ParamsCKKSRNS) -> SCHEME;
        fn GetPlaintextModulus(self: &ParamsCKKSRNS) -> u64; // PlaintextModulus
        fn GetDigitSize(self: &ParamsCKKSRNS) -> u32; // usint
        fn GetStandardDeviation(self: &ParamsCKKSRNS) -> f32;
        fn GetSecretKeyDist(self: &ParamsCKKSRNS) -> SecretKeyDist;
        fn GetMaxRelinSkDeg(self: &ParamsCKKSRNS) -> u32;
        fn GetPREMode(self: &ParamsCKKSRNS) -> ProxyReEncryptionMode;
        fn GetMultipartyMode(self: &ParamsCKKSRNS) -> MultipartyMode;
        fn GetExecutionMode(self: &ParamsCKKSRNS) -> ExecutionMode;
        fn GetDecryptionNoiseMode(self: &ParamsCKKSRNS) -> DecryptionNoiseMode;
        fn GetNoiseEstimate(self: &ParamsCKKSRNS) -> f64;
        fn GetDesiredPrecision(self: &ParamsCKKSRNS) -> f64;
        fn GetStatisticalSecurity(self: &ParamsCKKSRNS) -> f64;
        fn GetNumAdversarialQueries(self: &ParamsCKKSRNS) -> f64;
        fn GetThresholdNumOfParties(self: &ParamsCKKSRNS) -> u32;
        fn GetKeySwitchTechnique(self: &ParamsCKKSRNS) -> KeySwitchTechnique;
        fn GetScalingTechnique(self: &ParamsCKKSRNS) -> ScalingTechnique;
        fn GetBatchSize(self: &ParamsCKKSRNS) -> u32;
        fn GetFirstModSize(self: &ParamsCKKSRNS) -> u32;
        fn GetNumLargeDigits(self: &ParamsCKKSRNS) -> u32;
        fn GetMultiplicativeDepth(self: &ParamsCKKSRNS) -> u32;
        fn GetScalingModSize(self: &ParamsCKKSRNS) -> u32;
        fn GetSecurityLevel(self: &ParamsCKKSRNS) -> SecurityLevel;
        fn GetRingDim(self: &ParamsCKKSRNS) -> u32;
        fn GetEvalAddCount(self: &ParamsCKKSRNS) -> u32;
        fn GetKeySwitchCount(self: &ParamsCKKSRNS) -> u32;
        fn GetEncryptionTechnique(self: &ParamsCKKSRNS) -> EncryptionTechnique;
        fn GetMultiplicationTechnique(self: &ParamsCKKSRNS) -> MultiplicationTechnique;
        fn GetMultiHopModSize(self: &ParamsCKKSRNS) -> u32;
        fn GetInteractiveBootCompressionLevel(self: &ParamsCKKSRNS) -> COMPRESSION_LEVEL;
        // setters
        fn SetPlaintextModulus(self: Pin<&mut ParamsCKKSRNS>, ptModulus0: u64); // PlaintextModulus
        fn SetDigitSize(self: Pin<&mut ParamsCKKSRNS>, digitSize0: u32);
        fn SetStandardDeviation(self: Pin<&mut ParamsCKKSRNS>, standardDeviation0: f32);
        fn SetSecretKeyDist(self: Pin<&mut ParamsCKKSRNS>, secretKeyDist0: SecretKeyDist);
        fn SetMaxRelinSkDeg(self: Pin<&mut ParamsCKKSRNS>, maxRelinSkDeg0: u32);
        fn SetPREMode(self: Pin<&mut ParamsCKKSRNS>, PREMode0: ProxyReEncryptionMode);
        fn SetMultipartyMode(self: Pin<&mut ParamsCKKSRNS>, multipartyMode0: MultipartyMode);
        fn SetExecutionMode(self: Pin<&mut ParamsCKKSRNS>, executionMode0: ExecutionMode);
        fn SetDecryptionNoiseMode(self: Pin<&mut ParamsCKKSRNS>, decryptionNoiseMode0: DecryptionNoiseMode);
        fn SetNoiseEstimate(self: Pin<&mut ParamsCKKSRNS>, noiseEstimate0: f64);
        fn SetDesiredPrecision(self: Pin<&mut ParamsCKKSRNS>, desiredPrecision0: f64);
        fn SetStatisticalSecurity(self: Pin<&mut ParamsCKKSRNS>, statisticalSecurity0: u32);
        fn SetNumAdversarialQueries(self: Pin<&mut ParamsCKKSRNS>, numAdversarialQueries0: u32);
        fn SetThresholdNumOfParties(self: Pin<&mut ParamsCKKSRNS>, thresholdNumOfParties0: u32);
        fn SetKeySwitchTechnique(self: Pin<&mut ParamsCKKSRNS>, ksTech0: KeySwitchTechnique);
        fn SetScalingTechnique(self: Pin<&mut ParamsCKKSRNS>, scalTech0: ScalingTechnique);
        fn SetBatchSize(self: Pin<&mut ParamsCKKSRNS>, batchSize0: u32);
        fn SetFirstModSize(self: Pin<&mut ParamsCKKSRNS>, firstModSize0: u32);
        fn SetNumLargeDigits(self: Pin<&mut ParamsCKKSRNS>, numLargeDigits0: u32);
        fn SetMultiplicativeDepth(self: Pin<&mut ParamsCKKSRNS>, multiplicativeDepth0: u32);
        fn SetScalingModSize(self: Pin<&mut ParamsCKKSRNS>, scalingModSize0: u32);
        fn SetSecurityLevel(self: Pin<&mut ParamsCKKSRNS>, securityLevel0: SecurityLevel);
        fn SetRingDim(self: Pin<&mut ParamsCKKSRNS>, ringDim0: u32);
        fn SetEvalAddCount(self: Pin<&mut ParamsCKKSRNS>, evalAddCount0: u32);
        fn SetKeySwitchCount(self: Pin<&mut ParamsCKKSRNS>, keySwitchCount0: u32);
        fn SetEncryptionTechnique(self: Pin<&mut ParamsCKKSRNS>, encryptionTechnique0: EncryptionTechnique);
        fn SetMultiplicationTechnique(self: Pin<&mut ParamsCKKSRNS>, multiplicationTechnique0: MultiplicationTechnique);
        fn SetMultiHopModSize(self: Pin<&mut ParamsCKKSRNS>, multiHopModSize0: u32);
        fn SetInteractiveBootCompressionLevel(self: Pin<&mut ParamsCKKSRNS>, interactiveBootCompressionLevel0: COMPRESSION_LEVEL);
    }

    // KeyPairDCRTPoly
    unsafe extern "C++"
    {
        fn GetPrivateKey(self: &KeyPairDCRTPoly) -> SharedPtr<PrivateKeyImpl>;
        fn GetPublicKey(self: &KeyPairDCRTPoly) -> SharedPtr<PublicKeyImpl>;
    }

    // PublicKeyDCRTPoly
    unsafe extern "C++"
    {
        fn GenDefaultConstructedPublicKey() -> UniquePtr<PublicKeyDCRTPoly>;
    }

    // Plaintext
    unsafe extern "C++"
    {
        fn GenEmptyPlainText() -> UniquePtr<Plaintext>;
        fn GetPlainText(self: &Plaintext) -> SharedPtr<PlaintextImpl>;
        fn SetLength(self: &Plaintext, newSize: usize);
        fn GetString(self: &Plaintext) -> String;
        fn GetLogPrecision(self: &Plaintext) -> f64;
    }

    // CiphertextDCRTPoly
    unsafe extern "C++"
    {
        fn GetCipherText(self: &CiphertextDCRTPoly) -> SharedPtr<CiphertextImpl>;
        fn GenDefaultConstructedCiphertext() -> UniquePtr<CiphertextDCRTPoly>;
    }

    // ComplexPair
    struct ComplexPair
    {
        re: f64,
        im: f64,
    }

    // VectorOfComplexNumbers
    unsafe extern "C++"
    {
        type VectorOfComplexNumbers; // TODO: Think about vector of opaque C++ type
        fn GenVectorOfComplexNumbers(vals: &CxxVector<ComplexPair>) -> UniquePtr<VectorOfComplexNumbers>;
    }

    // CryptoContextDCRTPoly
    unsafe extern "C++"
    {
        fn GenEmptyCryptoContext() -> UniquePtr<CryptoContextDCRTPoly>;
        fn GenCryptoContextByParamsBFVRNS(params: &ParamsBFVRNS) -> UniquePtr<CryptoContextDCRTPoly>;
        fn GenCryptoContextByParamsBGVRNS(params: &ParamsBGVRNS) -> UniquePtr<CryptoContextDCRTPoly>;
        fn GenCryptoContextByParamsCKKSRNS(params: &ParamsCKKSRNS) -> UniquePtr<CryptoContextDCRTPoly>;

        fn Enable(self: &CryptoContextDCRTPoly, feature: PKESchemeFeature);
        fn KeyGen(self: &CryptoContextDCRTPoly) -> UniquePtr<KeyPairDCRTPoly>;
        fn EvalMultKeyGen(self: &CryptoContextDCRTPoly, key: SharedPtr<PrivateKeyImpl>);
        fn EvalRotateKeyGen(self: &CryptoContextDCRTPoly, privateKey: SharedPtr<PrivateKeyImpl>, indexList: &CxxVector<i32>, publicKey: SharedPtr<PublicKeyImpl>);
        fn MakePackedPlaintext(self: &CryptoContextDCRTPoly, value: &CxxVector<i64>, noiseScaleDeg: usize, level: u32) -> UniquePtr<Plaintext>; // noiseScaleDeg = 1, level = 0
        fn Encrypt(self: &CryptoContextDCRTPoly, publicKey: SharedPtr<PublicKeyImpl>, plaintext: SharedPtr<PlaintextImpl>) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAdd(self: &CryptoContextDCRTPoly, ciphertext1: SharedPtr<CiphertextImpl>, ciphertext2: SharedPtr<CiphertextImpl>) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSub(self: &CryptoContextDCRTPoly, ciphertext1: SharedPtr<CiphertextImpl>, ciphertext2: SharedPtr<CiphertextImpl>) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMult(self: &CryptoContextDCRTPoly, ciphertext1: SharedPtr<CiphertextImpl>, ciphertext2: SharedPtr<CiphertextImpl>) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultByConst(self: &CryptoContextDCRTPoly, ciphertext: SharedPtr<CiphertextImpl>, constant: f64) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalRotate(self: &CryptoContextDCRTPoly, ciphertext: SharedPtr<CiphertextImpl>, index: i32) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalChebyshevSeries(self: &CryptoContextDCRTPoly, ciphertext: SharedPtr<CiphertextImpl>, coefficients: &CxxVector<f64>, a: f64, b: f64) -> UniquePtr<CiphertextDCRTPoly>;
        fn Decrypt(self: &CryptoContextDCRTPoly, privateKey: SharedPtr<PrivateKeyImpl>, ciphertext: SharedPtr<CiphertextImpl>,
                   plaintext: Pin<&mut Plaintext>) -> UniquePtr<DecryptResult>;
        fn GetRingDimension(self: &CryptoContextDCRTPoly) -> u32;
        fn MakeCKKSPackedPlaintext(self: &CryptoContextDCRTPoly, value: &CxxVector<f64>, scaleDeg: usize, level: u32,
                                   params: SharedPtr<DCRTPolyParams>, slots: u32) -> UniquePtr<Plaintext>; // scaleDeg = 1, level = 0, params = nullptr, slots = 0
        fn MakeCKKSPackedPlaintextByVectorOfComplexNumbers(self: &CryptoContextDCRTPoly, value: &VectorOfComplexNumbers, scaleDeg: usize, level: u32,
                                   params: SharedPtr<DCRTPolyParams>, slots: u32) -> UniquePtr<Plaintext>; // scaleDeg = 1, level = 0, params = nullptr, slots = 0
        fn EvalPoly(self: &CryptoContextDCRTPoly, ciphertext: SharedPtr<CiphertextImpl>, coefficients: &CxxVector<f64>) -> UniquePtr<CiphertextDCRTPoly>;
    }

    // Serialize/Deserialize
    unsafe extern "C++"
    {
        fn SerializeCryptoContextToFile(ccLocation: &CxxString, cryptoContext: &CryptoContextDCRTPoly, serialMode: SerialMode) -> bool;
        fn DeserializeCryptoContextFromFile(ccLocation: &CxxString, cryptoContext: Pin<&mut CryptoContextDCRTPoly>, serialMode: SerialMode) -> bool;
        fn SerializeEvalMultKeyToFile(multKeyLocation: &CxxString, cryptoContext: &CryptoContextDCRTPoly, serialMode: SerialMode) -> bool;
        fn SerializeEvalMultKeyByIdToFile(multKeyLocation: &CxxString, serialMode: SerialMode, id: &CxxString) -> bool;
        fn DeserializeEvalMultKeyFromFile(multKeyLocation: &CxxString, serialMode: SerialMode) -> bool;
        fn SerializeEvalSumKeyToFile(sumKeyLocation: &CxxString, cryptoContext: &CryptoContextDCRTPoly, serialMode: SerialMode) -> bool;
        fn SerializeEvalSumKeyByIdToFile(sumKeyLocation: &CxxString, serialMode: SerialMode, id: &CxxString) -> bool;
        fn DeserializeEvalSumKeyFromFile(sumKeyLocation: &CxxString, serialMode: SerialMode) -> bool;
        fn SerializeEvalAutomorphismKeyToFile(automorphismKeyLocation: &CxxString, cryptoContext: &CryptoContextDCRTPoly, serialMode: SerialMode) -> bool;
        fn SerializeEvalAutomorphismKeyByIdToFile(automorphismKeyLocation: &CxxString, serialMode: SerialMode, id: &CxxString) -> bool;
        fn DeserializeEvalAutomorphismKeyFromFile(automorphismKeyLocation: &CxxString, serialMode: SerialMode) -> bool;
        fn SerializeCiphertextToFile(ciphertextLocation: &CxxString, ciphertext: &CiphertextDCRTPoly, serialMode: SerialMode) -> bool;
        fn DeserializeCiphertextFromFile(ciphertextLocation: &CxxString, ciphertext: Pin<&mut CiphertextDCRTPoly>, serialMode: SerialMode) -> bool;
        fn SerializePublicKeyToFile(publicKeyLocation: &CxxString, publicKey: &PublicKeyDCRTPoly, serialMode: SerialMode) -> bool;
        fn DeserializePublicKeyFromFile(publicKeyLocation: &CxxString, publicKey: Pin<&mut PublicKeyDCRTPoly>, serialMode: SerialMode) -> bool;
    }
}

fn PolycircuitParityCKKS()
{
    let mut _coeff_val = CxxVector::<f64>::new();
    _coeff_val.pin_mut().push(1.0282365732946517);
    _coeff_val.pin_mut().push(-4.706936325599742e-16);
    _coeff_val.pin_mut().push(0.02837802774254295);
    _coeff_val.pin_mut().push(-1.4264063560621828e-15);
    _coeff_val.pin_mut().push(0.02879811263816666);
    _coeff_val.pin_mut().push(-6.119017223279664e-16);
    _coeff_val.pin_mut().push(0.029483781521987242);
    _coeff_val.pin_mut().push(-3.581364595565021e-17);
    _coeff_val.pin_mut().push(0.030412601850717955);
    _coeff_val.pin_mut().push(-8.902249137547338e-17);
    _coeff_val.pin_mut().push(0.03155177709895617);
    _coeff_val.pin_mut().push(8.390625623895192e-17);
    _coeff_val.pin_mut().push(0.03285689179433524);
    _coeff_val.pin_mut().push(8.083651515703904e-17);
    _coeff_val.pin_mut().push(0.03427050362451338);
    _coeff_val.pin_mut().push(7.377611066863944e-16);
    _coeff_val.pin_mut().push(0.03572075499433183);
    _coeff_val.pin_mut().push(-8.840854315909081e-16);
    _coeff_val.pin_mut().push(0.037120231303595916);
    _coeff_val.pin_mut().push(-6.492502388245731e-16);
    _coeff_val.pin_mut().push(0.038365352691959995);
    _coeff_val.pin_mut().push(-7.12179931003787e-16);
    _coeff_val.pin_mut().push(0.039336645537823234);
    _coeff_val.pin_mut().push(1.550219246366002e-16);
    _coeff_val.pin_mut().push(0.03990029203802455);
    _coeff_val.pin_mut().push(6.425991331470952e-16);
    _coeff_val.pin_mut().push(0.039911389645487065);
    _coeff_val.pin_mut().push(1.729287476144253e-16);
    _coeff_val.pin_mut().push(0.03921935219434552);
    _coeff_val.pin_mut().push(6.871103788348319e-16);
    _coeff_val.pin_mut().push(0.03767583299051207);
    _coeff_val.pin_mut().push(2.353468162799871e-16);
    _coeff_val.pin_mut().push(0.035145426516682);
    _coeff_val.pin_mut().push(7.12179931003787e-16);
    _coeff_val.pin_mut().push(0.0315191892083183);
    _coeff_val.pin_mut().push(-4.3999622174084547e-16);
    _coeff_val.pin_mut().push(0.02673069416989159);
    _coeff_val.pin_mut().push(-6.528316034201381e-16);
    _coeff_val.pin_mut().push(0.020773891797598185);
    _coeff_val.pin_mut().push(1.2667798198027133e-15);
    _coeff_val.pin_mut().push(0.0137214958117252);
    _coeff_val.pin_mut().push(6.507851093655296e-16);
    _coeff_val.pin_mut().push(0.005741983414055029);
    _coeff_val.pin_mut().push(7.346913656044815e-16);
    _coeff_val.pin_mut().push(-0.0028873483331737317);
    _coeff_val.pin_mut().push(1.0038053337855103e-15);
    _coeff_val.pin_mut().push(-0.011774390529028452);
    _coeff_val.pin_mut().push(-2.3483519276633494e-16);
    _coeff_val.pin_mut().push(-0.020416755712367677);
    _coeff_val.pin_mut().push(1.5287310587926118e-15);
    _coeff_val.pin_mut().push(-0.02822024351722866);
    _coeff_val.pin_mut().push(3.9190361145754374e-16);
    _coeff_val.pin_mut().push(-0.034534010731828754);
    _coeff_val.pin_mut().push(1.2811052781849733e-15);
    _coeff_val.pin_mut().push(-0.03870382901857966);
    _coeff_val.pin_mut().push(1.8827745302398968e-16);
    _coeff_val.pin_mut().push(-0.040142560034977286);
    _coeff_val.pin_mut().push(-6.344131569286609e-16);
    _coeff_val.pin_mut().push(-0.038413868919243185);
    _coeff_val.pin_mut().push(7.162729191130042e-18);
    _coeff_val.pin_mut().push(-0.0333214285359667);
    _coeff_val.pin_mut().push(-3.2859020164309067e-16);
    _coeff_val.pin_mut().push(-0.024991878044725028);
    _coeff_val.pin_mut().push(-1.8704955659122454e-15);
    _coeff_val.pin_mut().push(-0.013936304421684418);
    _coeff_val.pin_mut().push(-9.33201288901514e-16);
    _coeff_val.pin_mut().push(-0.0010729809164823608);
    _coeff_val.pin_mut().push(-1.0703163905602891e-15);
    _coeff_val.pin_mut().push(0.012305361117403041);
    _coeff_val.pin_mut().push(2.936718968363317e-16);
    _coeff_val.pin_mut().push(0.024632264582911456);
    _coeff_val.pin_mut().push(8.185976218434334e-18);
    _coeff_val.pin_mut().push(0.034240276923933353);
    _coeff_val.pin_mut().push(-1.395708945243054e-15);
    _coeff_val.pin_mut().push(0.039596782655915715);
    _coeff_val.pin_mut().push(1.5451030112294805e-16);
    _coeff_val.pin_mut().push(0.03957792391552036);
    _coeff_val.pin_mut().push(-3.82438576454979e-16);
    _coeff_val.pin_mut().push(0.03373873452834574);
    _coeff_val.pin_mut().push(2.588814979079858e-16);
    _coeff_val.pin_mut().push(0.022523876455433797);
    _coeff_val.pin_mut().push(1.4509642847174857e-15);
    _coeff_val.pin_mut().push(0.0073575909670888315);
    _coeff_val.pin_mut().push(8.646437380721265e-16);
    _coeff_val.pin_mut().push(-0.009441459674504524);
    _coeff_val.pin_mut().push(1.813193732383205e-15);
    _coeff_val.pin_mut().push(-0.024951397393902897);
    _coeff_val.pin_mut().push(-1.4223133679529655e-16);
    _coeff_val.pin_mut().push(-0.03613527538508178);
    _coeff_val.pin_mut().push(-2.7934643845407164e-16);
    _coeff_val.pin_mut().push(-0.04046482545866737);
    _coeff_val.pin_mut().push(-5.304256777788622e-16);
    _coeff_val.pin_mut().push(-0.03656417385700626);
    _coeff_val.pin_mut().push(-2.7095581283017644e-15);
    _coeff_val.pin_mut().push(-0.02471676561206951);
    _coeff_val.pin_mut().push(-4.891120790514515e-16);
    _coeff_val.pin_mut().push(-0.007068369597225695);
    _coeff_val.pin_mut().push(-1.7804498275094676e-16);
    _coeff_val.pin_mut().push(0.012605493587130317);
    _coeff_val.pin_mut().push(-1.4386853203898341e-15);
    _coeff_val.pin_mut().push(0.029611922982651456);
    _coeff_val.pin_mut().push(-3.3920638955137274e-16);
    _coeff_val.pin_mut().push(0.03944671234924423);
    _coeff_val.pin_mut().push(1.08719996651081e-15);
    _coeff_val.pin_mut().push(0.039062647098980954);
    _coeff_val.pin_mut().push(6.671570618023982e-16);
    _coeff_val.pin_mut().push(0.027952547756249297);
    _coeff_val.pin_mut().push(1.4530107787720944e-16);
    _coeff_val.pin_mut().push(0.008664395626407377);
    _coeff_val.pin_mut().push(1.882774530239897e-15);
    _coeff_val.pin_mut().push(-0.013547239782560873);
    _coeff_val.pin_mut().push(5.812043115088378e-16);
    _coeff_val.pin_mut().push(-0.032010009476266636);
    _coeff_val.pin_mut().push(6.528316034201381e-16);
    _coeff_val.pin_mut().push(-0.040625739494329655);
    _coeff_val.pin_mut().push(7.520865650686545e-16);
    _coeff_val.pin_mut().push(-0.03601085870680733);
    _coeff_val.pin_mut().push(5.167397487886673e-17);
    _coeff_val.pin_mut().push(-0.019034820889075973);
    _coeff_val.pin_mut().push(-5.218559839251887e-16);
    _coeff_val.pin_mut().push(0.004947713041894956);
    _coeff_val.pin_mut().push(-1.0478049559595947e-15);
    _coeff_val.pin_mut().push(0.02752812059360267);
    _coeff_val.pin_mut().push(-1.2186872095194115e-15);
    _coeff_val.pin_mut().push(0.040101830805261994);
    _coeff_val.pin_mut().push(-2.967416379182446e-17);
    _coeff_val.pin_mut().push(0.03726115423243095);
    _coeff_val.pin_mut().push(6.988777196488312e-16);
    _coeff_val.pin_mut().push(0.01939255831193185);
    _coeff_val.pin_mut().push(5.883670406999678e-16);
    _coeff_val.pin_mut().push(-0.006803572914617558);
    _coeff_val.pin_mut().push(-4.993445493244944e-16);
    _coeff_val.pin_mut().push(-0.030494428161108613);
    _coeff_val.pin_mut().push(7.387843537136986e-16);
    _coeff_val.pin_mut().push(-0.041094603805437314);
    _coeff_val.pin_mut().push(3.028811200820704e-16);
    _coeff_val.pin_mut().push(-0.03317421083571684);
    _coeff_val.pin_mut().push(1.1562691408538496e-16);
    _coeff_val.pin_mut().push(-0.009604997343471458);
    _coeff_val.pin_mut().push(-3.806478941571965e-16);
    _coeff_val.pin_mut().push(0.018937897272732925);
    _coeff_val.pin_mut().push(-5.300419601436231e-16);
    _coeff_val.pin_mut().push(0.03849788868235471);
    _coeff_val.pin_mut().push(-5.116235136521458e-16);
    _coeff_val.pin_mut().push(0.038692042660548875);
    _coeff_val.pin_mut().push(-4.512519390411927e-16);
    _coeff_val.pin_mut().push(0.018588495207310804);
    _coeff_val.pin_mut().push(3.033927435957225e-16);
    _coeff_val.pin_mut().push(-0.011816946615080924);
    _coeff_val.pin_mut().push(5.065072785156244e-16);
    _coeff_val.pin_mut().push(-0.03608810726019114);
    _coeff_val.pin_mut().push(-1.371151016587751e-15);
    _coeff_val.pin_mut().push(-0.040145780033506585);
    _coeff_val.pin_mut().push(-5.453906655531875e-16);
    _coeff_val.pin_mut().push(-0.020797212174739347);
    _coeff_val.pin_mut().push(-9.848752637803808e-16);
    _coeff_val.pin_mut().push(0.011278410432111675);
    _coeff_val.pin_mut().push(2.5581175682607294e-18);
    _coeff_val.pin_mut().push(0.03682686560665954);
    _coeff_val.pin_mut().push(-3.9190361145754374e-16);
    _coeff_val.pin_mut().push(0.03945351884128929);
    _coeff_val.pin_mut().push(2.9264864980902745e-16);
    _coeff_val.pin_mut().push(0.016575357342929826);
    _coeff_val.pin_mut().push(7.602725412870888e-16);
    _coeff_val.pin_mut().push(-0.01758512160271986);
    _coeff_val.pin_mut().push(1.6985900653251243e-16);
    _coeff_val.pin_mut().push(-0.04020764447946108);
    _coeff_val.pin_mut().push(4.891120790514515e-16);
    _coeff_val.pin_mut().push(-0.03509612845595312);
    _coeff_val.pin_mut().push(-2.0848658181324943e-15);
    _coeff_val.pin_mut().push(-0.004884914335490759);
    _coeff_val.pin_mut().push(-8.648995498289526e-16);
    _coeff_val.pin_mut().push(0.029252074948411616);
    _coeff_val.pin_mut().push(4.563681741777142e-16);
    _coeff_val.pin_mut().push(0.04191655216467781);
    _coeff_val.pin_mut().push(1.2882680073761034e-15);
    _coeff_val.pin_mut().push(0.022655468292275514);
    _coeff_val.pin_mut().push(6.855755082938755e-16);
    _coeff_val.pin_mut().push(-0.01455994959400436);
    _coeff_val.pin_mut().push(1.6735205131561691e-15);
    _coeff_val.pin_mut().push(-0.04053890987153829);
    _coeff_val.pin_mut().push(-5.044607844610158e-16);
    _coeff_val.pin_mut().push(-0.03362052999794349);
    _coeff_val.pin_mut().push(-1.2371056560108887e-15);
    _coeff_val.pin_mut().push(0.00151142865655767);
    _coeff_val.pin_mut().push(4.819493498603214e-16);
    _coeff_val.pin_mut().push(0.035734547119844834);
    _coeff_val.pin_mut().push(9.685033113435122e-16);
    _coeff_val.pin_mut().push(0.039095944314048135);
    _coeff_val.pin_mut().push(1.4750105898591366e-15);
    _coeff_val.pin_mut().push(0.0075869643083738844);
    _coeff_val.pin_mut().push(7.183194131676128e-16);
    _coeff_val.pin_mut().push(-0.031173878232206936);
    _coeff_val.pin_mut().push(1.8009147680555536e-16);
    _coeff_val.pin_mut().push(-0.0413135918991599);
    _coeff_val.pin_mut().push(-6.679244970728765e-16);
    _coeff_val.pin_mut().push(-0.012286463384270278);
    _coeff_val.pin_mut().push(-1.1649667405859362e-15);
    _coeff_val.pin_mut().push(0.028959085684998227);
    _coeff_val.pin_mut().push(2.281840870888571e-16);
    _coeff_val.pin_mut().push(0.04195150804383059);
    _coeff_val.pin_mut().push(3.1311359035511325e-16);
    _coeff_val.pin_mut().push(0.01269787577679402);
    _coeff_val.pin_mut().push(1.9032394707859826e-15);
    _coeff_val.pin_mut().push(-0.02993055873618359);
    _coeff_val.pin_mut().push(1.5041731301373088e-16);
    _coeff_val.pin_mut().push(-0.04152673233725611);
    _coeff_val.pin_mut().push(-1.5844980217806957e-15);
    _coeff_val.pin_mut().push(-0.008740330625590681);
    _coeff_val.pin_mut().push(-5.82227558536142e-16);
    _coeff_val.pin_mut().push(0.03391036152912064);
    _coeff_val.pin_mut().push(1.1690597286951534e-16);
    _coeff_val.pin_mut().push(0.03921310763804737);
    _coeff_val.pin_mut().push(1.0437119678503776e-16);
    _coeff_val.pin_mut().push(7.23135090542721e-05);
    _coeff_val.pin_mut().push(-8.799924434816909e-16);
    _coeff_val.pin_mut().push(-0.0395196033164466);
    _coeff_val.pin_mut().push(-3.601829536111107e-16);
    _coeff_val.pin_mut().push(-0.03293419210435873);
    _coeff_val.pin_mut().push(-8.226906099526505e-16);
    _coeff_val.pin_mut().push(0.013221313455220563);
    _coeff_val.pin_mut().push(-1.1194322478708951e-15);
    _coeff_val.pin_mut().push(0.04364573338713884);
    _coeff_val.pin_mut().push(3.1413683738241756e-16);
    _coeff_val.pin_mut().push(0.02005141263254599);
    _coeff_val.pin_mut().push(8.62597244017518e-16);
    _coeff_val.pin_mut().push(-0.029148352631725948);
    _coeff_val.pin_mut().push(-2.568350038533772e-16);
    _coeff_val.pin_mut().push(-0.041210265200466424);
    _coeff_val.pin_mut().push(3.581364595565021e-16);
    _coeff_val.pin_mut().push(0.000688085518887857);
    _coeff_val.pin_mut().push(-1.4407318144444428e-15);
    _coeff_val.pin_mut().push(0.042033742514799445);
    _coeff_val.pin_mut().push(-2.7320695629024587e-16);
    _coeff_val.pin_mut().push(0.026642805427760808);
    _coeff_val.pin_mut().push(2.5785825088068154e-16);
    _coeff_val.pin_mut().push(-0.025694536755576102);
    _coeff_val.pin_mut().push(6.31343415846748e-16);
    _coeff_val.pin_mut().push(-0.042365103272949296);
    _coeff_val.pin_mut().push(-7.1422642505839565e-16);
    _coeff_val.pin_mut().push(0.0013766875543126205);
    _coeff_val.pin_mut().push(-7.981326812973476e-16);
    _coeff_val.pin_mut().push(0.043483659520571406);
    _coeff_val.pin_mut().push(9.439453826882091e-16);
    _coeff_val.pin_mut().push(0.021686013500515085);
    _coeff_val.pin_mut().push(8.083651515703904e-17);
    _coeff_val.pin_mut().push(-0.032866338103267334);
    _coeff_val.pin_mut().push(1.5471495052840891e-15);
    _coeff_val.pin_mut().push(-0.037683376523961);
    _coeff_val.pin_mut().push(-4.34879986604324e-16);
    _coeff_val.pin_mut().push(0.01593334716083381);
    _coeff_val.pin_mut().push(8.851086786182123e-16);
    _coeff_val.pin_mut().push(0.044857608405025735);
    _coeff_val.pin_mut().push(5.556231358262304e-16);
    _coeff_val.pin_mut().push(0.0021485743967524637);
    _coeff_val.pin_mut().push(7.326448715498729e-16);
    _coeff_val.pin_mut().push(-0.04439493119034457);
    _coeff_val.pin_mut().push(-9.250153126830797e-16);
    _coeff_val.pin_mut().push(-0.017909699804215126);
    _coeff_val.pin_mut().push(-5.054840314883202e-16);
    _coeff_val.pin_mut().push(0.03885352238836723);
    _coeff_val.pin_mut().push(3.499504833380678e-16);
    _coeff_val.pin_mut().push(0.029803366049722092);
    _coeff_val.pin_mut().push(6.200876985464008e-16);
    _coeff_val.pin_mut().push(-0.030919165118297648);
    _coeff_val.pin_mut().push(1.1051067894886351e-16);
    _coeff_val.pin_mut().push(-0.03774960809342361);
    _coeff_val.pin_mut().push(-4.0315932875789093e-16);
    _coeff_val.pin_mut().push(0.02273709567864195);
    _coeff_val.pin_mut().push(-4.635309033688442e-16);
    _coeff_val.pin_mut().push(0.04248848852872072);
    _coeff_val.pin_mut().push(1.816263473465118e-15);
    _coeff_val.pin_mut().push(-0.01573235188920321);
    _coeff_val.pin_mut().push(-8.585042559083007e-16);
    _coeff_val.pin_mut().push(-0.04502814203301542);
    _coeff_val.pin_mut().push(-7.592492942597845e-16);
    _coeff_val.pin_mut().push(0.010716491656246515);
    _coeff_val.pin_mut().push(-5.418093009576225e-16);
    _coeff_val.pin_mut().push(0.04627948299333109);
    _coeff_val.pin_mut().push(1.055990932178029e-15);
    _coeff_val.pin_mut().push(-0.008097381189294317);
    _coeff_val.pin_mut().push(8.431555504987364e-16);
    _coeff_val.pin_mut().push(-0.04685513454275595);
    _coeff_val.pin_mut().push(-2.3227707519807423e-16);
    _coeff_val.pin_mut().push(0.008071803370293128);
    _coeff_val.pin_mut().push(-1.5021266360827002e-15);
    _coeff_val.pin_mut().push(0.04697019045498176);
    _coeff_val.pin_mut().push(9.106898543008197e-17);
    _coeff_val.pin_mut().push(-0.010735980787645986);
    _coeff_val.pin_mut().push(5.08553772570233e-16);
    _coeff_val.pin_mut().push(-0.04639074360804884);
    _coeff_val.pin_mut().push(-2.107888876246841e-15);
    _coeff_val.pin_mut().push(0.016080568633452884);
    _coeff_val.pin_mut().push(-2.1334700519294483e-16);
    _coeff_val.pin_mut().push(0.04441081522455115);
    _coeff_val.pin_mut().push(1.1695713522088055e-15);
    _coeff_val.pin_mut().push(-0.023851190879486076);
    _coeff_val.pin_mut().push(5.71483464749447e-16);
    _coeff_val.pin_mut().push(-0.0398880728527485);
    _coeff_val.pin_mut().push(-1.5844980217806957e-15);
    _coeff_val.pin_mut().push(0.03327360235936262);
    _coeff_val.pin_mut().push(7.239472718177864e-16);
    _coeff_val.pin_mut().push(0.031425796361817866);
    _coeff_val.pin_mut().push(-2.1641674627485772e-16);
    _coeff_val.pin_mut().push(-0.042692741754707816);
    _coeff_val.pin_mut().push(-5.065072785156244e-16);
    _coeff_val.pin_mut().push(-0.01783322397284791);
    _coeff_val.pin_mut().push(7.111566839764828e-16);
    _coeff_val.pin_mut().push(0.049285465936018055);
    _coeff_val.pin_mut().push(1.2790587841303646e-15);
    _coeff_val.pin_mut().push(-0.0010225049218098468);
    _coeff_val.pin_mut().push(5.699485942084905e-16);
    _coeff_val.pin_mut().push(-0.04917901222418253);
    _coeff_val.pin_mut().push(1.3624534168556644e-15);
    _coeff_val.pin_mut().push(0.02303374630277961);
    _coeff_val.pin_mut().push(-7.838072229150875e-16);
    _coeff_val.pin_mut().push(0.038460288578110534);
    _coeff_val.pin_mut().push(1.4427783084990513e-16);
    _coeff_val.pin_mut().push(-0.042823320810027835);
    _coeff_val.pin_mut().push(4.0111283470328235e-16);
    _coeff_val.pin_mut().push(-0.015462921860599046);
    _coeff_val.pin_mut().push(3.7220610618193614e-16);
    _coeff_val.pin_mut().push(0.051980637477125835);
    _coeff_val.pin_mut().push(1.764077875072599e-15);
    _coeff_val.pin_mut().push(-0.016003453443670906);
    _coeff_val.pin_mut().push(-1.055990932178029e-15);
    _coeff_val.pin_mut().push(-0.0420642054982171);
    _coeff_val.pin_mut().push(-5.525533947443175e-16);
    _coeff_val.pin_mut().push(0.04439051968632978);
    _coeff_val.pin_mut().push(-4.880888320241472e-16);
    _coeff_val.pin_mut().push(0.01100554029332548);
    _coeff_val.pin_mut().push(1.041665473795769e-15);
    _coeff_val.pin_mut().push(-0.05278928368608406);
    _coeff_val.pin_mut().push(-1.3844532279427068e-15);
    _coeff_val.pin_mut().push(0.029680027640307378);
    _coeff_val.pin_mut().push(4.092988109217167e-17);
    _coeff_val.pin_mut().push(0.029198101501758354);
    _coeff_val.pin_mut().push(1.4478945436355728e-16);
    _coeff_val.pin_mut().push(-0.05436289665733025);
    _coeff_val.pin_mut().push(-1.3558023111781865e-15);
    _coeff_val.pin_mut().push(0.018100898000621656);
    _coeff_val.pin_mut().push(-9.36271029983427e-16);
    _coeff_val.pin_mut().push(0.038258753311141515);
    _coeff_val.pin_mut().push(1.139897188416981e-15);
    _coeff_val.pin_mut().push(-0.054237828648586076);
    _coeff_val.pin_mut().push(-1.171617846263414e-15);
    _coeff_val.pin_mut().push(0.014471910714514756);
    _coeff_val.pin_mut().push(6.681803088297025e-16);
    _coeff_val.pin_mut().push(0.039919915061914904);
    _coeff_val.pin_mut().push(9.78224158102903e-16);
    _coeff_val.pin_mut().push(-0.05631339747917951);
    _coeff_val.pin_mut().push(-7.766444937239574e-16);
    _coeff_val.pin_mut().push(0.02073779944867681);
    _coeff_val.pin_mut().push(9.004573840277768e-17);
    _coeff_val.pin_mut().push(0.03347906768939985);
    _coeff_val.pin_mut().push(3.4278775414693775e-16);
    _coeff_val.pin_mut().push(-0.05942762653047738);
    _coeff_val.pin_mut().push(-1.2862215133214946e-15);
    _coeff_val.pin_mut().push(0.03692617720380156);
    _coeff_val.pin_mut().push(-6.139482163825751e-18);
    _coeff_val.pin_mut().push(0.014568064466136042);
    _coeff_val.pin_mut().push(1.1726410932907183e-15);
    _coeff_val.pin_mut().push(-0.05548802466976733);
    _coeff_val.pin_mut().push(-1.6249162793592153e-15);
    _coeff_val.pin_mut().push(0.0572853951202334);
    _coeff_val.pin_mut().push(1.0928278251609835e-15);
    _coeff_val.pin_mut().push(-0.020565229468585605);
    _coeff_val.pin_mut().push(-1.798868274000945e-15);
    _coeff_val.pin_mut().push(-0.029430599788513288);
    _coeff_val.pin_mut().push(-1.4110576506526182e-15);
    _coeff_val.pin_mut().push(0.062077077978793575);
    _coeff_val.pin_mut().push(7.490168239867416e-16);
    _coeff_val.pin_mut().push(-0.060040485031613244);
    _coeff_val.pin_mut().push(-2.619512389898987e-16);
    _coeff_val.pin_mut().push(0.026521972259372587);
    _coeff_val.pin_mut().push(8.13481386706912e-17);
    _coeff_val.pin_mut().push(0.020080885513841927);
    _coeff_val.pin_mut().push(1.557381975557132e-15);
    _coeff_val.pin_mut().push(-0.057920705367231096);
    _coeff_val.pin_mut().push(3.3025297806246014e-16);
    _coeff_val.pin_mut().push(0.072169469706476);
    _coeff_val.pin_mut().push(6.322387569956392e-16);
    _coeff_val.pin_mut().push(-0.059605597281768195);
    _coeff_val.pin_mut().push(-1.6228697853046067e-15);
    _coeff_val.pin_mut().push(0.027057676956707317);
    _coeff_val.pin_mut().push(-5.668788531265776e-16);
    _coeff_val.pin_mut().push(0.013657485273408378);
    _coeff_val.pin_mut().push(4.0520582281249955e-16);
    _coeff_val.pin_mut().push(-0.05107741847405493);
    _coeff_val.pin_mut().push(-7.080869428945699e-16);
    _coeff_val.pin_mut().push(0.0775680498867074);
    _coeff_val.pin_mut().push(1.7456594285811218e-15);
    _coeff_val.pin_mut().push(-0.09034438911704955);
    _coeff_val.pin_mut().push(-1.371151016587751e-15);
    _coeff_val.pin_mut().push(0.09061405859748928);
    _coeff_val.pin_mut().push(7.858537169696961e-16);
    _coeff_val.pin_mut().push(-0.08186414697628912);
    _coeff_val.pin_mut().push(-2.476257806076386e-16);
    _coeff_val.pin_mut().push(0.06817854818541069);
    _coeff_val.pin_mut().push(2.5657919209655116e-16);
    _coeff_val.pin_mut().push(-0.053077754238003844);
    _coeff_val.pin_mut().push(-8.267835980618677e-16);
    _coeff_val.pin_mut().push(0.03898716504532329);
    _coeff_val.pin_mut().push(1.985099232970326e-16);
    _coeff_val.pin_mut().push(-0.027199202468130457);
    _coeff_val.pin_mut().push(-2.998113790001575e-16);
    _coeff_val.pin_mut().push(0.01811262388276272);
    _coeff_val.pin_mut().push(2.075144971373104e-15);
    _coeff_val.pin_mut().push(-0.011558155702415432);
    _coeff_val.pin_mut().push(9.048061838938199e-16);
    _coeff_val.pin_mut().push(0.007089882783377631);
    _coeff_val.pin_mut().push(6.221341926010093e-16);
    _coeff_val.pin_mut().push(-0.004191363748538981);
    _coeff_val.pin_mut().push(-3.0799735521859184e-16);
    _coeff_val.pin_mut().push(0.002393211870511635);
    _coeff_val.pin_mut().push(1.2898028779170598e-15);
    _coeff_val.pin_mut().push(-0.001322278076469718);
    _coeff_val.pin_mut().push(7.572028002051759e-16);
    _coeff_val.pin_mut().push(0.0007080737423442029);
    _coeff_val.pin_mut().push(4.706936325599742e-17);
    _coeff_val.pin_mut().push(-0.0003680090978295104);
    _coeff_val.pin_mut().push(-5.054840314883202e-16);
    _coeff_val.pin_mut().push(0.00018586400318515415);
    _coeff_val.pin_mut().push(-3.253925546827648e-16);
    _coeff_val.pin_mut().push(-9.1310710816589e-05);
    _coeff_val.pin_mut().push(-1.0027820867582059e-16);
    _coeff_val.pin_mut().push(4.365161272285162e-05);
    _coeff_val.pin_mut().push(-6.344131569286609e-16);
    _coeff_val.pin_mut().push(-2.0255567135543343e-05);
    _coeff_val.pin_mut().push(-5.607393709627519e-16);
    _coeff_val.pin_mut().push(8.959692105336827e-06);
    _coeff_val.pin_mut().push(-1.0805488608333321e-15);
    _coeff_val.pin_mut().push(-3.3612648141086696e-06);
    _coeff_val.pin_mut().push(8.513415267171707e-16);

    let_cxx_string!(_cc_location = "/root/POLYCIRCUIT/POLYCIRCUIT_PARITY/INPUT/cc.bin");
    let_cxx_string!(_public_key_location = "/root/POLYCIRCUIT/POLYCIRCUIT_PARITY/INPUT/pub_key.bin");
    let_cxx_string!(_mult_key_location = "/root/POLYCIRCUIT/POLYCIRCUIT_PARITY/INPUT/mult_key.bin");
    let_cxx_string!(_rot_key_location = "/root/POLYCIRCUIT/POLYCIRCUIT_PARITY/INPUT/rot_key.bin");
    let_cxx_string!(_input_location = "/root/POLYCIRCUIT/POLYCIRCUIT_PARITY/INPUT/input");
    let_cxx_string!(_output_location = "/root/POLYCIRCUIT/POLYCIRCUIT_PARITY/INPUT/output");

    let mut _cc = ffi::GenEmptyCryptoContext();
    ffi::DeserializeCryptoContextFromFile(&_cc_location, _cc.pin_mut(), ffi::SerialMode::BINARY);
    let mut _public_key = ffi::GenDefaultConstructedPublicKey();
    ffi::DeserializePublicKeyFromFile(&_public_key_location, _public_key.pin_mut(), ffi::SerialMode::BINARY);
    ffi::DeserializeEvalMultKeyFromFile(&_mult_key_location, ffi::SerialMode::BINARY);
    ffi::DeserializeEvalAutomorphismKeyFromFile(&_rot_key_location, ffi::SerialMode::BINARY);

    let mut _input_cipher_text = ffi::GenDefaultConstructedCiphertext();
    ffi::DeserializeCiphertextFromFile(&_input_location, _input_cipher_text.pin_mut(), ffi::SerialMode::BINARY);
    _cc.Enable(ffi::PKESchemeFeature::ADVANCEDSHE);

    let _output_ciphertext = _cc.EvalChebyshevSeries(_input_cipher_text.GetCipherText(), &_coeff_val, -1.0, 1.0);
    ffi::SerializeCiphertextToFile(&_output_location, &_output_ciphertext, ffi::SerialMode::BINARY);
}


fn PolynomialEvaluationExample()
{
    println!("\n======EXAMPLE FOR EVALPOLY========\n");

    let mut _cc_params_ckksrns = ffi::GetParamsCKKSRNS();
    _cc_params_ckksrns.pin_mut().SetMultiplicativeDepth(6);
    _cc_params_ckksrns.pin_mut().SetScalingModSize(50);

    let mut _cc = ffi::GenCryptoContextByParamsCKKSRNS(&_cc_params_ckksrns);
    _cc.Enable(ffi::PKESchemeFeature::PKE);
    _cc.Enable(ffi::PKESchemeFeature::KEYSWITCH);
    _cc.Enable(ffi::PKESchemeFeature::LEVELEDSHE);
    _cc.Enable(ffi::PKESchemeFeature::ADVANCEDSHE);

    let mut _vals = CxxVector::<ffi::ComplexPair>::new();
    _vals.pin_mut().push(ffi::ComplexPair{re: 0.5, im: 0.0});
    _vals.pin_mut().push(ffi::ComplexPair{re: 0.7, im: 0.0});
    _vals.pin_mut().push(ffi::ComplexPair{re: 0.9, im: 0.0});
    _vals.pin_mut().push(ffi::ComplexPair{re: 0.95, im: 0.0});
    _vals.pin_mut().push(ffi::ComplexPair{re: 0.93, im: 0.0});
    let _input = ffi::GenVectorOfComplexNumbers(&_vals);
    let _encoded_length = _vals.len(); // no len() funtion implemented for _input

    let mut _coefficients_1 = CxxVector::<f64>::new();
    _coefficients_1.pin_mut().push(0.15);
    _coefficients_1.pin_mut().push(0.75);
    _coefficients_1.pin_mut().push(0.0);
    _coefficients_1.pin_mut().push(1.25);
    _coefficients_1.pin_mut().push(0.0);
    _coefficients_1.pin_mut().push(0.0);
    _coefficients_1.pin_mut().push(1.0);
    _coefficients_1.pin_mut().push(0.0);
    _coefficients_1.pin_mut().push(1.0);
    _coefficients_1.pin_mut().push(2.0);
    _coefficients_1.pin_mut().push(0.0);
    _coefficients_1.pin_mut().push(1.0);
    _coefficients_1.pin_mut().push(0.0);
    _coefficients_1.pin_mut().push(0.0);
    _coefficients_1.pin_mut().push(0.0);
    _coefficients_1.pin_mut().push(0.0);
    _coefficients_1.pin_mut().push(1.0);

    let mut _coefficients_2 = CxxVector::<f64>::new();
    _coefficients_2.pin_mut().push(1.0);
    _coefficients_2.pin_mut().push(2.0);
    _coefficients_2.pin_mut().push(3.0);
    _coefficients_2.pin_mut().push(4.0);
    _coefficients_2.pin_mut().push(5.0);
    _coefficients_2.pin_mut().push(-1.0);
    _coefficients_2.pin_mut().push(-2.0);
    _coefficients_2.pin_mut().push(-3.0);
    _coefficients_2.pin_mut().push(-4.0);
    _coefficients_2.pin_mut().push(-5.0);
    _coefficients_2.pin_mut().push(0.1);
    _coefficients_2.pin_mut().push(0.2);
    _coefficients_2.pin_mut().push(0.3);
    _coefficients_2.pin_mut().push(0.4);
    _coefficients_2.pin_mut().push(0.5);
    _coefficients_2.pin_mut().push(-0.1);
    _coefficients_2.pin_mut().push(-0.2);
    _coefficients_2.pin_mut().push(-0.3);
    _coefficients_2.pin_mut().push(-0.4);
    _coefficients_2.pin_mut().push(-0.5);
    _coefficients_2.pin_mut().push(0.1);
    _coefficients_2.pin_mut().push(0.2);
    _coefficients_2.pin_mut().push(0.3);
    _coefficients_2.pin_mut().push(0.4);
    _coefficients_2.pin_mut().push(0.5);
    _coefficients_2.pin_mut().push(-0.1);
    _coefficients_2.pin_mut().push(-0.2);
    _coefficients_2.pin_mut().push(-0.3);
    _coefficients_2.pin_mut().push(-0.4);
    _coefficients_2.pin_mut().push(-0.5);

    let mut _plain_text_1 = _cc.MakeCKKSPackedPlaintextByVectorOfComplexNumbers(&_input, 1, 0, SharedPtr::<ffi::DCRTPolyParams>::null(), 0);
    let mut _key_pair = _cc.KeyGen();
    print!("Generating evaluation key for homomorphic multiplication...");
    _cc.EvalMultKeyGen(_key_pair.GetPrivateKey());
    println!("Completed.\n");
    let mut _cipher_text_1 = _cc.Encrypt(_key_pair.GetPublicKey(), _plain_text_1.GetPlainText());

    let mut _start = Instant::now();
    let mut _result = _cc.EvalPoly(_cipher_text_1.GetCipherText(), &_coefficients_1);
    let _time_eval_poly_1 = _start.elapsed();

    _start = Instant::now();
    let mut _result_2 = _cc.EvalPoly(_cipher_text_1.GetCipherText(), &_coefficients_2);
    let _time_eval_poly_2 = _start.elapsed();

    let mut _plain_text_dec = ffi::GenEmptyPlainText();
    _cc.Decrypt(_key_pair.GetPrivateKey(), _result.GetCipherText(), _plain_text_dec.pin_mut());
    _plain_text_dec.SetLength(_encoded_length);
    let mut _plain_text_dec_2 = ffi::GenEmptyPlainText();
    _cc.Decrypt(_key_pair.GetPrivateKey(), _result_2.GetCipherText(), _plain_text_dec_2.pin_mut());
    _plain_text_dec_2.SetLength(_encoded_length);

    println!("\n Original Plaintext #1:");
    println!("{}", _plain_text_1.GetString());
    println!("\n Result of evaluating a polynomial with coefficients [{} ]", _coefficients_1.iter().fold(String::new(), |acc, &arg| acc + " " + &arg.to_string()));
    println!("{}", _plain_text_dec.GetString());
    println!("\n Expected result: (0.70519107, 1.38285078, 3.97211180, 5.60215665, 4.86357575)");
    println!("\n Evaluation time: {:.0?}", _time_eval_poly_1);
    println!("\n Result of evaluating a polynomial with coefficients [{} ]", _coefficients_2.iter().fold(String::new(), |acc, &arg| acc + " " + &arg.to_string()));
    println!("{}\n", _plain_text_dec_2.GetString());
    println!(" Expected result: (3.4515092326, 5.3752765397, 4.8993108833, 3.2495023573, 4.0485229982)");
    print!("\n Evaluation time: {:.0?}\n", _time_eval_poly_2);
}

fn SimpleRealNumbersExample()
{
    let _mult_depth: u32 = 1;
    let _scale_mod_size: u32 = 50;
    let _batch_size: u32 = 8;

    let mut _cc_params_ckksrns = ffi::GetParamsCKKSRNS();
    _cc_params_ckksrns.pin_mut().SetMultiplicativeDepth(_mult_depth);
    _cc_params_ckksrns.pin_mut().SetScalingModSize(_scale_mod_size);
    _cc_params_ckksrns.pin_mut().SetBatchSize(_batch_size);

    let mut _cc = ffi::GenCryptoContextByParamsCKKSRNS(&_cc_params_ckksrns);
    _cc.Enable(ffi::PKESchemeFeature::PKE);
    _cc.Enable(ffi::PKESchemeFeature::KEYSWITCH);
    _cc.Enable(ffi::PKESchemeFeature::LEVELEDSHE);

    println!("CKKS scheme is using ring dimension {}\n", _cc.GetRingDimension());

    let mut _key_pair = _cc.KeyGen();
    _cc.EvalMultKeyGen(_key_pair.GetPrivateKey());
    let mut _index_list = CxxVector::<i32>::new();
    _index_list.pin_mut().push(1);
    _index_list.pin_mut().push(-2);
    _cc.EvalRotateKeyGen(_key_pair.GetPrivateKey(), &_index_list, SharedPtr::<ffi::PublicKeyImpl>::null());

    let mut _x_1 = CxxVector::<f64>::new();
    _x_1.pin_mut().push(0.25);
    _x_1.pin_mut().push(0.5);
    _x_1.pin_mut().push(0.75);
    _x_1.pin_mut().push(1.0);
    _x_1.pin_mut().push(2.0);
    _x_1.pin_mut().push(3.0);
    _x_1.pin_mut().push(4.0);
    _x_1.pin_mut().push(5.0);

    let mut _x_2 = CxxVector::<f64>::new();
    _x_2.pin_mut().push(5.0);
    _x_2.pin_mut().push(4.0);
    _x_2.pin_mut().push(3.0);
    _x_2.pin_mut().push(2.0);
    _x_2.pin_mut().push(1.0);
    _x_2.pin_mut().push(0.75);
    _x_2.pin_mut().push(0.5);
    _x_2.pin_mut().push(0.25);

    let mut _p_txt_1 = _cc.MakeCKKSPackedPlaintext(&_x_1, 1, 0, SharedPtr::<ffi::DCRTPolyParams>::null(), 0);
    let mut _p_txt_2 = _cc.MakeCKKSPackedPlaintext(&_x_2, 1, 0, SharedPtr::<ffi::DCRTPolyParams>::null(), 0);

    println!("Input x1: {}", _p_txt_1.GetString());
    println!("Input x2: {}", _p_txt_2.GetString());

    let mut _c1 = _cc.Encrypt(_key_pair.GetPublicKey(), _p_txt_1.GetPlainText());
    let mut _c2 = _cc.Encrypt(_key_pair.GetPublicKey(), _p_txt_2.GetPlainText());

    let mut _c_add = _cc.EvalAdd(_c1.GetCipherText(), _c2.GetCipherText());
    let mut _c_sub = _cc.EvalSub(_c1.GetCipherText(), _c2.GetCipherText());
    let mut _c_scalar = _cc.EvalMultByConst(_c1.GetCipherText(), 4.0);
    let mut _c_mul = _cc.EvalMult(_c1.GetCipherText(), _c2.GetCipherText());
    let mut _c_rot_1 = _cc.EvalRotate(_c1.GetCipherText(), 1);
    let mut _c_rot_2 = _cc.EvalRotate(_c1.GetCipherText(), -2);

    let mut _result = ffi::GenEmptyPlainText();
    println!("\nResults of homomorphic computations:");

    _cc.Decrypt(_key_pair.GetPrivateKey(), _c1.GetCipherText(), _result.pin_mut());
    _result.SetLength(_batch_size.try_into().unwrap());
    println!("x1 = {}Estimated precision in bits: {}", _result.GetString(), _result.GetLogPrecision());

    _cc.Decrypt(_key_pair.GetPrivateKey(), _c_add.GetCipherText(), _result.pin_mut());
    _result.SetLength(_batch_size.try_into().unwrap());
    println!("x1 + x2 = {}Estimated precision in bits: {}",_result.GetString(), _result.GetLogPrecision());

    _cc.Decrypt(_key_pair.GetPrivateKey(), _c_sub.GetCipherText(), _result.pin_mut());
    _result.SetLength(_batch_size.try_into().unwrap());
    println!("x1 - x2 = {}", _result.GetString());

    _cc.Decrypt(_key_pair.GetPrivateKey(), _c_scalar.GetCipherText(), _result.pin_mut());
    _result.SetLength(_batch_size.try_into().unwrap());
    println!("4 * x1 = {}", _result.GetString());

    _cc.Decrypt(_key_pair.GetPrivateKey(), _c_mul.GetCipherText(), _result.pin_mut());
    _result.SetLength(_batch_size.try_into().unwrap());
    println!("x1 * x2 = {}", _result.GetString());

    _cc.Decrypt(_key_pair.GetPrivateKey(), _c_rot_1.GetCipherText(), _result.pin_mut());
    _result.SetLength(_batch_size.try_into().unwrap());
    println!("\nIn rotations, very small outputs (~10^-10 here) correspond to 0's:");
    println!("x1 rotate by 1 = {}", _result.GetString());

    _cc.Decrypt(_key_pair.GetPrivateKey(), _c_rot_2.GetCipherText(), _result.pin_mut());
    _result.SetLength(_batch_size.try_into().unwrap());
    println!("x1 rotate by -2 = {}", _result.GetString());
}

fn SimpleIntegersExample()
{
    let mut _cc_params_bfvrns = ffi::GetParamsBFVRNS();
    _cc_params_bfvrns.pin_mut().SetPlaintextModulus(65537);
    _cc_params_bfvrns.pin_mut().SetMultiplicativeDepth(2);

    let mut _cc = ffi::GenCryptoContextByParamsBFVRNS(&_cc_params_bfvrns);
    _cc.Enable(ffi::PKESchemeFeature::PKE);
    _cc.Enable(ffi::PKESchemeFeature::KEYSWITCH);
    _cc.Enable(ffi::PKESchemeFeature::LEVELEDSHE);
    
    let mut _key_pair = _cc.KeyGen();
    _cc.EvalMultKeyGen(_key_pair.GetPrivateKey());
    
    let mut _index_list = CxxVector::<i32>::new();
    _index_list.pin_mut().push(1);
    _index_list.pin_mut().push(2);
    _index_list.pin_mut().push(-1);
    _index_list.pin_mut().push(-2);    
    _cc.EvalRotateKeyGen(_key_pair.GetPrivateKey(), &_index_list, SharedPtr::<ffi::PublicKeyImpl>::null());
    
    let mut _vector_of_ints_1 = CxxVector::<i64>::new();
    _vector_of_ints_1.pin_mut().push(1);
    _vector_of_ints_1.pin_mut().push(2);
    _vector_of_ints_1.pin_mut().push(3);
    _vector_of_ints_1.pin_mut().push(4);
    _vector_of_ints_1.pin_mut().push(5);
    _vector_of_ints_1.pin_mut().push(6);    
    _vector_of_ints_1.pin_mut().push(7);
    _vector_of_ints_1.pin_mut().push(8);
    _vector_of_ints_1.pin_mut().push(9);
    _vector_of_ints_1.pin_mut().push(10);
    _vector_of_ints_1.pin_mut().push(11);
    _vector_of_ints_1.pin_mut().push(12);    
    let mut _plain_text_1 = _cc.MakePackedPlaintext(&_vector_of_ints_1, 1, 0);
    
    let mut _vector_of_ints_2 = CxxVector::<i64>::new();
    _vector_of_ints_2.pin_mut().push(3);
    _vector_of_ints_2.pin_mut().push(2);
    _vector_of_ints_2.pin_mut().push(1);
    _vector_of_ints_2.pin_mut().push(4);
    _vector_of_ints_2.pin_mut().push(5);
    _vector_of_ints_2.pin_mut().push(6);    
    _vector_of_ints_2.pin_mut().push(7);
    _vector_of_ints_2.pin_mut().push(8);
    _vector_of_ints_2.pin_mut().push(9);
    _vector_of_ints_2.pin_mut().push(10);
    _vector_of_ints_2.pin_mut().push(11);
    _vector_of_ints_2.pin_mut().push(12);    
    let mut _plain_text_2 = _cc.MakePackedPlaintext(&_vector_of_ints_2, 1, 0); 
    
    let mut _vector_of_ints_3 = CxxVector::<i64>::new();
    _vector_of_ints_3.pin_mut().push(1);
    _vector_of_ints_3.pin_mut().push(2);
    _vector_of_ints_3.pin_mut().push(5);
    _vector_of_ints_3.pin_mut().push(2);
    _vector_of_ints_3.pin_mut().push(5);
    _vector_of_ints_3.pin_mut().push(6);    
    _vector_of_ints_3.pin_mut().push(7);
    _vector_of_ints_3.pin_mut().push(8);
    _vector_of_ints_3.pin_mut().push(9);
    _vector_of_ints_3.pin_mut().push(10);
    _vector_of_ints_3.pin_mut().push(11);
    _vector_of_ints_3.pin_mut().push(12);    
    let mut _plain_text_3 = _cc.MakePackedPlaintext(&_vector_of_ints_3, 1, 0);

    let mut _cipher_text_1 = _cc.Encrypt(_key_pair.GetPublicKey(), _plain_text_1.GetPlainText());
    let mut _cipher_text_2 = _cc.Encrypt(_key_pair.GetPublicKey(), _plain_text_2.GetPlainText());
    let mut _cipher_text_3 = _cc.Encrypt(_key_pair.GetPublicKey(), _plain_text_3.GetPlainText());    

    let mut _cipher_text_add_1_2 = _cc.EvalAdd(_cipher_text_1.GetCipherText(), _cipher_text_2.GetCipherText());
    let mut _cipher_text_add_result = _cc.EvalAdd(_cipher_text_add_1_2.GetCipherText(), _cipher_text_3.GetCipherText());

    let mut _cipher_text_mul_1_2 = _cc.EvalMult(_cipher_text_1.GetCipherText(), _cipher_text_2.GetCipherText());
    let mut _cipher_text_mult_result = _cc.EvalMult(_cipher_text_mul_1_2.GetCipherText(), _cipher_text_3.GetCipherText());
    
    let mut _cipher_text_rot_1 = _cc.EvalRotate(_cipher_text_1.GetCipherText(), 1);
    let mut _cipher_text_rot_2 = _cc.EvalRotate(_cipher_text_1.GetCipherText(), 2);
    let mut _cipher_text_rot_3 = _cc.EvalRotate(_cipher_text_1.GetCipherText(), -1);
    let mut _cipher_text_rot_4 = _cc.EvalRotate(_cipher_text_1.GetCipherText(), -2);
    
    let mut _plain_text_add_result = ffi::GenEmptyPlainText();
    _cc.Decrypt(_key_pair.GetPrivateKey(), _cipher_text_add_result.GetCipherText(), _plain_text_add_result.pin_mut());
    let mut _plain_text_mult_result = ffi::GenEmptyPlainText();
    _cc.Decrypt(_key_pair.GetPrivateKey(), _cipher_text_mult_result.GetCipherText(), _plain_text_mult_result.pin_mut());
    let mut _plain_text_rot_1 = ffi::GenEmptyPlainText();
    _cc.Decrypt(_key_pair.GetPrivateKey(), _cipher_text_rot_1.GetCipherText(), _plain_text_rot_1.pin_mut());
    let mut _plain_text_rot_2 = ffi::GenEmptyPlainText();
    _cc.Decrypt(_key_pair.GetPrivateKey(), _cipher_text_rot_2.GetCipherText(), _plain_text_rot_2.pin_mut()); 
    let mut _plain_text_rot_3 = ffi::GenEmptyPlainText();
    _cc.Decrypt(_key_pair.GetPrivateKey(), _cipher_text_rot_3.GetCipherText(), _plain_text_rot_3.pin_mut());     
    let mut _plain_text_rot_4 = ffi::GenEmptyPlainText();
    _cc.Decrypt(_key_pair.GetPrivateKey(), _cipher_text_rot_4.GetCipherText(), _plain_text_rot_4.pin_mut());     

    _plain_text_rot_1.SetLength(_vector_of_ints_1.len());
    _plain_text_rot_2.SetLength(_vector_of_ints_1.len());
    _plain_text_rot_3.SetLength(_vector_of_ints_1.len());
    _plain_text_rot_4.SetLength(_vector_of_ints_1.len());

    println!("Plaintext #1: {}", _plain_text_1.GetString());
    println!("Plaintext #2: {}", _plain_text_2.GetString());
    println!("Plaintext #3: {}", _plain_text_3.GetString());

    println!("\nResults of homomorphic computations");
    println!("#1 + #2 + #3: {}", _plain_text_add_result.GetString());
    println!("#1 * #2 * #3: {}", _plain_text_mult_result.GetString());
    println!("Left rotation of #1 by 1: {}", _plain_text_rot_1.GetString());
    println!("Left rotation of #1 by 2: {}", _plain_text_rot_2.GetString());
    println!("Right rotation of #1 by -1: {}", _plain_text_rot_3.GetString());
    println!("Right rotation of #1 by -2: {}", _plain_text_rot_4.GetString());	
}

fn main()
{
    SimpleIntegersExample();
    SimpleRealNumbersExample();
    PolynomialEvaluationExample();
    PolycircuitParityCKKS();
}
