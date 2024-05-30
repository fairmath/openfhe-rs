#![allow(non_snake_case)]
#![allow(dead_code)]
#![allow(unused_imports)]

use cxx::{CxxVector, SharedPtr, let_cxx_string};
pub use cxx;

#[cxx::bridge(namespace = "openfhe")]
pub mod ffi
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

    #[repr(i32)]
    enum Format
    {
        EVALUATION = 0,
        COEFFICIENT = 1
    }

    struct ComplexPair
    {
        re: f64,
        im: f64,
    }

    unsafe extern "C++"
    {
        include!("openfhe/src/Ciphertext.h");
        include!("openfhe/src/CryptoContext.h");
        include!("openfhe/src/KeyPair.h");
        include!("openfhe/src/Params.h");
        include!("openfhe/src/Plaintext.h");
        include!("openfhe/src/PublicKey.h");
        include!("openfhe/src/SerialDeserial.h");
        include!("openfhe/src/EvalKey.h");
        include!("openfhe/src/LWEPrivateKey.h");
        include!("openfhe/src/VectorOfCiphertexts.h");

        type COMPRESSION_LEVEL;
        type DecryptionNoiseMode;
        type EncryptionTechnique;
        type ExecutionMode;
        type KeySwitchTechnique;
        type MultipartyMode;
        type MultiplicationTechnique;
        type PKESchemeFeature;
        type ProxyReEncryptionMode;
        type ScalingTechnique;
        type SCHEME;
        type SecretKeyDist;
        type SecurityLevel;
        type SerialMode;
        type Format;

        type CiphertextDCRTPoly;
        type CryptoContextDCRTPoly;
        type DCRTPolyParams;
        type DecryptResult;
        type KeyPairDCRTPoly;
        type Params;
        type ParamsBFVRNS;
        type ParamsBGVRNS;
        type ParamsCKKSRNS;
        type Plaintext;
        type PrivateKeyImpl;
        type PublicKeyDCRTPoly;
        type PublicKeyImpl;
        type EvalKeyDCRTPoly;
        type LWEPrivateKey;
        type VectorOfCiphertexts;
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
        fn SetLength(self: &Plaintext, newSize: usize);
        fn GetString(self: &Plaintext) -> String;
        fn GetLogPrecision(self: &Plaintext) -> f64;
        fn SetLevel(self: &Plaintext, l: usize);
        fn IsEncoded(self: &Plaintext) -> bool;
        fn HighBound(self: &Plaintext) -> i64;
        fn LowBound(self: &Plaintext) -> i64;
        fn GetLength(self: &Plaintext) -> usize;
        fn GetLevel(self: &Plaintext) -> usize;
        fn GetLogError(self: &Plaintext) -> f64;
        fn GetNoiseScaleDeg(self: &Plaintext) -> usize;
        fn GetScalingFactor(self: &Plaintext) -> f64;
        fn GetSchemeID(self: &Plaintext) -> SCHEME;
        fn GetSlots(self: &Plaintext) -> u32;
        fn Encode(self: &Plaintext) -> bool;
        fn Decode(self: &Plaintext) -> bool;
        fn SetFormat(self: &Plaintext, fmt: Format);
        fn SetIntVectorValue(self: &Plaintext, val: &CxxVector<i64>);
        fn SetNoiseScaleDeg(self: &Plaintext, nsd: usize);
        fn SetScalingFactor(self: &Plaintext, sf: f64);
        fn SetSlots(self: &Plaintext, s: u32);
        fn SetStringValue(self: &Plaintext, value: &CxxString);
        fn GetPackedValue(self: &Plaintext) -> &CxxVector<i64>;
        fn GetRealPackedValue(self: &Plaintext) -> UniquePtr<CxxVector<f64>>;
        fn GetCoefPackedValue(self: &Plaintext) -> &CxxVector<i64>;
        fn GetStringValue(self: &Plaintext) -> &CxxString;
        fn GetCopyOfCKKSPackedValue(self: &Plaintext) -> UniquePtr<CxxVector<ComplexPair>>;
    }

    // CiphertextDCRTPoly
    unsafe extern "C++"
    {
        fn GenDefaultConstructedCiphertext() -> UniquePtr<CiphertextDCRTPoly>;
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
        fn MultipartyKeyGen(self: &CryptoContextDCRTPoly, publicKey: &PublicKeyDCRTPoly,
                            makeSparse: /* false */ bool, fresh: /* false */ bool)
                            -> UniquePtr<KeyPairDCRTPoly>;
        fn MultiAddPubKeys(self: &CryptoContextDCRTPoly, publicKey1: &PublicKeyDCRTPoly,
                           publicKey2: &PublicKeyDCRTPoly, keyId: /* "" */ &CxxString)
                           -> UniquePtr<PublicKeyDCRTPoly>;
        fn EvalMultKeyGen(self: &CryptoContextDCRTPoly, key: SharedPtr<PrivateKeyImpl>);
        fn EvalMultKeysGen(self: &CryptoContextDCRTPoly, key: SharedPtr<PrivateKeyImpl>);
        fn EvalRotateKeyGen(self: &CryptoContextDCRTPoly, privateKey: SharedPtr<PrivateKeyImpl>,
                            indexList: &CxxVector<i32>,
                            publicKey: /* null() */ SharedPtr<PublicKeyImpl>);
        fn EvalAtIndexKeyGen(self: &CryptoContextDCRTPoly, privateKey: SharedPtr<PrivateKeyImpl>,
                             indexList: &CxxVector<i32>,
                             publicKey: /* null() */ SharedPtr<PublicKeyImpl>);
        fn EvalCKKStoFHEWPrecompute(self: &CryptoContextDCRTPoly, scale: /* 1.0 */ f64);
        fn MakePackedPlaintext(self: &CryptoContextDCRTPoly, value: &CxxVector<i64>,
                               noiseScaleDeg: /* 1 */ usize, level: /* 0 */ u32)
                               -> UniquePtr<Plaintext>;
        fn EncryptByPublicKey(self: &CryptoContextDCRTPoly, publicKey: SharedPtr<PublicKeyImpl>,
                              plaintext: &Plaintext) -> UniquePtr<CiphertextDCRTPoly>;
        fn EncryptByPrivateKey(self: &CryptoContextDCRTPoly, privateKey: SharedPtr<PrivateKeyImpl>,
                               plaintext: &Plaintext) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAddByCiphertexts(self: &CryptoContextDCRTPoly, ciphertext1: &CiphertextDCRTPoly,
                                ciphertext2: &CiphertextDCRTPoly) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAddByCiphertextAndPlaintext(self: &CryptoContextDCRTPoly,
                                           ciphertext: &CiphertextDCRTPoly, plaintext: &Plaintext)
                                           -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAddByPlaintextAndCiphertext(self: &CryptoContextDCRTPoly,
                                           plaintext: &Plaintext, ciphertext: &CiphertextDCRTPoly)
                                           -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAddByConstAndCiphertext(self: &CryptoContextDCRTPoly,
                                       constant: f64, ciphertext: &CiphertextDCRTPoly)
                                       -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAddByCiphertextAndConst(self: &CryptoContextDCRTPoly,
                                       ciphertext: &CiphertextDCRTPoly, constant: f64)
                                       -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAddMutableByCiphertexts(self: &CryptoContextDCRTPoly,
                                       ciphertext1: &CiphertextDCRTPoly,
                                       ciphertext2: &CiphertextDCRTPoly)
                                       -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAddMutableByCiphertextAndPlaintext(self: &CryptoContextDCRTPoly,
                                                  ciphertext: &CiphertextDCRTPoly,
                                                  plaintext: &Plaintext)
                                                  -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAddMutableByPlaintextAndCiphertext(self: &CryptoContextDCRTPoly,
                                                  plaintext: &Plaintext,
                                                  ciphertext: &CiphertextDCRTPoly)
                                                  -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAddInPlaceByCiphertexts(self: &CryptoContextDCRTPoly,
                                       ciphertext1: &CiphertextDCRTPoly,
                                       ciphertext2: &CiphertextDCRTPoly);
        fn EvalAddInPlaceByCiphertextAndPlaintext(self: &CryptoContextDCRTPoly,
                                                  ciphertext: &CiphertextDCRTPoly,
                                                  plaintext: &Plaintext);
        fn EvalAddInPlaceByPlaintextAndCiphertext(self: &CryptoContextDCRTPoly,
                                                  plaintext: &Plaintext,
                                                  ciphertext: &CiphertextDCRTPoly);
        fn EvalAddInPlaceByCiphertextAndConst(self: &CryptoContextDCRTPoly,
                                              ciphertext: &CiphertextDCRTPoly, constant: f64);
        fn EvalAddInPlaceByConstAndCiphertext(self: &CryptoContextDCRTPoly, constant: f64,
                                              ciphertext: &CiphertextDCRTPoly);
        fn EvalAddMutableInPlace(self: &CryptoContextDCRTPoly, ciphertext1: &CiphertextDCRTPoly,
                                 ciphertext2: &CiphertextDCRTPoly);
        fn EvalSubByCiphertexts(self: &CryptoContextDCRTPoly, ciphertext1: &CiphertextDCRTPoly,
                                ciphertext2: &CiphertextDCRTPoly) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSubByCiphertextAndPlaintext(self: &CryptoContextDCRTPoly,
                                           ciphertext: &CiphertextDCRTPoly, plaintext: &Plaintext)
                                           -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSubByPlaintextAndCiphertext(self: &CryptoContextDCRTPoly,
                                           plaintext: &Plaintext, ciphertext: &CiphertextDCRTPoly)
                                           -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSubByConstAndCiphertext(self: &CryptoContextDCRTPoly, constant: f64,
                                       ciphertext: &CiphertextDCRTPoly)
                                       -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSubByCiphertextAndConst(self: &CryptoContextDCRTPoly,
                                       ciphertext: &CiphertextDCRTPoly, constant: f64)
                                       -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSubMutableByCiphertexts(self: &CryptoContextDCRTPoly,
                                       ciphertext1: &CiphertextDCRTPoly,
                                       ciphertext2: &CiphertextDCRTPoly)
                                       -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSubMutableByCiphertextAndPlaintext(self: &CryptoContextDCRTPoly,
                                                  ciphertext: &CiphertextDCRTPoly,
                                                  plaintext: &Plaintext)
                                                  -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSubMutableByPlaintextAndCiphertext(self: &CryptoContextDCRTPoly,
                                                  plaintext: &Plaintext,
                                                  ciphertext: &CiphertextDCRTPoly)
                                                  -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSubInPlaceByCiphertexts(self: &CryptoContextDCRTPoly,
                                       ciphertext1: &CiphertextDCRTPoly,
                                       ciphertext2: &CiphertextDCRTPoly);
        fn EvalSubInPlaceByCiphertextAndConst(self: &CryptoContextDCRTPoly,
                                              ciphertext: &CiphertextDCRTPoly, constant: f64);
        fn EvalSubInPlaceByConstAndCiphertext(self: &CryptoContextDCRTPoly, constant: f64,
                                              ciphertext: &CiphertextDCRTPoly);
        fn EvalSubMutableInPlace(self: &CryptoContextDCRTPoly, ciphertext1: &CiphertextDCRTPoly,
                                 ciphertext2: &CiphertextDCRTPoly);
        fn EvalMultByCiphertexts(self: &CryptoContextDCRTPoly, ciphertext1: &CiphertextDCRTPoly,
                                 ciphertext2: &CiphertextDCRTPoly)
                                 -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultByCiphertextAndPlaintext(self: &CryptoContextDCRTPoly,
                                            ciphertext: &CiphertextDCRTPoly, plaintext: &Plaintext)
                                            -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultByPlaintextAndCiphertext(self: &CryptoContextDCRTPoly, plaintext: &Plaintext,
                                            ciphertext: &CiphertextDCRTPoly)
                                            -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultByConstAndCiphertext(self: &CryptoContextDCRTPoly, constant: f64,
                                        ciphertext: &CiphertextDCRTPoly)
                                        -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultByCiphertextAndConst(self: &CryptoContextDCRTPoly,
                                        ciphertext: &CiphertextDCRTPoly, constant: f64)
                                        -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultMutableByCiphertexts(self: &CryptoContextDCRTPoly,
                                       ciphertext1: &CiphertextDCRTPoly,
                                       ciphertext2: &CiphertextDCRTPoly)
                                       -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultMutableByCiphertextAndPlaintext(self: &CryptoContextDCRTPoly,
                                                  ciphertext: &CiphertextDCRTPoly,
                                                  plaintext: &Plaintext)
                                                  -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultMutableByPlaintextAndCiphertext(self: &CryptoContextDCRTPoly,
                                                  plaintext: &Plaintext,
                                                  ciphertext: &CiphertextDCRTPoly)
                                                  -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultInPlaceByCiphertextAndConst(self: &CryptoContextDCRTPoly,
                                               ciphertext: &CiphertextDCRTPoly, constant: f64);
        fn EvalMultInPlaceByConstAndCiphertext(self: &CryptoContextDCRTPoly, constant: f64,
                                               ciphertext: &CiphertextDCRTPoly);
        fn EvalMultMutableInPlace(self: &CryptoContextDCRTPoly, ciphertext1: &CiphertextDCRTPoly,
                                 ciphertext2: &CiphertextDCRTPoly);
        fn EvalMultNoRelin(self: &CryptoContextDCRTPoly, ciphertext1: &CiphertextDCRTPoly,
                           ciphertext2: &CiphertextDCRTPoly) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultAndRelinearize(self: &CryptoContextDCRTPoly, ciphertext1: &CiphertextDCRTPoly,
                                  ciphertext2: &CiphertextDCRTPoly)
                                  -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalRotate(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly, index: i32)
                      -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalChebyshevSeries(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly,
                               coefficients: &CxxVector<f64>, a: f64, b: f64)
                               -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalChebyshevFunction(self: &CryptoContextDCRTPoly, func: fn(f64, ret: &mut f64),
                                 ciphertext: &CiphertextDCRTPoly, a: f64, b: f64, degree: u32)
                                 -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalBootstrap(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly,
                         numIterations: /* 1 */ u32, precision: /* 0 */ u32)
                         -> UniquePtr<CiphertextDCRTPoly>;
        fn Rescale(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly)
                   -> UniquePtr<CiphertextDCRTPoly>;
        fn RescaleInPlace(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly);
        fn ModReduce(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly)
                     -> UniquePtr<CiphertextDCRTPoly>;
        fn ModReduceInPlace(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly);
        fn EvalSum(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly, batchSize: u32)
                   -> UniquePtr<CiphertextDCRTPoly>;
        fn IntMPBootAdjustScale(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly)
                                -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalLogistic(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly, a: f64,
                        b: f64, degree: u32) -> UniquePtr<CiphertextDCRTPoly>;
        fn IntMPBootRandomElementGen(self: &CryptoContextDCRTPoly, publicKey: &PublicKeyDCRTPoly)
                                     -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalBootstrapSetup(self: &CryptoContextDCRTPoly,
                              levelBudget: /* {5, 4} */ &CxxVector<u32>,
                              dim1: /* {0, 0} */ &CxxVector<u32>, slots: /* 0 */ u32,
                              correctionFactor: /* 0 */ u32, precompute: /* true */ bool);
        fn EvalBootstrapKeyGen(self: &CryptoContextDCRTPoly, privateKey: SharedPtr<PrivateKeyImpl>,
                               slots: u32);
        fn DecryptByPrivateKeyAndCiphertext(self: &CryptoContextDCRTPoly,
                                            privateKey: SharedPtr<PrivateKeyImpl>,
                                            ciphertext: &CiphertextDCRTPoly,
                                            plaintext: Pin<&mut Plaintext>)
                                            -> UniquePtr<DecryptResult>;
        fn DecryptByCiphertextAndPrivateKey(self: &CryptoContextDCRTPoly,
                                            ciphertext: &CiphertextDCRTPoly,
                                            privateKey: SharedPtr<PrivateKeyImpl>,
                                            plaintext: Pin<&mut Plaintext>)
                                            -> UniquePtr<DecryptResult>;
        fn GetRingDimension(self: &CryptoContextDCRTPoly) -> u32;
        fn GetCyclotomicOrder(self: &CryptoContextDCRTPoly) -> u32;
        fn MakeStringPlaintext(self: &CryptoContextDCRTPoly, s: &CxxString)
                               -> UniquePtr<Plaintext>;
        fn MakeCoefPackedPlaintext(self: &CryptoContextDCRTPoly, value: &CxxVector<i64>,
                                   noiseScaleDeg: /* 1 */ usize, level: /* 0 */ u32)
                                   -> UniquePtr<Plaintext>;
        fn MakeCKKSPackedPlaintext(self: &CryptoContextDCRTPoly, value: &CxxVector<f64>,
                                   scaleDeg: /* 1 */ usize, level: /* 0 */ u32,
                                   params: /* null() */ SharedPtr<DCRTPolyParams>,
                                   slots: /* 0 */ u32) -> UniquePtr<Plaintext>;
        fn MakeCKKSPackedPlaintextByVectorOfComplex(self: &CryptoContextDCRTPoly,
                                                    value: &CxxVector<ComplexPair>,
                                                    scaleDeg: /* 1 */ usize, level: /* 0 */ u32,
                                                    params: /* null() */ SharedPtr<DCRTPolyParams>,
                                                    slots: /* 0 */ u32) -> UniquePtr<Plaintext>;
        fn EvalPoly(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly,
                    coefficients: &CxxVector<f64>) -> UniquePtr<CiphertextDCRTPoly>;
        fn SetSchemeId(self: &CryptoContextDCRTPoly, schemeTag: SCHEME);
        fn GetSchemeId(self: &CryptoContextDCRTPoly) -> SCHEME;
        fn GetKeyGenLevel(self: &CryptoContextDCRTPoly) -> usize;
        fn SetKeyGenLevel(self: &CryptoContextDCRTPoly, level: usize);
        fn SetSwkFC(self: &CryptoContextDCRTPoly, FHEWtoCKKSswk: &CiphertextDCRTPoly);
        fn EvalCompareSwitchPrecompute(self: &CryptoContextDCRTPoly, pLWE: u32, scaleSign: f64,
                                       unit: bool);
        fn FindAutomorphismIndex(self: &CryptoContextDCRTPoly, idx: u32) -> u32;
        fn GetSwkFC(self: &CryptoContextDCRTPoly) -> UniquePtr<CiphertextDCRTPoly>;
        fn EnableByMask(self: &CryptoContextDCRTPoly, featureMask: u32);
        fn SparseKeyGen(self: &CryptoContextDCRTPoly) -> UniquePtr<KeyPairDCRTPoly>;
        fn EvalPolyLinear(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly,
                          coefficients: &CxxVector<f64>)-> UniquePtr<CiphertextDCRTPoly>;
        fn EvalPolyPS(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly,
                      coefficients: &CxxVector<f64>) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalChebyshevSeriesLinear(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly,
                                     coefficients: &CxxVector<f64>, a: f64, b: f64)
                                     -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalChebyshevSeriesPS(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly,
                                 coefficients: &CxxVector<f64>, a: f64, b: f64)
                                 -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalDivide(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly, a: f64,
                      b: f64, degree: u32) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSin(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly, a: f64, b: f64,
                   degree: u32) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalCos(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly, a: f64, b: f64,
                   degree: u32) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalNegate(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly)
                      -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalNegateInPlace(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly);
        fn EvalSquare(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly)
                      -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSquareMutable(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly)
                             -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSquareInPlace(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly);
        fn EvalAtIndex(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly, index: u32)
                       -> UniquePtr<CiphertextDCRTPoly>;
        fn ComposedEvalMult(self: &CryptoContextDCRTPoly, ciphertext1: &CiphertextDCRTPoly,
                            ciphertext2: &CiphertextDCRTPoly) -> UniquePtr<CiphertextDCRTPoly>;
        fn Relinearize(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly)
                       -> UniquePtr<CiphertextDCRTPoly>;
        fn RelinearizeInPlace(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly);
        fn KeySwitchDown(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly)
                         -> UniquePtr<CiphertextDCRTPoly>;
        fn KeySwitchExt(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly,
                        addFirst: bool) -> UniquePtr<CiphertextDCRTPoly>;
        fn Compress(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly,
                    towersLeft: /* 1 */ u32) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalCompareSchemeSwitching(self: &CryptoContextDCRTPoly,
                                      ciphertext1: &CiphertextDCRTPoly,
                                      ciphertext2: &CiphertextDCRTPoly, numCtxts: /* 0 */ u32,
                                      numSlots: /* 0 */ u32, pLWE: /* 0 */ u32,
                                      scaleSign: /* 1.0 */ f64, unit: /* false */ bool)
                                      -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalBootstrapPrecompute(self: &CryptoContextDCRTPoly, slots: /* 0 */ u32);
        fn FindAutomorphismIndices(self: &CryptoContextDCRTPoly, idxList: &CxxVector<u32>)
                                   -> UniquePtr<CxxVector<u32>>;
        fn EvalInnerProductByCiphertexts(self: &CryptoContextDCRTPoly,
                                         ciphertext1: &CiphertextDCRTPoly,
                                         ciphertext2: &CiphertextDCRTPoly, batchSize: u32)
                                         -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalInnerProductByPlaintext(self: &CryptoContextDCRTPoly,
                                       ciphertext: &CiphertextDCRTPoly, plaintext: &Plaintext,
                                       batchSize: u32) -> UniquePtr<CiphertextDCRTPoly>;
        fn KeySwitch(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly,
                     evalKey: &EvalKeyDCRTPoly) -> UniquePtr<CiphertextDCRTPoly>;
        fn KeySwitchInPlace(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly,
                            evalKey: &EvalKeyDCRTPoly);
        fn LevelReduce(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly,
                       evalKey: &EvalKeyDCRTPoly, levels: /* 1 */ usize)
                       -> UniquePtr<CiphertextDCRTPoly>;
        fn LevelReduceInPlace(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly,
                              evalKey: &EvalKeyDCRTPoly, levels: /* 1 */ usize);
        fn ReEncrypt(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly,
                     evalKey: &EvalKeyDCRTPoly, publicKey: /* null() */ SharedPtr<PublicKeyImpl>)
                     -> UniquePtr<CiphertextDCRTPoly>;
        fn KeySwitchGen(self: &CryptoContextDCRTPoly, oldPrivateKey: SharedPtr<PrivateKeyImpl>,
                        newPrivateKey: SharedPtr<PrivateKeyImpl>) -> UniquePtr<EvalKeyDCRTPoly>;
        fn ReKeyGen(self: &CryptoContextDCRTPoly, oldPrivateKey: SharedPtr<PrivateKeyImpl>,
                    newPublicKey: SharedPtr<PublicKeyImpl>) -> UniquePtr<EvalKeyDCRTPoly>;
        fn MultiKeySwitchGen(self: &CryptoContextDCRTPoly,
                             originalPrivateKey: SharedPtr<PrivateKeyImpl>,
                             newPrivateKey: SharedPtr<PrivateKeyImpl>, evalKey: &EvalKeyDCRTPoly)
                             -> UniquePtr<EvalKeyDCRTPoly>;
        fn MultiAddEvalKeys(self: &CryptoContextDCRTPoly, evalKey1: &EvalKeyDCRTPoly,
                            evalKey2: &EvalKeyDCRTPoly, keyId: /* "" */ &CxxString)
                            -> UniquePtr<EvalKeyDCRTPoly>;
        fn MultiMultEvalKey(self: &CryptoContextDCRTPoly, privateKey: SharedPtr<PrivateKeyImpl>,
                            evalKey: &EvalKeyDCRTPoly, keyId: /* "" */ &CxxString)
                            -> UniquePtr<EvalKeyDCRTPoly>;
        fn MultiAddEvalMultKeys(self: &CryptoContextDCRTPoly, evalKey1: &EvalKeyDCRTPoly,
                                evalKey2: &EvalKeyDCRTPoly, keyId: /* "" */ &CxxString)
                                -> UniquePtr<EvalKeyDCRTPoly>;
        fn EvalSumKeyGen(self: &CryptoContextDCRTPoly, privateKey: SharedPtr<PrivateKeyImpl>,
                         publicKey: /* null() */ SharedPtr<PublicKeyImpl>);
        fn EvalCKKStoFHEWKeyGen(self: &CryptoContextDCRTPoly, keyPair: &KeyPairDCRTPoly,
                                lwesk: &LWEPrivateKey);
        fn EvalFHEWtoCKKSKeyGen(self: &CryptoContextDCRTPoly, keyPair: &KeyPairDCRTPoly,
                                lwesk: &LWEPrivateKey, numSlots: /* 0 */ u32,
                                numCtxts: /* 0 */ u32, dim1: /* 0 */ u32, L: /* 0 */ u32);
        fn EvalSchemeSwitchingKeyGen(self: &CryptoContextDCRTPoly, keyPair: &KeyPairDCRTPoly,
                                     lwesk: &LWEPrivateKey);
        fn GetModulus(self: &CryptoContextDCRTPoly) -> u64;
        fn GetRootOfUnity(self: &CryptoContextDCRTPoly) -> u64;
        fn MultipartyDecryptLead(self: &CryptoContextDCRTPoly, ciphertextVec: &VectorOfCiphertexts,
                                 privateKey: SharedPtr<PrivateKeyImpl>)
                                 -> UniquePtr<VectorOfCiphertexts>;
        fn MultipartyDecryptMain(self: &CryptoContextDCRTPoly, ciphertextVec: &VectorOfCiphertexts,
                                 privateKey: SharedPtr<PrivateKeyImpl>)
                                 -> UniquePtr<VectorOfCiphertexts>;
        fn IntMPBootDecrypt(self: &CryptoContextDCRTPoly, privateKey: SharedPtr<PrivateKeyImpl>,
                            ciphertext: &CiphertextDCRTPoly, a: &CiphertextDCRTPoly)
                            -> UniquePtr<VectorOfCiphertexts>;
        fn EvalMinSchemeSwitching(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly,
                                  publicKey: &PublicKeyDCRTPoly, numValues: /* 0 */ u32,
                                  numSlots: /* 0 */ u32, pLWE: /* 0 */ u32,
                                  scaleSign: /* 1.0 */ f64) -> UniquePtr<VectorOfCiphertexts>;
        fn EvalMinSchemeSwitchingAlt(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly,
                                     publicKey: &PublicKeyDCRTPoly, numValues: /* 0 */ u32,
                                     numSlots: /* 0 */ u32, pLWE: /* 0 */ u32,
                                     scaleSign: /* 1.0 */ f64) -> UniquePtr<VectorOfCiphertexts>;
        fn EvalMaxSchemeSwitching(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly,
                                  publicKey: &PublicKeyDCRTPoly, numValues: /* 0 */ u32,
                                  numSlots: /* 0 */ u32, pLWE: /* 0 */ u32,
                                  scaleSign: /* 1.0 */ f64) -> UniquePtr<VectorOfCiphertexts>;
        fn EvalMaxSchemeSwitchingAlt(self: &CryptoContextDCRTPoly, ciphertext: &CiphertextDCRTPoly,
                                     publicKey: &PublicKeyDCRTPoly, numValues: /* 0 */ u32,
                                     numSlots: /* 0 */ u32, pLWE: /* 0 */ u32,
                                     scaleSign: /* 1.0 */ f64) -> UniquePtr<VectorOfCiphertexts>;
        fn EvalAddMany(self: &CryptoContextDCRTPoly, ciphertextVec: &VectorOfCiphertexts)
                       -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultMany(self: &CryptoContextDCRTPoly, ciphertextVec: &VectorOfCiphertexts)
                        -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMerge(self: &CryptoContextDCRTPoly, ciphertextVec: &VectorOfCiphertexts)
                     -> UniquePtr<CiphertextDCRTPoly>;
        fn IntMPBootEncrypt(self: &CryptoContextDCRTPoly, publicKey: &PublicKeyDCRTPoly,
                            sharesPair: &VectorOfCiphertexts, a: &CiphertextDCRTPoly,
                            ciphertext: &CiphertextDCRTPoly) -> UniquePtr<CiphertextDCRTPoly>;

        // cxx currently does not support static class methods
        fn ClearEvalMultKeys();
        fn ClearEvalMultKeysById(id: &CxxString);
        fn ClearEvalMultKeysByCryptoContext(cryptoContext: &CryptoContextDCRTPoly);
        fn ClearEvalSumKeys();
        fn ClearEvalSumKeysById(id: &CxxString);
        fn ClearEvalSumKeysByCryptoContext(cryptoContext: &CryptoContextDCRTPoly);
        fn ClearEvalAutomorphismKeys();
        fn ClearEvalAutomorphismKeysById(id: &CxxString);
        fn ClearEvalAutomorphismKeysByCryptoContext(cryptoContext: &CryptoContextDCRTPoly);
        fn GetExistingEvalAutomorphismKeyIndices(keyTag: &CxxString) -> UniquePtr<CxxVector<u32>>;
        fn GetUniqueValues(oldValues: &CxxVector<u32>, newValues: &CxxVector<u32>)
                           -> UniquePtr<CxxVector<u32>>;
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

        let _cc = ffi::GenCryptoContextByParamsBFVRNS(&_cc_params_bfvrns);
        _cc.Enable(ffi::PKESchemeFeature::PKE);
        _cc.Enable(ffi::PKESchemeFeature::KEYSWITCH);
        _cc.Enable(ffi::PKESchemeFeature::LEVELEDSHE);

        let _key_pair = _cc.KeyGen();
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
        let _plain_text_1 = _cc.MakePackedPlaintext(&_vector_of_ints_1, 1, 0);

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
        let _plain_text_2 = _cc.MakePackedPlaintext(&_vector_of_ints_2, 1, 0);

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
        let _plain_text_3 = _cc.MakePackedPlaintext(&_vector_of_ints_3, 1, 0);

        let _cipher_text_1 = _cc.EncryptByPublicKey(_key_pair.GetPublicKey(), &_plain_text_1);
        let _cipher_text_2 = _cc.EncryptByPublicKey(_key_pair.GetPublicKey(), &_plain_text_2);
        let _cipher_text_3 = _cc.EncryptByPublicKey(_key_pair.GetPublicKey(), &_plain_text_3);

        let _cipher_text_add_1_2 = _cc.EvalAddByCiphertexts(&_cipher_text_1, &_cipher_text_2);
        let _cipher_text_add_result = _cc.EvalAddByCiphertexts(&_cipher_text_add_1_2, &_cipher_text_3);

        let _cipher_text_mul_1_2 = _cc.EvalMultByCiphertexts(&_cipher_text_1, &_cipher_text_2);
        let _cipher_text_mult_result = _cc.EvalMultByCiphertexts(&_cipher_text_mul_1_2, &_cipher_text_3);

        let _cipher_text_rot_1 = _cc.EvalRotate(&_cipher_text_1, 1);
        let _cipher_text_rot_2 = _cc.EvalRotate(&_cipher_text_1, 2);
        let _cipher_text_rot_3 = _cc.EvalRotate(&_cipher_text_1, -1);
        let _cipher_text_rot_4 = _cc.EvalRotate(&_cipher_text_1, -2);

        let mut _plain_text_add_result = ffi::GenEmptyPlainText();
        _cc.DecryptByPrivateKeyAndCiphertext(_key_pair.GetPrivateKey(), &_cipher_text_add_result, _plain_text_add_result.pin_mut());
        let mut _plain_text_mult_result = ffi::GenEmptyPlainText();
        _cc.DecryptByPrivateKeyAndCiphertext(_key_pair.GetPrivateKey(), &_cipher_text_mult_result, _plain_text_mult_result.pin_mut());
        let mut _plain_text_rot_1 = ffi::GenEmptyPlainText();
        _cc.DecryptByPrivateKeyAndCiphertext(_key_pair.GetPrivateKey(), &_cipher_text_rot_1, _plain_text_rot_1.pin_mut());
        let mut _plain_text_rot_2 = ffi::GenEmptyPlainText();
        _cc.DecryptByPrivateKeyAndCiphertext(_key_pair.GetPrivateKey(), &_cipher_text_rot_2, _plain_text_rot_2.pin_mut());
        let mut _plain_text_rot_3 = ffi::GenEmptyPlainText();
        _cc.DecryptByPrivateKeyAndCiphertext(_key_pair.GetPrivateKey(), &_cipher_text_rot_3, _plain_text_rot_3.pin_mut());
        let mut _plain_text_rot_4 = ffi::GenEmptyPlainText();
        _cc.DecryptByPrivateKeyAndCiphertext(_key_pair.GetPrivateKey(), &_cipher_text_rot_4, _plain_text_rot_4.pin_mut());

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

    #[test]
    fn SimpleRealNumbersExample()
    {
        let _mult_depth: u32 = 1;
        let _scale_mod_size: u32 = 50;
        let _batch_size: u32 = 8;

        let mut _cc_params_ckksrns = ffi::GetParamsCKKSRNS();
        _cc_params_ckksrns.pin_mut().SetMultiplicativeDepth(_mult_depth);
        _cc_params_ckksrns.pin_mut().SetScalingModSize(_scale_mod_size);
        _cc_params_ckksrns.pin_mut().SetBatchSize(_batch_size);

        let _cc = ffi::GenCryptoContextByParamsCKKSRNS(&_cc_params_ckksrns);
        _cc.Enable(ffi::PKESchemeFeature::PKE);
        _cc.Enable(ffi::PKESchemeFeature::KEYSWITCH);
        _cc.Enable(ffi::PKESchemeFeature::LEVELEDSHE);

        println!("CKKS scheme is using ring dimension {}\n", _cc.GetRingDimension());

        let _key_pair = _cc.KeyGen();
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

        let _p_txt_1 = _cc.MakeCKKSPackedPlaintext(&_x_1, 1, 0, SharedPtr::<ffi::DCRTPolyParams>::null(), 0);
        let _p_txt_2 = _cc.MakeCKKSPackedPlaintext(&_x_2, 1, 0, SharedPtr::<ffi::DCRTPolyParams>::null(), 0);

        println!("Input x1: {}", _p_txt_1.GetString());
        println!("Input x2: {}", _p_txt_2.GetString());

        let _c1 = _cc.EncryptByPublicKey(_key_pair.GetPublicKey(), &_p_txt_1);
        let _c2 = _cc.EncryptByPublicKey(_key_pair.GetPublicKey(), &_p_txt_2);

        let _c_add = _cc.EvalAddByCiphertexts(&_c1, &_c2);
        let _c_sub = _cc.EvalSubByCiphertexts(&_c1, &_c2);
        let _c_scalar = _cc.EvalMultByCiphertextAndConst(&_c1, 4.0);
        let _c_mul = _cc.EvalMultByCiphertexts(&_c1, &_c2);
        let _c_rot_1 = _cc.EvalRotate(&_c1, 1);
        let _c_rot_2 = _cc.EvalRotate(&_c1, -2);

        let mut _result = ffi::GenEmptyPlainText();
        println!("\nResults of homomorphic computations:");

        _cc.DecryptByPrivateKeyAndCiphertext(_key_pair.GetPrivateKey(), &_c1, _result.pin_mut());
        _result.SetLength(_batch_size.try_into().unwrap());
        println!("x1 = {}Estimated precision in bits: {}", _result.GetString(), _result.GetLogPrecision());

        _cc.DecryptByPrivateKeyAndCiphertext(_key_pair.GetPrivateKey(), &_c_add, _result.pin_mut());
        _result.SetLength(_batch_size.try_into().unwrap());
        println!("x1 + x2 = {}Estimated precision in bits: {}",_result.GetString(), _result.GetLogPrecision());

        _cc.DecryptByPrivateKeyAndCiphertext(_key_pair.GetPrivateKey(), &_c_sub, _result.pin_mut());
        _result.SetLength(_batch_size.try_into().unwrap());
        println!("x1 - x2 = {}", _result.GetString());

        _cc.DecryptByPrivateKeyAndCiphertext(_key_pair.GetPrivateKey(), &_c_scalar, _result.pin_mut());
        _result.SetLength(_batch_size.try_into().unwrap());
        println!("4 * x1 = {}", _result.GetString());

        _cc.DecryptByPrivateKeyAndCiphertext(_key_pair.GetPrivateKey(), &_c_mul, _result.pin_mut());
        _result.SetLength(_batch_size.try_into().unwrap());
        println!("x1 * x2 = {}", _result.GetString());

        _cc.DecryptByPrivateKeyAndCiphertext(_key_pair.GetPrivateKey(), &_c_rot_1, _result.pin_mut());
        _result.SetLength(_batch_size.try_into().unwrap());
        println!("\nIn rotations, very small outputs (~10^-10 here) correspond to 0's:");
        println!("x1 rotate by 1 = {}", _result.GetString());

        _cc.DecryptByPrivateKeyAndCiphertext(_key_pair.GetPrivateKey(), &_c_rot_2, _result.pin_mut());
        _result.SetLength(_batch_size.try_into().unwrap());
        println!("x1 rotate by -2 = {}", _result.GetString());
    }

    #[test]
    fn PolynomialEvaluationExample()
    {
        use std::time::Instant;
        println!("\n======EXAMPLE FOR EVALPOLY========\n");

        let mut _cc_params_ckksrns = ffi::GetParamsCKKSRNS();
        _cc_params_ckksrns.pin_mut().SetMultiplicativeDepth(6);
        _cc_params_ckksrns.pin_mut().SetScalingModSize(50);

        let _cc = ffi::GenCryptoContextByParamsCKKSRNS(&_cc_params_ckksrns);
        _cc.Enable(ffi::PKESchemeFeature::PKE);
        _cc.Enable(ffi::PKESchemeFeature::KEYSWITCH);
        _cc.Enable(ffi::PKESchemeFeature::LEVELEDSHE);
        _cc.Enable(ffi::PKESchemeFeature::ADVANCEDSHE);

        let mut _input = CxxVector::<ffi::ComplexPair>::new();
        _input.pin_mut().push(ffi::ComplexPair{re: 0.5, im: 0.0});
        _input.pin_mut().push(ffi::ComplexPair{re: 0.7, im: 0.0});
        _input.pin_mut().push(ffi::ComplexPair{re: 0.9, im: 0.0});
        _input.pin_mut().push(ffi::ComplexPair{re: 0.95, im: 0.0});
        _input.pin_mut().push(ffi::ComplexPair{re: 0.93, im: 0.0});
        let _encoded_length = _input.len();

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

        let _plain_text_1 = _cc.MakeCKKSPackedPlaintextByVectorOfComplex(&_input, 1, 0, SharedPtr::<ffi::DCRTPolyParams>::null(), 0);
        let _key_pair = _cc.KeyGen();
        print!("Generating evaluation key for homomorphic multiplication...");
        _cc.EvalMultKeyGen(_key_pair.GetPrivateKey());
        println!("Completed.\n");
        let _cipher_text_1 = _cc.EncryptByPublicKey(_key_pair.GetPublicKey(), &_plain_text_1);

        let mut _start = Instant::now();
        let _result = _cc.EvalPoly(&_cipher_text_1, &_coefficients_1);
        let _time_eval_poly_1 = _start.elapsed();

        _start = Instant::now();
        let _result_2 = _cc.EvalPoly(&_cipher_text_1, &_coefficients_2);
        let _time_eval_poly_2 = _start.elapsed();

        let mut _plain_text_dec = ffi::GenEmptyPlainText();
        _cc.DecryptByPrivateKeyAndCiphertext(_key_pair.GetPrivateKey(), &_result, _plain_text_dec.pin_mut());
        _plain_text_dec.SetLength(_encoded_length);
        let mut _plain_text_dec_2 = ffi::GenEmptyPlainText();
        _cc.DecryptByPrivateKeyAndCiphertext(_key_pair.GetPrivateKey(), &_result_2, _plain_text_dec_2.pin_mut());
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
}
