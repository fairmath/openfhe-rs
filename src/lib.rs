#![allow(non_snake_case)]
#![allow(dead_code)]
#![allow(unused_imports)]

use cxx::{CxxVector, SharedPtr, let_cxx_string};

#[cxx::bridge(namespace = "openfhe")]
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
        include!("openfhe/src/bindings.hpp");
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
        type Complex;
    }

    // Params
    unsafe extern "C++"
    {
        fn GetParamsByScheme(scheme: SCHEME) -> UniquePtr<Params>;
        fn GetParamsByVectorOfString(vals: &CxxVector<CxxString>) -> UniquePtr<Params>;

        // getters
        fn GetScheme(self: &Params) -> SCHEME;
        fn GetPlaintextModulus(self: &Params) -> u64;
        fn GetDigitSize(self: &Params) -> u32;
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
        fn SetPlaintextModulus(self: Pin<&mut Params>, ptModulus0: u64);
        fn SetDigitSize(self: Pin<&mut Params>, digitSize0: u32);
        fn SetStandardDeviation(self: Pin<&mut Params>, standardDeviation0: f32);
        fn SetSecretKeyDist(self: Pin<&mut Params>, secretKeyDist0: SecretKeyDist);
        fn SetMaxRelinSkDeg(self: Pin<&mut Params>, maxRelinSkDeg0: u32);
        fn SetPREMode(self: Pin<&mut Params>, PREMode0: ProxyReEncryptionMode);
        fn SetMultipartyMode(self: Pin<&mut Params>, multipartyMode0: MultipartyMode);
        fn SetExecutionMode(self: Pin<&mut Params>, executionMode0: ExecutionMode);
        fn SetDecryptionNoiseMode(self: Pin<&mut Params>,
                                  decryptionNoiseMode0: DecryptionNoiseMode);
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
        fn SetEncryptionTechnique(self: Pin<&mut Params>,
                                  encryptionTechnique0: EncryptionTechnique);
        fn SetMultiplicationTechnique(self: Pin<&mut Params>,
                                      multiplicationTechnique0: MultiplicationTechnique);
        fn SetMultiHopModSize(self: Pin<&mut Params>, multiHopModSize0: u32);
        fn SetInteractiveBootCompressionLevel(self: Pin<&mut Params>,
                                              interactiveBootCompressionLevel0: COMPRESSION_LEVEL);
    }

    // ParamsBFVRNS
    unsafe extern "C++"
    {
        fn GetParamsBFVRNS() -> UniquePtr<ParamsBFVRNS>;
        fn GetParamsBFVRNSbyVectorOfString(vals: &CxxVector<CxxString>) -> UniquePtr<ParamsBFVRNS>;
        // getters
        fn GetScheme(self: &ParamsBFVRNS) -> SCHEME;
        fn GetPlaintextModulus(self: &ParamsBFVRNS) -> u64;
        fn GetDigitSize(self: &ParamsBFVRNS) -> u32;
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
        fn SetPlaintextModulus(self: Pin<&mut ParamsBFVRNS>, ptModulus0: u64);
        fn SetDigitSize(self: Pin<&mut ParamsBFVRNS>, digitSize0: u32);
        fn SetStandardDeviation(self: Pin<&mut ParamsBFVRNS>, standardDeviation0: f32);
        fn SetSecretKeyDist(self: Pin<&mut ParamsBFVRNS>, secretKeyDist0: SecretKeyDist);
        fn SetMaxRelinSkDeg(self: Pin<&mut ParamsBFVRNS>, maxRelinSkDeg0: u32);
        fn SetPREMode(self: Pin<&mut ParamsBFVRNS>, PREMode0: ProxyReEncryptionMode);
        fn SetMultipartyMode(self: Pin<&mut ParamsBFVRNS>, multipartyMode0: MultipartyMode);
        fn SetExecutionMode(self: Pin<&mut ParamsBFVRNS>, executionMode0: ExecutionMode);
        fn SetDecryptionNoiseMode(self: Pin<&mut ParamsBFVRNS>,
                                  decryptionNoiseMode0: DecryptionNoiseMode);
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
        fn SetEncryptionTechnique(self: Pin<&mut ParamsBFVRNS>,
                                  encryptionTechnique0: EncryptionTechnique);
        fn SetMultiplicationTechnique(self: Pin<&mut ParamsBFVRNS>,
                                      multiplicationTechnique0: MultiplicationTechnique);
        fn SetMultiHopModSize(self: Pin<&mut ParamsBFVRNS>, multiHopModSize0: u32);
        fn SetInteractiveBootCompressionLevel(self: Pin<&mut ParamsBFVRNS>,
                                              interactiveBootCompressionLevel0: COMPRESSION_LEVEL);
    }

    // ParamsBGVRNS
    unsafe extern "C++"
    {
        fn GetParamsBGVRNS() -> UniquePtr<ParamsBGVRNS>;
        fn GetParamsBGVRNSbyVectorOfString(vals: &CxxVector<CxxString>) -> UniquePtr<ParamsBGVRNS>;
        // getters
        fn GetScheme(self: &ParamsBGVRNS) -> SCHEME;
        fn GetPlaintextModulus(self: &ParamsBGVRNS) -> u64;
        fn GetDigitSize(self: &ParamsBGVRNS) -> u32;
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
        fn SetPlaintextModulus(self: Pin<&mut ParamsBGVRNS>, ptModulus0: u64);
        fn SetDigitSize(self: Pin<&mut ParamsBGVRNS>, digitSize0: u32);
        fn SetStandardDeviation(self: Pin<&mut ParamsBGVRNS>, standardDeviation0: f32);
        fn SetSecretKeyDist(self: Pin<&mut ParamsBGVRNS>, secretKeyDist0: SecretKeyDist);
        fn SetMaxRelinSkDeg(self: Pin<&mut ParamsBGVRNS>, maxRelinSkDeg0: u32);
        fn SetPREMode(self: Pin<&mut ParamsBGVRNS>, PREMode0: ProxyReEncryptionMode);
        fn SetMultipartyMode(self: Pin<&mut ParamsBGVRNS>, multipartyMode0: MultipartyMode);
        fn SetExecutionMode(self: Pin<&mut ParamsBGVRNS>, executionMode0: ExecutionMode);
        fn SetDecryptionNoiseMode(self: Pin<&mut ParamsBGVRNS>,
                                  decryptionNoiseMode0: DecryptionNoiseMode);
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
        fn SetEncryptionTechnique(self: Pin<&mut ParamsBGVRNS>,
                                  encryptionTechnique0: EncryptionTechnique);
        fn SetMultiplicationTechnique(self: Pin<&mut ParamsBGVRNS>,
                                      multiplicationTechnique0: MultiplicationTechnique);
        fn SetMultiHopModSize(self: Pin<&mut ParamsBGVRNS>, multiHopModSize0: u32);
        fn SetInteractiveBootCompressionLevel(self: Pin<&mut ParamsBGVRNS>,
                                              interactiveBootCompressionLevel0: COMPRESSION_LEVEL);
    }

    // ParamsCKKSRNS
    unsafe extern "C++"
    {
        fn GetParamsCKKSRNS() -> UniquePtr<ParamsCKKSRNS>;
        fn GetParamsCKKSRNSbyVectorOfString(vals: &CxxVector<CxxString>)
                                            -> UniquePtr<ParamsCKKSRNS>;
        // getters
        fn GetScheme(self: &ParamsCKKSRNS) -> SCHEME;
        fn GetPlaintextModulus(self: &ParamsCKKSRNS) -> u64;
        fn GetDigitSize(self: &ParamsCKKSRNS) -> u32;
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
        fn SetPlaintextModulus(self: Pin<&mut ParamsCKKSRNS>, ptModulus0: u64);
        fn SetDigitSize(self: Pin<&mut ParamsCKKSRNS>, digitSize0: u32);
        fn SetStandardDeviation(self: Pin<&mut ParamsCKKSRNS>, standardDeviation0: f32);
        fn SetSecretKeyDist(self: Pin<&mut ParamsCKKSRNS>, secretKeyDist0: SecretKeyDist);
        fn SetMaxRelinSkDeg(self: Pin<&mut ParamsCKKSRNS>, maxRelinSkDeg0: u32);
        fn SetPREMode(self: Pin<&mut ParamsCKKSRNS>, PREMode0: ProxyReEncryptionMode);
        fn SetMultipartyMode(self: Pin<&mut ParamsCKKSRNS>, multipartyMode0: MultipartyMode);
        fn SetExecutionMode(self: Pin<&mut ParamsCKKSRNS>, executionMode0: ExecutionMode);
        fn SetDecryptionNoiseMode(self: Pin<&mut ParamsCKKSRNS>,
                                  decryptionNoiseMode0: DecryptionNoiseMode);
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
        fn SetEncryptionTechnique(self: Pin<&mut ParamsCKKSRNS>,
                                  encryptionTechnique0: EncryptionTechnique);
        fn SetMultiplicationTechnique(self: Pin<&mut ParamsCKKSRNS>,
                                      multiplicationTechnique0: MultiplicationTechnique);
        fn SetMultiHopModSize(self: Pin<&mut ParamsCKKSRNS>, multiHopModSize0: u32);
        fn SetInteractiveBootCompressionLevel(self: Pin<&mut ParamsCKKSRNS>,
                                              interactiveBootCompressionLevel0: COMPRESSION_LEVEL);
    }

    // PublicKeyDCRTPoly
    unsafe extern "C++"
    {
        fn GenDefaultConstructedPublicKey() -> UniquePtr<PublicKeyDCRTPoly>;
    }

    // KeyPairDCRTPoly
    unsafe extern "C++"
    {
        fn GetPrivateKey(self: &KeyPairDCRTPoly) -> SharedPtr<PrivateKeyImpl>;
        fn GetPublicKey(self: &KeyPairDCRTPoly) -> SharedPtr<PublicKeyImpl>;
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
    // SharedComplex
    struct SharedComplex
    {
        ptr: SharedPtr<Complex>,
    }
    // Vector of SharedComplex
    unsafe extern "C++"
    {
        fn GenVectorOfComplex(vals: &CxxVector<ComplexPair>)
                              -> UniquePtr<CxxVector<SharedComplex>>;
    }

    // CryptoContextDCRTPoly
    unsafe extern "C++"
    {
        fn GenEmptyCryptoContext() -> UniquePtr<CryptoContextDCRTPoly>;
        fn GenCryptoContextByParamsBFVRNS(params: &ParamsBFVRNS)
                                          -> UniquePtr<CryptoContextDCRTPoly>;
        fn GenCryptoContextByParamsBGVRNS(params: &ParamsBGVRNS)
                                          -> UniquePtr<CryptoContextDCRTPoly>;
        fn GenCryptoContextByParamsCKKSRNS(params: &ParamsCKKSRNS)
                                           -> UniquePtr<CryptoContextDCRTPoly>;

        fn Enable(self: &CryptoContextDCRTPoly, feature: PKESchemeFeature);
        fn KeyGen(self: &CryptoContextDCRTPoly) -> UniquePtr<KeyPairDCRTPoly>;
        fn EvalMultKeyGen(self: &CryptoContextDCRTPoly, key: SharedPtr<PrivateKeyImpl>);
        fn EvalRotateKeyGen(self: &CryptoContextDCRTPoly, privateKey: SharedPtr<PrivateKeyImpl>,
                            indexList: &CxxVector<i32>, publicKey: SharedPtr<PublicKeyImpl>);
        fn MakePackedPlaintext(self: &CryptoContextDCRTPoly, value: &CxxVector<i64>,
                               noiseScaleDeg: /* 1 */ usize, level: /* 0 */ u32)
                               -> UniquePtr<Plaintext>;
        fn Encrypt(self: &CryptoContextDCRTPoly, publicKey: SharedPtr<PublicKeyImpl>,
                   plaintext: SharedPtr<PlaintextImpl>) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAdd(self: &CryptoContextDCRTPoly, ciphertext1: SharedPtr<CiphertextImpl>,
                   ciphertext2: SharedPtr<CiphertextImpl>) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSub(self: &CryptoContextDCRTPoly, ciphertext1: SharedPtr<CiphertextImpl>,
                   ciphertext2: SharedPtr<CiphertextImpl>) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMult(self: &CryptoContextDCRTPoly, ciphertext1: SharedPtr<CiphertextImpl>,
                    ciphertext2: SharedPtr<CiphertextImpl>) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultByConst(self: &CryptoContextDCRTPoly, ciphertext: SharedPtr<CiphertextImpl>,
                           constant: f64) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalRotate(self: &CryptoContextDCRTPoly, ciphertext: SharedPtr<CiphertextImpl>,
                      index: i32) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalChebyshevSeries(self: &CryptoContextDCRTPoly, ciphertext: SharedPtr<CiphertextImpl>,
                               coefficients: &CxxVector<f64>, a: f64, b: f64)
                               -> UniquePtr<CiphertextDCRTPoly>;
        fn Decrypt(self: &CryptoContextDCRTPoly, privateKey: SharedPtr<PrivateKeyImpl>,
                   ciphertext: SharedPtr<CiphertextImpl>, plaintext: Pin<&mut Plaintext>)
                   -> UniquePtr<DecryptResult>;
        fn GetRingDimension(self: &CryptoContextDCRTPoly) -> u32;
        fn MakeCKKSPackedPlaintext(self: &CryptoContextDCRTPoly, value: &CxxVector<f64>,
                                   scaleDeg: /* 1 */ usize, level: /* 0 */ u32,
                                   params: /* null() */ SharedPtr<DCRTPolyParams>,
                                   slots: /* 0 */ u32) -> UniquePtr<Plaintext>;
        fn MakeCKKSPackedPlaintextByVectorOfComplex(self: &CryptoContextDCRTPoly,
                                                    value: &CxxVector<SharedComplex>,
                                                    scaleDeg: /* 1 */ usize, level: /* 0 */ u32,
                                                    params: /* null() */ SharedPtr<DCRTPolyParams>,
                                                    slots: /* 0 */ u32) -> UniquePtr<Plaintext>;
        fn EvalPoly(self: &CryptoContextDCRTPoly, ciphertext: SharedPtr<CiphertextImpl>,
                    coefficients: &CxxVector<f64>) -> UniquePtr<CiphertextDCRTPoly>;
    }

    // Serialize / Deserialize
    unsafe extern "C++"
    {
        fn SerializeCryptoContextToFile(ccLocation: &CxxString,
                                        cryptoContext: &CryptoContextDCRTPoly,
                                        serialMode: SerialMode) -> bool;
        fn DeserializeCryptoContextFromFile(ccLocation: &CxxString,
                                            cryptoContext: Pin<&mut CryptoContextDCRTPoly>,
                                            serialMode: SerialMode) -> bool;
        fn SerializeEvalMultKeyToFile(multKeyLocation: &CxxString,
                                      cryptoContext: &CryptoContextDCRTPoly,
                                      serialMode: SerialMode) -> bool;
        fn SerializeEvalMultKeyByIdToFile(multKeyLocation: &CxxString, serialMode: SerialMode,
                                          id: &CxxString) -> bool;
        fn DeserializeEvalMultKeyFromFile(multKeyLocation: &CxxString, serialMode: SerialMode)
                                          -> bool;
        fn SerializeEvalSumKeyToFile(sumKeyLocation: &CxxString,
                                     cryptoContext: &CryptoContextDCRTPoly, serialMode: SerialMode)
                                     -> bool;
        fn SerializeEvalSumKeyByIdToFile(sumKeyLocation: &CxxString, serialMode: SerialMode,
                                         id: &CxxString) -> bool;
        fn DeserializeEvalSumKeyFromFile(sumKeyLocation: &CxxString, serialMode: SerialMode)
                                         -> bool;
        fn SerializeEvalAutomorphismKeyToFile(automorphismKeyLocation: &CxxString,
                                              cryptoContext: &CryptoContextDCRTPoly,
                                              serialMode: SerialMode) -> bool;
        fn SerializeEvalAutomorphismKeyByIdToFile(automorphismKeyLocation: &CxxString,
                                                  serialMode: SerialMode, id: &CxxString) -> bool;
        fn DeserializeEvalAutomorphismKeyFromFile(automorphismKeyLocation: &CxxString,
                                                  serialMode: SerialMode) -> bool;
        fn SerializeCiphertextToFile(ciphertextLocation: &CxxString,
                                     ciphertext: &CiphertextDCRTPoly, serialMode: SerialMode)
                                     -> bool;
        fn DeserializeCiphertextFromFile(ciphertextLocation: &CxxString,
                                         ciphertext: Pin<&mut CiphertextDCRTPoly>,
                                         serialMode: SerialMode) -> bool;
        fn SerializePublicKeyToFile(publicKeyLocation: &CxxString, publicKey: &PublicKeyDCRTPoly,
                                    serialMode: SerialMode) -> bool;
        fn DeserializePublicKeyFromFile(publicKeyLocation: &CxxString,
                                        publicKey: Pin<&mut PublicKeyDCRTPoly>,
                                        serialMode: SerialMode) -> bool;
    }
}

#[cfg(test)]
mod tests
{
    use super::*;

    // TODO: add more tests
    #[test]
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
}
