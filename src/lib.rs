#![allow(dead_code)]
#![allow(non_snake_case)]
#![allow(unused_imports)]

pub use cxx;
use cxx::{let_cxx_string, CxxVector};

#[cxx::bridge(namespace = "openfhe")]
pub mod ffi {
    #[repr(i32)]
    enum COMPRESSION_LEVEL {
        COMPACT = 2,
        SLACK = 3,
    }

    #[repr(i32)]
    enum DecryptionNoiseMode {
        FIXED_NOISE_DECRYPT = 0,
        NOISE_FLOODING_DECRYPT,
    }

    #[repr(i32)]
    enum EncryptionTechnique {
        STANDARD = 0,
        EXTENDED,
    }

    #[repr(i32)]
    enum ExecutionMode {
        EXEC_EVALUATION = 0,
        EXEC_NOISE_ESTIMATION,
    }

    #[repr(i32)]
    enum Format {
        EVALUATION = 0,
        COEFFICIENT = 1,
    }

    #[repr(i32)]
    enum KeySwitchTechnique {
        INVALID_KS_TECH = 0,
        BV,
        HYBRID,
    }

    #[repr(i32)]
    enum MultipartyMode {
        INVALID_MULTIPARTY_MODE = 0,
        FIXED_NOISE_MULTIPARTY,
        NOISE_FLOODING_MULTIPARTY,
    }

    #[repr(i32)]
    enum MultiplicationTechnique {
        BEHZ = 0,
        HPS,
        HPSPOVERQ,
        HPSPOVERQLEVELED,
    }

    #[repr(i32)]
    enum PKESchemeFeature {
        PKE = 0x01,
        KEYSWITCH = 0x02,
        PRE = 0x04,
        LEVELEDSHE = 0x08,
        ADVANCEDSHE = 0x10,
        MULTIPARTY = 0x20,
        FHE = 0x40,
        SCHEMESWITCH = 0x80,
    }

    #[repr(i32)]
    enum PlaintextEncodings {
        INVALID_ENCODING = 0,
        COEF_PACKED_ENCODING,
        PACKED_ENCODING,
        STRING_ENCODING,
        CKKS_PACKED_ENCODING,
    }

    #[repr(i32)]
    enum ProxyReEncryptionMode {
        NOT_SET = 0,
        INDCPA,
        FIXED_NOISE_HRA,
        NOISE_FLOODING_HRA,
    }

    #[repr(i32)]
    enum ScalingTechnique {
        FIXEDMANUAL = 0,
        FIXEDAUTO,
        FLEXIBLEAUTO,
        FLEXIBLEAUTOEXT,
        NORESCALE,
        INVALID_RS_TECHNIQUE,
    }

    #[repr(i32)]
    enum SCHEME {
        INVALID_SCHEME = 0,
        CKKSRNS_SCHEME,
        BFVRNS_SCHEME,
        BGVRNS_SCHEME,
    }

    #[repr(i32)]
    enum SecretKeyDist {
        GAUSSIAN = 0,
        UNIFORM_TERNARY = 1,
        SPARSE_TERNARY = 2,
    }

    #[repr(i32)]
    enum SecurityLevel {
        HEStd_128_classic,
        HEStd_192_classic,
        HEStd_256_classic,
        HEStd_128_quantum,
        HEStd_192_quantum,
        HEStd_256_quantum,
        HEStd_NotSet,
    }

    #[repr(i32)]
    enum SerialMode {
        BINARY = 0,
        JSON = 1,
    }

    struct ComplexPair {
        re: f64,
        im: f64,
    }

    unsafe extern "C++" {
        // includes
        include!("openfhe/src/AssociativeContainers.h");
        include!("openfhe/src/Ciphertext.h");
        include!("openfhe/src/CryptoContext.h");
        include!("openfhe/src/CryptoParametersBase.h");
        include!("openfhe/src/DCRTPoly.h");
        include!("openfhe/src/DecryptResult.h");
        include!("openfhe/src/EncodingParams.h");
        include!("openfhe/src/EvalKey.h");
        include!("openfhe/src/KeyPair.h");
        include!("openfhe/src/LWEPrivateKey.h");
        include!("openfhe/src/Matrix.h");
        include!("openfhe/src/Params.h");
        include!("openfhe/src/Plaintext.h");
        include!("openfhe/src/PrivateKey.h");
        include!("openfhe/src/PublicKey.h");
        include!("openfhe/src/SchemeBase.h");
        include!("openfhe/src/SequenceContainers.h");
        include!("openfhe/src/SerialDeserial.h");
        include!("openfhe/src/TrapdoorPair.h");

        // enums
        type COMPRESSION_LEVEL;
        type DecryptionNoiseMode;
        type EncryptionTechnique;
        type ExecutionMode;
        type Format;
        type KeySwitchTechnique;
        type MultipartyMode;
        type MultiplicationTechnique;
        type PKESchemeFeature;
        type PlaintextEncodings;
        type ProxyReEncryptionMode;
        type ScalingTechnique;
        type SCHEME;
        type SecretKeyDist;
        type SecurityLevel;
        type SerialMode;

        // types
        type CiphertextDCRTPoly;
        type CryptoContextDCRTPoly;
        type CryptoParametersBaseDCRTPoly;
        type DCRTPoly;
        type DCRTPolyParams;
        type DecryptResult;
        type EncodingParams;
        type EvalKeyDCRTPoly;
        type KeyPairDCRTPoly;
        type LWEPrivateKey;
        type MapFromIndexToEvalKey;
        type MapFromStringToMapFromIndexToEvalKey;
        type MapFromStringToVectorOfEvalKeys;
        type Params;
        type ParamsBFVRNS;
        type ParamsBGVRNS;
        type ParamsCKKSRNS;
        type Plaintext;
        type PrivateKeyDCRTPoly;
        type PublicKeyDCRTPoly;
        type SchemeBaseDCRTPoly;
        type SetOfUints;
        type UnorderedMapFromIndexToDCRTPoly;
        type VectorOfCiphertexts;
        type VectorOfDCRTPolys;
        type VectorOfEvalKeys;
        type VectorOfLWECiphertexts;
        type VectorOfPrivateKeys;
        type VectorOfVectorOfCiphertexts;
        type RLWETrapdoorPairDRCTPoly;
        type MatrixDCRTPoly;
    }

    // CiphertextDCRTPoly
    unsafe extern "C++" {
        // Generator functions
        fn DCRTPolyGenNullCiphertext() -> UniquePtr<CiphertextDCRTPoly>;
    }

    // CryptoContextDCRTPoly
    unsafe extern "C++" {
        fn ComposedEvalMult(
            self: &CryptoContextDCRTPoly,
            ciphertext1: &CiphertextDCRTPoly,
            ciphertext2: &CiphertextDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn Compress(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            towersLeft: /* 1 */ u32,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn DecryptByCiphertextAndPrivateKey(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            privateKey: &PrivateKeyDCRTPoly,
            plaintext: Pin<&mut Plaintext>,
        ) -> UniquePtr<DecryptResult>;
        fn DecryptByPrivateKeyAndCiphertext(
            self: &CryptoContextDCRTPoly,
            privateKey: &PrivateKeyDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            plaintext: Pin<&mut Plaintext>,
        ) -> UniquePtr<DecryptResult>;
        fn EnableByFeature(self: &CryptoContextDCRTPoly, feature: PKESchemeFeature);
        fn EnableByMask(self: &CryptoContextDCRTPoly, featureMask: u32);
        fn EncryptByPrivateKey(
            self: &CryptoContextDCRTPoly,
            privateKey: &PrivateKeyDCRTPoly,
            plaintext: &Plaintext,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EncryptByPublicKey(
            self: &CryptoContextDCRTPoly,
            publicKey: &PublicKeyDCRTPoly,
            plaintext: &Plaintext,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAddByCiphertextAndConst(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            constant: f64,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAddByCiphertextAndPlaintext(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            plaintext: &Plaintext,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAddByCiphertexts(
            self: &CryptoContextDCRTPoly,
            ciphertext1: &CiphertextDCRTPoly,
            ciphertext2: &CiphertextDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAddByConstAndCiphertext(
            self: &CryptoContextDCRTPoly,
            constant: f64,
            ciphertext: &CiphertextDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAddByPlaintextAndCiphertext(
            self: &CryptoContextDCRTPoly,
            plaintext: &Plaintext,
            ciphertext: &CiphertextDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAddInPlaceByCiphertextAndConst(
            self: &CryptoContextDCRTPoly,
            ciphertext: Pin<&mut CiphertextDCRTPoly>,
            constant: f64,
        );
        fn EvalAddInPlaceByCiphertextAndPlaintext(
            self: &CryptoContextDCRTPoly,
            ciphertext: Pin<&mut CiphertextDCRTPoly>,
            plaintext: &Plaintext,
        );
        fn EvalAddInPlaceByCiphertexts(
            self: &CryptoContextDCRTPoly,
            ciphertext1: Pin<&mut CiphertextDCRTPoly>,
            ciphertext2: &CiphertextDCRTPoly,
        );
        fn EvalAddInPlaceByConstAndCiphertext(
            self: &CryptoContextDCRTPoly,
            constant: f64,
            ciphertext: Pin<&mut CiphertextDCRTPoly>,
        );
        fn EvalAddInPlaceByPlaintextAndCiphertext(
            self: &CryptoContextDCRTPoly,
            plaintext: &Plaintext,
            ciphertext: Pin<&mut CiphertextDCRTPoly>,
        );
        fn EvalAddMany(
            self: &CryptoContextDCRTPoly,
            ciphertextVec: &VectorOfCiphertexts,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAddManyInPlace(
            self: &CryptoContextDCRTPoly,
            ciphertextVec: Pin<&mut VectorOfCiphertexts>,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAddMutableByCiphertextAndPlaintext(
            self: &CryptoContextDCRTPoly,
            ciphertext: Pin<&mut CiphertextDCRTPoly>,
            plaintext: &Plaintext,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAddMutableByCiphertexts(
            self: &CryptoContextDCRTPoly,
            ciphertext1: Pin<&mut CiphertextDCRTPoly>,
            ciphertext2: Pin<&mut CiphertextDCRTPoly>,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAddMutableByPlaintextAndCiphertext(
            self: &CryptoContextDCRTPoly,
            plaintext: &Plaintext,
            ciphertext: Pin<&mut CiphertextDCRTPoly>,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAddMutableInPlace(
            self: &CryptoContextDCRTPoly,
            ciphertext1: Pin<&mut CiphertextDCRTPoly>,
            ciphertext2: Pin<&mut CiphertextDCRTPoly>,
        );
        fn EvalAtIndex(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            index: u32,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAtIndexKeyGen(
            self: &CryptoContextDCRTPoly,
            privateKey: &PrivateKeyDCRTPoly,
            indexList: &CxxVector<i32>,
            publicKey: /* DCRTPolyGenNullPublicKey() */ &PublicKeyDCRTPoly,
        );
        fn EvalAutomorphism(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            i: u32,
            evalKeyMap: &MapFromIndexToEvalKey,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalAutomorphismKeyGen(
            self: &CryptoContextDCRTPoly,
            privateKey: &PrivateKeyDCRTPoly,
            indexList: &CxxVector<u32>,
        ) -> UniquePtr<MapFromIndexToEvalKey>;
        fn EvalBootstrap(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            numIterations: /* 1 */ u32,
            precision: /* 0 */ u32,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalBootstrapKeyGen(
            self: &CryptoContextDCRTPoly,
            privateKey: &PrivateKeyDCRTPoly,
            slots: u32,
        );
        fn EvalBootstrapPrecompute(self: &CryptoContextDCRTPoly, slots: /* 0 */ u32);
        fn EvalBootstrapSetup(
            self: &CryptoContextDCRTPoly,
            levelBudget: /* {5, 4} */ &CxxVector<u32>,
            dim1: /* {0, 0} */ &CxxVector<u32>,
            slots: /* 0 */ u32,
            correctionFactor: /* 0 */ u32,
            precompute: /* true */ bool,
        );
        fn EvalCKKStoFHEW(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            numCtxts: /* 0 */ u32,
        ) -> UniquePtr<VectorOfLWECiphertexts>;
        fn EvalCKKStoFHEWKeyGen(
            self: &CryptoContextDCRTPoly,
            keyPair: &KeyPairDCRTPoly,
            lwesk: &LWEPrivateKey,
        );
        fn EvalCKKStoFHEWPrecompute(self: &CryptoContextDCRTPoly, scale: /* 1.0 */ f64);
        fn EvalChebyshevFunction(
            self: &CryptoContextDCRTPoly,
            func: fn(f64, ret: &mut f64),
            ciphertext: &CiphertextDCRTPoly,
            a: f64,
            b: f64,
            degree: u32,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalChebyshevSeries(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            coefficients: &CxxVector<f64>,
            a: f64,
            b: f64,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalChebyshevSeriesLinear(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            coefficients: &CxxVector<f64>,
            a: f64,
            b: f64,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalChebyshevSeriesPS(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            coefficients: &CxxVector<f64>,
            a: f64,
            b: f64,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalCompareSchemeSwitching(
            self: &CryptoContextDCRTPoly,
            ciphertext1: &CiphertextDCRTPoly,
            ciphertext2: &CiphertextDCRTPoly,
            numCtxts: /* 0 */ u32,
            numSlots: /* 0 */ u32,
            pLWE: /* 0 */ u32,
            scaleSign: /* 1.0 */ f64,
            unit: /* false */ bool,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalCompareSwitchPrecompute(
            self: &CryptoContextDCRTPoly,
            pLWE: u32,
            scaleSign: f64,
            unit: bool,
        );
        fn EvalCos(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            a: f64,
            b: f64,
            degree: u32,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalDivide(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            a: f64,
            b: f64,
            degree: u32,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalFHEWtoCKKS(
            self: &CryptoContextDCRTPoly,
            LWECiphertexts: Pin<&mut VectorOfLWECiphertexts>,
            numCtxts: /* 0 */ u32,
            numSlots: /* 0 */ u32,
            p: /* 4 */ u32,
            pmin: /* 0.0 */ f64,
            pmax: /* 2.0 */ f64,
            dim1: /* 0 */ u32,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalFHEWtoCKKSKeyGen(
            self: &CryptoContextDCRTPoly,
            keyPair: &KeyPairDCRTPoly,
            lwesk: &LWEPrivateKey,
            numSlots: /* 0 */ u32,
            numCtxts: /* 0 */ u32,
            dim1: /* 0 */ u32,
            L: /* 0 */ u32,
        );
        fn EvalFastRotation(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            index: u32,
            m: u32,
            digits: &VectorOfDCRTPolys,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalFastRotationExt(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            index: u32,
            digits: &VectorOfDCRTPolys,
            addFirst: bool,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalFastRotationPrecompute(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
        ) -> UniquePtr<VectorOfDCRTPolys>;
        fn EvalInnerProductByCiphertexts(
            self: &CryptoContextDCRTPoly,
            ciphertext1: &CiphertextDCRTPoly,
            ciphertext2: &CiphertextDCRTPoly,
            batchSize: u32,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalInnerProductByCiphertextAndPlaintext(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            plaintext: &Plaintext,
            batchSize: u32,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalInnerProductByPlaintextAndCiphertext(
            self: &CryptoContextDCRTPoly,
            plaintext: &Plaintext,
            ciphertext: &CiphertextDCRTPoly,
            batchSize: u32,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalLinearWSumMutableByConstantsAndVectorOfCiphertexts(
            self: &CryptoContextDCRTPoly,
            constantsVec: &CxxVector<f64>,
            ciphertextVec: Pin<&mut VectorOfCiphertexts>,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalLinearWSumMutableByVectorOfCiphertextsAndConstants(
            self: &CryptoContextDCRTPoly,
            ciphertextVec: Pin<&mut VectorOfCiphertexts>,
            constantsVec: &CxxVector<f64>,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalLogistic(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            a: f64,
            b: f64,
            degree: u32,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMaxSchemeSwitching(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            publicKey: &PublicKeyDCRTPoly,
            numValues: /* 0 */ u32,
            numSlots: /* 0 */ u32,
            pLWE: /* 0 */ u32,
            scaleSign: /* 1.0 */ f64,
        ) -> UniquePtr<VectorOfCiphertexts>;
        fn EvalMaxSchemeSwitchingAlt(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            publicKey: &PublicKeyDCRTPoly,
            numValues: /* 0 */ u32,
            numSlots: /* 0 */ u32,
            pLWE: /* 0 */ u32,
            scaleSign: /* 1.0 */ f64,
        ) -> UniquePtr<VectorOfCiphertexts>;
        fn EvalMerge(
            self: &CryptoContextDCRTPoly,
            ciphertextVec: &VectorOfCiphertexts,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMinSchemeSwitching(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            publicKey: &PublicKeyDCRTPoly,
            numValues: /* 0 */ u32,
            numSlots: /* 0 */ u32,
            pLWE: /* 0 */ u32,
            scaleSign: /* 1.0 */ f64,
        ) -> UniquePtr<VectorOfCiphertexts>;
        fn EvalMinSchemeSwitchingAlt(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            publicKey: &PublicKeyDCRTPoly,
            numValues: /* 0 */ u32,
            numSlots: /* 0 */ u32,
            pLWE: /* 0 */ u32,
            scaleSign: /* 1.0 */ f64,
        ) -> UniquePtr<VectorOfCiphertexts>;
        fn EvalMultAndRelinearize(
            self: &CryptoContextDCRTPoly,
            ciphertext1: &CiphertextDCRTPoly,
            ciphertext2: &CiphertextDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultByCiphertextAndConst(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            constant: f64,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultByCiphertextAndPlaintext(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            plaintext: &Plaintext,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultByCiphertexts(
            self: &CryptoContextDCRTPoly,
            ciphertext1: &CiphertextDCRTPoly,
            ciphertext2: &CiphertextDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultByConstAndCiphertext(
            self: &CryptoContextDCRTPoly,
            constant: f64,
            ciphertext: &CiphertextDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultByPlaintextAndCiphertext(
            self: &CryptoContextDCRTPoly,
            plaintext: &Plaintext,
            ciphertext: &CiphertextDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultInPlaceByCiphertextAndConst(
            self: &CryptoContextDCRTPoly,
            ciphertext: Pin<&mut CiphertextDCRTPoly>,
            constant: f64,
        );
        fn EvalMultInPlaceByConstAndCiphertext(
            self: &CryptoContextDCRTPoly,
            constant: f64,
            ciphertext: Pin<&mut CiphertextDCRTPoly>,
        );
        fn EvalMultKeyGen(self: &CryptoContextDCRTPoly, key: &PrivateKeyDCRTPoly);
        fn EvalMultKeysGen(self: &CryptoContextDCRTPoly, key: &PrivateKeyDCRTPoly);
        fn EvalMultMany(
            self: &CryptoContextDCRTPoly,
            ciphertextVec: &VectorOfCiphertexts,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultMutableByCiphertextAndPlaintext(
            self: &CryptoContextDCRTPoly,
            ciphertext: Pin<&mut CiphertextDCRTPoly>,
            plaintext: &Plaintext,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultMutableByCiphertexts(
            self: &CryptoContextDCRTPoly,
            ciphertext1: Pin<&mut CiphertextDCRTPoly>,
            ciphertext2: Pin<&mut CiphertextDCRTPoly>,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultMutableByPlaintextAndCiphertext(
            self: &CryptoContextDCRTPoly,
            plaintext: &Plaintext,
            ciphertext: Pin<&mut CiphertextDCRTPoly>,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalMultMutableInPlace(
            self: &CryptoContextDCRTPoly,
            ciphertext1: Pin<&mut CiphertextDCRTPoly>,
            ciphertext2: Pin<&mut CiphertextDCRTPoly>,
        );
        fn EvalMultNoRelin(
            self: &CryptoContextDCRTPoly,
            ciphertext1: &CiphertextDCRTPoly,
            ciphertext2: &CiphertextDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalNegate(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalNegateInPlace(
            self: &CryptoContextDCRTPoly,
            ciphertext: Pin<&mut CiphertextDCRTPoly>,
        );
        fn EvalPoly(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            coefficients: &CxxVector<f64>,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalPolyLinear(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            coefficients: &CxxVector<f64>,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalPolyPS(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            coefficients: &CxxVector<f64>,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalRotate(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            index: i32,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalRotateKeyGen(
            self: &CryptoContextDCRTPoly,
            privateKey: &PrivateKeyDCRTPoly,
            indexList: &CxxVector<i32>,
            publicKey: /* DCRTPolyGenNullPublicKey() */ &PublicKeyDCRTPoly,
        );
        fn EvalSchemeSwitchingKeyGen(
            self: &CryptoContextDCRTPoly,
            keyPair: &KeyPairDCRTPoly,
            lwesk: &LWEPrivateKey,
        );
        fn EvalSin(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            a: f64,
            b: f64,
            degree: u32,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSquare(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSquareInPlace(
            self: &CryptoContextDCRTPoly,
            ciphertext: Pin<&mut CiphertextDCRTPoly>,
        );
        fn EvalSquareMutable(
            self: &CryptoContextDCRTPoly,
            ciphertext: Pin<&mut CiphertextDCRTPoly>,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSubByCiphertextAndConst(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            constant: f64,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSubByCiphertextAndPlaintext(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            plaintext: &Plaintext,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSubByCiphertexts(
            self: &CryptoContextDCRTPoly,
            ciphertext1: &CiphertextDCRTPoly,
            ciphertext2: &CiphertextDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSubByConstAndCiphertext(
            self: &CryptoContextDCRTPoly,
            constant: f64,
            ciphertext: &CiphertextDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSubByPlaintextAndCiphertext(
            self: &CryptoContextDCRTPoly,
            plaintext: &Plaintext,
            ciphertext: &CiphertextDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSubInPlaceByCiphertextAndConst(
            self: &CryptoContextDCRTPoly,
            ciphertext: Pin<&mut CiphertextDCRTPoly>,
            constant: f64,
        );
        fn EvalSubInPlaceByCiphertexts(
            self: &CryptoContextDCRTPoly,
            ciphertext1: Pin<&mut CiphertextDCRTPoly>,
            ciphertext2: &CiphertextDCRTPoly,
        );
        fn EvalSubInPlaceByConstAndCiphertext(
            self: &CryptoContextDCRTPoly,
            constant: f64,
            ciphertext: Pin<&mut CiphertextDCRTPoly>,
        );
        fn EvalSubMutableByCiphertextAndPlaintext(
            self: &CryptoContextDCRTPoly,
            ciphertext: Pin<&mut CiphertextDCRTPoly>,
            plaintext: &Plaintext,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSubMutableByCiphertexts(
            self: &CryptoContextDCRTPoly,
            ciphertext1: Pin<&mut CiphertextDCRTPoly>,
            ciphertext2: Pin<&mut CiphertextDCRTPoly>,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSubMutableByPlaintextAndCiphertext(
            self: &CryptoContextDCRTPoly,
            plaintext: &Plaintext,
            ciphertext: Pin<&mut CiphertextDCRTPoly>,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSubMutableInPlace(
            self: &CryptoContextDCRTPoly,
            ciphertext1: Pin<&mut CiphertextDCRTPoly>,
            ciphertext2: Pin<&mut CiphertextDCRTPoly>,
        );
        fn EvalSum(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            batchSize: u32,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSumCols(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            rowSize: u32,
            evalSumKeyMap: &MapFromIndexToEvalKey,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSumColsKeyGen(
            self: &CryptoContextDCRTPoly,
            privateKey: &PrivateKeyDCRTPoly,
            publicKey: /* DCRTPolyGenNullPublicKey() */ &PublicKeyDCRTPoly,
        ) -> UniquePtr<MapFromIndexToEvalKey>;
        fn EvalSumKeyGen(
            self: &CryptoContextDCRTPoly,
            privateKey: &PrivateKeyDCRTPoly,
            publicKey: /* DCRTPolyGenNullPublicKey() */ &PublicKeyDCRTPoly,
        );
        fn EvalSumRows(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            rowSize: u32,
            evalSumKeyMap: &MapFromIndexToEvalKey,
            subringDim: /* 0 */ u32,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn EvalSumRowsKeyGen(
            self: &CryptoContextDCRTPoly,
            privateKey: &PrivateKeyDCRTPoly,
            publicKey: /* DCRTPolyGenNullPublicKey() */ &PublicKeyDCRTPoly,
            rowSize: /* 0 */ u32,
            subringDim: /* 0 */ u32,
        ) -> UniquePtr<MapFromIndexToEvalKey>;
        fn FindAutomorphismIndex(self: &CryptoContextDCRTPoly, idx: u32) -> u32;
        fn FindAutomorphismIndices(
            self: &CryptoContextDCRTPoly,
            idxList: &CxxVector<u32>,
        ) -> UniquePtr<CxxVector<u32>>;
        fn GetCryptoParameters(
            self: &CryptoContextDCRTPoly,
        ) -> UniquePtr<CryptoParametersBaseDCRTPoly>;
        fn GetCyclotomicOrder(self: &CryptoContextDCRTPoly) -> u32;
        fn GetElementParams(self: &CryptoContextDCRTPoly) -> UniquePtr<DCRTPolyParams>;
        fn GetEncodingParams(self: &CryptoContextDCRTPoly) -> UniquePtr<EncodingParams>;
        fn GetKeyGenLevel(self: &CryptoContextDCRTPoly) -> usize;
        fn GetModulus(self: &CryptoContextDCRTPoly) -> u64;
        fn GetRingDimension(self: &CryptoContextDCRTPoly) -> u32;
        fn GetRootOfUnity(self: &CryptoContextDCRTPoly) -> u64;
        fn GetScheme(self: &CryptoContextDCRTPoly) -> UniquePtr<SchemeBaseDCRTPoly>;
        fn GetSchemeId(self: &CryptoContextDCRTPoly) -> SCHEME;
        fn GetSwkFC(self: &CryptoContextDCRTPoly) -> UniquePtr<CiphertextDCRTPoly>;
        fn IntMPBootAdd(
            self: &CryptoContextDCRTPoly,
            sharesPairVec: Pin<&mut VectorOfVectorOfCiphertexts>,
        ) -> UniquePtr<VectorOfCiphertexts>;
        fn IntMPBootAdjustScale(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn IntMPBootDecrypt(
            self: &CryptoContextDCRTPoly,
            privateKey: &PrivateKeyDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            a: &CiphertextDCRTPoly,
        ) -> UniquePtr<VectorOfCiphertexts>;
        fn IntMPBootEncrypt(
            self: &CryptoContextDCRTPoly,
            publicKey: &PublicKeyDCRTPoly,
            sharesPair: &VectorOfCiphertexts,
            a: &CiphertextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn IntMPBootRandomElementGen(
            self: &CryptoContextDCRTPoly,
            publicKey: &PublicKeyDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn KeyGen(self: &CryptoContextDCRTPoly) -> UniquePtr<KeyPairDCRTPoly>;
        fn KeySwitch(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            evalKey: &EvalKeyDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn KeySwitchDown(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn KeySwitchDownFirstElement(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
        ) -> UniquePtr<DCRTPoly>;
        fn KeySwitchExt(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            addFirst: bool,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn KeySwitchGen(
            self: &CryptoContextDCRTPoly,
            oldPrivateKey: &PrivateKeyDCRTPoly,
            newPrivateKey: &PrivateKeyDCRTPoly,
        ) -> UniquePtr<EvalKeyDCRTPoly>;
        fn KeySwitchInPlace(
            self: &CryptoContextDCRTPoly,
            ciphertext: Pin<&mut CiphertextDCRTPoly>,
            evalKey: &EvalKeyDCRTPoly,
        );
        fn LevelReduce(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            evalKey: &EvalKeyDCRTPoly,
            levels: /* 1 */ usize,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn LevelReduceInPlace(
            self: &CryptoContextDCRTPoly,
            ciphertext: Pin<&mut CiphertextDCRTPoly>,
            evalKey: &EvalKeyDCRTPoly,
            levels: /* 1 */ usize,
        );
        fn MakeCKKSPackedPlaintextByVectorOfDouble(
            self: &CryptoContextDCRTPoly,
            value: &CxxVector<f64>,
            scaleDeg: /* 1 */ usize,
            level: /* 0 */ u32,
            params: /* DCRTPolyGenNullParams() */ &DCRTPolyParams,
            slots: /* 0 */ u32,
        ) -> UniquePtr<Plaintext>;
        fn MakeCKKSPackedPlaintextByVectorOfComplex(
            self: &CryptoContextDCRTPoly,
            value: &CxxVector<ComplexPair>,
            scaleDeg: /* 1 */ usize,
            level: /* 0 */ u32,
            params: /* DCRTPolyGenNullParams() */ &DCRTPolyParams,
            slots: /* 0 */ u32,
        ) -> UniquePtr<Plaintext>;
        fn MakeCoefPackedPlaintext(
            self: &CryptoContextDCRTPoly,
            value: &CxxVector<i64>,
            noiseScaleDeg: /* 1 */ usize,
            level: /* 0 */ u32,
        ) -> UniquePtr<Plaintext>;
        fn MakePackedPlaintext(
            self: &CryptoContextDCRTPoly,
            value: &CxxVector<i64>,
            noiseScaleDeg: /* 1 */ usize,
            level: /* 0 */ u32,
        ) -> UniquePtr<Plaintext>;
        fn MakeStringPlaintext(self: &CryptoContextDCRTPoly, s: &CxxString)
            -> UniquePtr<Plaintext>;
        fn ModReduce(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn ModReduceInPlace(self: &CryptoContextDCRTPoly, ciphertext: Pin<&mut CiphertextDCRTPoly>);
        fn MultiAddEvalAutomorphismKeys(
            self: &CryptoContextDCRTPoly,
            evalKeyMap1: &MapFromIndexToEvalKey,
            evalKeyMap2: &MapFromIndexToEvalKey,
            keyId: /* "" */ &CxxString,
        ) -> UniquePtr<MapFromIndexToEvalKey>;
        fn MultiAddEvalKeys(
            self: &CryptoContextDCRTPoly,
            evalKey1: &EvalKeyDCRTPoly,
            evalKey2: &EvalKeyDCRTPoly,
            keyId: /* "" */ &CxxString,
        ) -> UniquePtr<EvalKeyDCRTPoly>;
        fn MultiAddEvalMultKeys(
            self: &CryptoContextDCRTPoly,
            evalKey1: &EvalKeyDCRTPoly,
            evalKey2: &EvalKeyDCRTPoly,
            keyId: /* "" */ &CxxString,
        ) -> UniquePtr<EvalKeyDCRTPoly>;
        fn MultiAddEvalSumKeys(
            self: &CryptoContextDCRTPoly,
            evalKeyMap1: &MapFromIndexToEvalKey,
            evalKeyMap2: &MapFromIndexToEvalKey,
            keyId: /* "" */ &CxxString,
        ) -> UniquePtr<MapFromIndexToEvalKey>;
        fn MultiAddPubKeys(
            self: &CryptoContextDCRTPoly,
            publicKey1: &PublicKeyDCRTPoly,
            publicKey2: &PublicKeyDCRTPoly,
            keyId: /* "" */ &CxxString,
        ) -> UniquePtr<PublicKeyDCRTPoly>;
        fn MultiEvalAtIndexKeyGen(
            self: &CryptoContextDCRTPoly,
            privateKey: &PrivateKeyDCRTPoly,
            evalKeyMap: &MapFromIndexToEvalKey,
            indexList: &CxxVector<i32>,
            keyId: /* "" */ &CxxString,
        ) -> UniquePtr<MapFromIndexToEvalKey>;
        fn MultiEvalAutomorphismKeyGen(
            self: &CryptoContextDCRTPoly,
            privateKey: &PrivateKeyDCRTPoly,
            evalKeyMap: &MapFromIndexToEvalKey,
            indexList: &CxxVector<u32>,
            keyId: /* "" */ &CxxString,
        ) -> UniquePtr<MapFromIndexToEvalKey>;
        fn MultiEvalSumKeyGen(
            self: &CryptoContextDCRTPoly,
            privateKey: &PrivateKeyDCRTPoly,
            evalKeyMap: &MapFromIndexToEvalKey,
            keyId: /* "" */ &CxxString,
        ) -> UniquePtr<MapFromIndexToEvalKey>;
        fn MultiKeySwitchGen(
            self: &CryptoContextDCRTPoly,
            originalPrivateKey: &PrivateKeyDCRTPoly,
            newPrivateKey: &PrivateKeyDCRTPoly,
            evalKey: &EvalKeyDCRTPoly,
        ) -> UniquePtr<EvalKeyDCRTPoly>;
        fn MultiMultEvalKey(
            self: &CryptoContextDCRTPoly,
            privateKey: &PrivateKeyDCRTPoly,
            evalKey: &EvalKeyDCRTPoly,
            keyId: /* "" */ &CxxString,
        ) -> UniquePtr<EvalKeyDCRTPoly>;
        fn MultipartyDecryptFusion(
            self: &CryptoContextDCRTPoly,
            partialCiphertextVec: &VectorOfCiphertexts,
            plaintext: Pin<&mut Plaintext>,
        ) -> UniquePtr<DecryptResult>;
        fn MultipartyDecryptLead(
            self: &CryptoContextDCRTPoly,
            ciphertextVec: &VectorOfCiphertexts,
            privateKey: &PrivateKeyDCRTPoly,
        ) -> UniquePtr<VectorOfCiphertexts>;
        fn MultipartyDecryptMain(
            self: &CryptoContextDCRTPoly,
            ciphertextVec: &VectorOfCiphertexts,
            privateKey: &PrivateKeyDCRTPoly,
        ) -> UniquePtr<VectorOfCiphertexts>;
        fn MultipartyKeyGenByPublicKey(
            self: &CryptoContextDCRTPoly,
            publicKey: &PublicKeyDCRTPoly,
            makeSparse: /* false */ bool,
            fresh: /* false */ bool,
        ) -> UniquePtr<KeyPairDCRTPoly>;
        fn MultipartyKeyGenByVectorOfPrivateKeys(
            self: &CryptoContextDCRTPoly,
            privateKeyVec: &VectorOfPrivateKeys,
        ) -> UniquePtr<KeyPairDCRTPoly>;
        fn ReEncrypt(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
            evalKey: &EvalKeyDCRTPoly,
            publicKey: /* DCRTPolyGenNullPublicKey() */ &PublicKeyDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn ReKeyGen(
            self: &CryptoContextDCRTPoly,
            oldPrivateKey: &PrivateKeyDCRTPoly,
            newPublicKey: &PublicKeyDCRTPoly,
        ) -> UniquePtr<EvalKeyDCRTPoly>;
        fn RecoverSharedKey(
            self: &CryptoContextDCRTPoly,
            sk: Pin<&mut PrivateKeyDCRTPoly>,
            sk_shares: Pin<&mut UnorderedMapFromIndexToDCRTPoly>,
            N: u32,
            threshold: u32,
            shareType: &CxxString,
        );
        fn Relinearize(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn RelinearizeInPlace(
            self: &CryptoContextDCRTPoly,
            ciphertext: Pin<&mut CiphertextDCRTPoly>,
        );
        fn Rescale(
            self: &CryptoContextDCRTPoly,
            ciphertext: &CiphertextDCRTPoly,
        ) -> UniquePtr<CiphertextDCRTPoly>;
        fn RescaleInPlace(self: &CryptoContextDCRTPoly, ciphertext: Pin<&mut CiphertextDCRTPoly>);
        fn SetKeyGenLevel(self: &CryptoContextDCRTPoly, level: usize);
        fn SetSchemeId(self: &CryptoContextDCRTPoly, schemeTag: SCHEME);
        fn SetSwkFC(self: &CryptoContextDCRTPoly, FHEWtoCKKSswk: &CiphertextDCRTPoly);
        fn ShareKeys(
            self: &CryptoContextDCRTPoly,
            sk: &PrivateKeyDCRTPoly,
            N: u32,
            threshold: u32,
            index: u32,
            shareType: &CxxString,
        ) -> UniquePtr<UnorderedMapFromIndexToDCRTPoly>;
        fn SparseKeyGen(self: &CryptoContextDCRTPoly) -> UniquePtr<KeyPairDCRTPoly>;

        // cxx currently does not support static class methods
        fn DCRTPolyClearEvalAutomorphismKeys();
        fn DCRTPolyClearEvalAutomorphismKeysByCryptoContext(cryptoContext: &CryptoContextDCRTPoly);
        fn DCRTPolyClearEvalAutomorphismKeysById(id: &CxxString);
        fn DCRTPolyClearEvalMultKeys();
        fn DCRTPolyClearEvalMultKeysByCryptoContext(cryptoContext: &CryptoContextDCRTPoly);
        fn DCRTPolyClearEvalMultKeysById(id: &CxxString);
        fn DCRTPolyClearEvalSumKeys();
        fn DCRTPolyClearEvalSumKeysByCryptoContext(cryptoContext: &CryptoContextDCRTPoly);
        fn DCRTPolyClearEvalSumKeysById(id: &CxxString);
        fn DCRTPolyGetCopyOfAllEvalAutomorphismKeys(
        ) -> UniquePtr<MapFromStringToMapFromIndexToEvalKey>;
        fn DCRTPolyGetCopyOfAllEvalMultKeys() -> UniquePtr<MapFromStringToVectorOfEvalKeys>;
        fn DCRTPolyGetCopyOfAllEvalSumKeys() -> UniquePtr<MapFromStringToMapFromIndexToEvalKey>;
        fn DCRTPolyGetCopyOfEvalAutomorphismKeyMap(
            keyID: &CxxString,
        ) -> UniquePtr<MapFromIndexToEvalKey>;
        fn DCRTPolyGetCopyOfEvalMultKeyVector(keyID: &CxxString) -> UniquePtr<VectorOfEvalKeys>;
        fn DCRTPolyGetCopyOfEvalSumKeyMap(id: &CxxString) -> UniquePtr<MapFromIndexToEvalKey>;
        fn DCRTPolyGetExistingEvalAutomorphismKeyIndices(
            keyTag: &CxxString,
        ) -> UniquePtr<SetOfUints>;
        fn DCRTPolyGetPlaintextForDecrypt(
            pte: PlaintextEncodings,
            evp: &DCRTPolyParams,
            ep: &EncodingParams,
        ) -> UniquePtr<Plaintext>;
        fn DCRTPolyGetUniqueValues(
            oldValues: &SetOfUints,
            newValues: &SetOfUints,
        ) -> UniquePtr<SetOfUints>;
        fn DCRTPolyInsertEvalAutomorphismKey(
            evalKeyMap: &MapFromIndexToEvalKey,
            keyTag: /* "" */ &CxxString,
        );
        fn DCRTPolyInsertEvalMultKey(evalKeyVec: &VectorOfEvalKeys);
        fn DCRTPolyInsertEvalSumKey(
            mapToInsert: &MapFromIndexToEvalKey,
            keyTag: /* "" */ &CxxString,
        );

        // Generator functions
        fn DCRTPolyGenCryptoContextByParamsCKKSRNS(
            params: &ParamsCKKSRNS,
        ) -> UniquePtr<CryptoContextDCRTPoly>;
        fn DCRTPolyGenCryptoContextByParamsBFVRNS(
            params: &ParamsBFVRNS,
        ) -> UniquePtr<CryptoContextDCRTPoly>;
        fn DCRTPolyGenCryptoContextByParamsBGVRNS(
            params: &ParamsBGVRNS,
        ) -> UniquePtr<CryptoContextDCRTPoly>;
        fn DCRTPolyGenNullCryptoContext() -> UniquePtr<CryptoContextDCRTPoly>;
    }

    // DCRTPolyParams
    unsafe extern "C++" {
        // Generator functions
        fn DCRTPolyGenNullParams() -> UniquePtr<DCRTPolyParams>;
        fn DCRTPolyGenParamsByOrderSizeBits(
            order: u32,
            size: u32,
            bits: u32,
        ) -> UniquePtr<DCRTPolyParams>;
    }

    // KeyPairDCRTPoly
    unsafe extern "C++" {
        fn GetPrivateKey(self: &KeyPairDCRTPoly) -> UniquePtr<PrivateKeyDCRTPoly>;
        fn GetPublicKey(self: &KeyPairDCRTPoly) -> UniquePtr<PublicKeyDCRTPoly>;
    }

    // Params
    unsafe extern "C++" {
        fn GetBatchSize(self: &Params) -> u32;
        fn GetDecryptionNoiseMode(self: &Params) -> DecryptionNoiseMode;
        fn GetDesiredPrecision(self: &Params) -> f64;
        fn GetDigitSize(self: &Params) -> u32;
        fn GetEncryptionTechnique(self: &Params) -> EncryptionTechnique;
        fn GetEvalAddCount(self: &Params) -> u32;
        fn GetExecutionMode(self: &Params) -> ExecutionMode;
        fn GetFirstModSize(self: &Params) -> u32;
        fn GetInteractiveBootCompressionLevel(self: &Params) -> COMPRESSION_LEVEL;
        fn GetKeySwitchCount(self: &Params) -> u32;
        fn GetKeySwitchTechnique(self: &Params) -> KeySwitchTechnique;
        fn GetMaxRelinSkDeg(self: &Params) -> u32;
        fn GetMultipartyMode(self: &Params) -> MultipartyMode;
        fn GetMultiplicationTechnique(self: &Params) -> MultiplicationTechnique;
        fn GetMultiplicativeDepth(self: &Params) -> u32;
        fn GetNoiseEstimate(self: &Params) -> f64;
        fn GetNumAdversarialQueries(self: &Params) -> f64;
        fn GetNumLargeDigits(self: &Params) -> u32;
        fn GetPREMode(self: &Params) -> ProxyReEncryptionMode;
        fn GetPlaintextModulus(self: &Params) -> u64;
        fn GetRingDim(self: &Params) -> u32;
        fn GetScalingModSize(self: &Params) -> u32;
        fn GetScalingTechnique(self: &Params) -> ScalingTechnique;
        fn GetScheme(self: &Params) -> SCHEME;
        fn GetSecretKeyDist(self: &Params) -> SecretKeyDist;
        fn GetSecurityLevel(self: &Params) -> SecurityLevel;
        fn GetStandardDeviation(self: &Params) -> f32;
        fn GetStatisticalSecurity(self: &Params) -> f64;
        fn GetThresholdNumOfParties(self: &Params) -> u32;
        fn SetBatchSize(self: Pin<&mut Params>, batchSize0: u32);
        fn SetDecryptionNoiseMode(
            self: Pin<&mut Params>,
            decryptionNoiseMode0: DecryptionNoiseMode,
        );
        fn SetDesiredPrecision(self: Pin<&mut Params>, desiredPrecision0: f64);
        fn SetDigitSize(self: Pin<&mut Params>, digitSize0: u32);
        fn SetEncryptionTechnique(
            self: Pin<&mut Params>,
            encryptionTechnique0: EncryptionTechnique,
        );
        fn SetEvalAddCount(self: Pin<&mut Params>, evalAddCount0: u32);
        fn SetExecutionMode(self: Pin<&mut Params>, executionMode0: ExecutionMode);
        fn SetFirstModSize(self: Pin<&mut Params>, firstModSize0: u32);
        fn SetInteractiveBootCompressionLevel(
            self: Pin<&mut Params>,
            interactiveBootCompressionLevel0: COMPRESSION_LEVEL,
        );
        fn SetKeySwitchCount(self: Pin<&mut Params>, keySwitchCount0: u32);
        fn SetKeySwitchTechnique(self: Pin<&mut Params>, ksTech0: KeySwitchTechnique);
        fn SetMaxRelinSkDeg(self: Pin<&mut Params>, maxRelinSkDeg0: u32);
        fn SetMultipartyMode(self: Pin<&mut Params>, multipartyMode0: MultipartyMode);
        fn SetMultiplicationTechnique(
            self: Pin<&mut Params>,
            multiplicationTechnique0: MultiplicationTechnique,
        );
        fn SetMultiplicativeDepth(self: Pin<&mut Params>, multiplicativeDepth0: u32);
        fn SetNoiseEstimate(self: Pin<&mut Params>, noiseEstimate0: f64);
        fn SetNumAdversarialQueries(self: Pin<&mut Params>, numAdversarialQueries0: u32);
        fn SetNumLargeDigits(self: Pin<&mut Params>, numLargeDigits0: u32);
        fn SetPREMode(self: Pin<&mut Params>, PREMode0: ProxyReEncryptionMode);
        fn SetPlaintextModulus(self: Pin<&mut Params>, ptModulus0: u64);
        fn SetRingDim(self: Pin<&mut Params>, ringDim0: u32);
        fn SetScalingModSize(self: Pin<&mut Params>, scalingModSize0: u32);
        fn SetScalingTechnique(self: Pin<&mut Params>, scalTech0: ScalingTechnique);
        fn SetSecretKeyDist(self: Pin<&mut Params>, secretKeyDist0: SecretKeyDist);
        fn SetSecurityLevel(self: Pin<&mut Params>, securityLevel0: SecurityLevel);
        fn SetStandardDeviation(self: Pin<&mut Params>, standardDeviation0: f32);
        fn SetStatisticalSecurity(self: Pin<&mut Params>, statisticalSecurity0: u32);
        fn SetThresholdNumOfParties(self: Pin<&mut Params>, thresholdNumOfParties0: u32);

        // Generator functions
        fn GenParamsByScheme(scheme: SCHEME) -> UniquePtr<Params>;
        fn GenParamsByVectorOfString(vals: &CxxVector<CxxString>) -> UniquePtr<Params>;
    }

    // ParamsBFVRNS
    unsafe extern "C++" {
        fn GetBatchSize(self: &ParamsBFVRNS) -> u32;
        fn GetDecryptionNoiseMode(self: &ParamsBFVRNS) -> DecryptionNoiseMode;
        fn GetDesiredPrecision(self: &ParamsBFVRNS) -> f64;
        fn GetDigitSize(self: &ParamsBFVRNS) -> u32;
        fn GetEncryptionTechnique(self: &ParamsBFVRNS) -> EncryptionTechnique;
        fn GetEvalAddCount(self: &ParamsBFVRNS) -> u32;
        fn GetExecutionMode(self: &ParamsBFVRNS) -> ExecutionMode;
        fn GetFirstModSize(self: &ParamsBFVRNS) -> u32;
        fn GetInteractiveBootCompressionLevel(self: &ParamsBFVRNS) -> COMPRESSION_LEVEL;
        fn GetKeySwitchCount(self: &ParamsBFVRNS) -> u32;
        fn GetKeySwitchTechnique(self: &ParamsBFVRNS) -> KeySwitchTechnique;
        fn GetMaxRelinSkDeg(self: &ParamsBFVRNS) -> u32;
        fn GetMultipartyMode(self: &ParamsBFVRNS) -> MultipartyMode;
        fn GetMultiplicationTechnique(self: &ParamsBFVRNS) -> MultiplicationTechnique;
        fn GetMultiplicativeDepth(self: &ParamsBFVRNS) -> u32;
        fn GetNoiseEstimate(self: &ParamsBFVRNS) -> f64;
        fn GetNumAdversarialQueries(self: &ParamsBFVRNS) -> f64;
        fn GetNumLargeDigits(self: &ParamsBFVRNS) -> u32;
        fn GetPREMode(self: &ParamsBFVRNS) -> ProxyReEncryptionMode;
        fn GetPlaintextModulus(self: &ParamsBFVRNS) -> u64;
        fn GetRingDim(self: &ParamsBFVRNS) -> u32;
        fn GetScalingModSize(self: &ParamsBFVRNS) -> u32;
        fn GetScalingTechnique(self: &ParamsBFVRNS) -> ScalingTechnique;
        fn GetScheme(self: &ParamsBFVRNS) -> SCHEME;
        fn GetSecretKeyDist(self: &ParamsBFVRNS) -> SecretKeyDist;
        fn GetSecurityLevel(self: &ParamsBFVRNS) -> SecurityLevel;
        fn GetStandardDeviation(self: &ParamsBFVRNS) -> f32;
        fn GetStatisticalSecurity(self: &ParamsBFVRNS) -> f64;
        fn GetThresholdNumOfParties(self: &ParamsBFVRNS) -> u32;
        fn SetBatchSize(self: Pin<&mut ParamsBFVRNS>, batchSize0: u32);
        fn SetDecryptionNoiseMode(
            self: Pin<&mut ParamsBFVRNS>,
            decryptionNoiseMode0: DecryptionNoiseMode,
        );
        fn SetDesiredPrecision(self: Pin<&mut ParamsBFVRNS>, desiredPrecision0: f64);
        fn SetDigitSize(self: Pin<&mut ParamsBFVRNS>, digitSize0: u32);
        fn SetEncryptionTechnique(
            self: Pin<&mut ParamsBFVRNS>,
            encryptionTechnique0: EncryptionTechnique,
        );
        fn SetEvalAddCount(self: Pin<&mut ParamsBFVRNS>, evalAddCount0: u32);
        fn SetExecutionMode(self: Pin<&mut ParamsBFVRNS>, executionMode0: ExecutionMode);
        fn SetFirstModSize(self: Pin<&mut ParamsBFVRNS>, firstModSize0: u32);
        fn SetInteractiveBootCompressionLevel(
            self: Pin<&mut ParamsBFVRNS>,
            interactiveBootCompressionLevel0: COMPRESSION_LEVEL,
        );
        fn SetKeySwitchCount(self: Pin<&mut ParamsBFVRNS>, keySwitchCount0: u32);
        fn SetKeySwitchTechnique(self: Pin<&mut ParamsBFVRNS>, ksTech0: KeySwitchTechnique);
        fn SetMaxRelinSkDeg(self: Pin<&mut ParamsBFVRNS>, maxRelinSkDeg0: u32);
        fn SetMultipartyMode(self: Pin<&mut ParamsBFVRNS>, multipartyMode0: MultipartyMode);
        fn SetMultiplicationTechnique(
            self: Pin<&mut ParamsBFVRNS>,
            multiplicationTechnique0: MultiplicationTechnique,
        );
        fn SetMultiplicativeDepth(self: Pin<&mut ParamsBFVRNS>, multiplicativeDepth0: u32);
        fn SetNoiseEstimate(self: Pin<&mut ParamsBFVRNS>, noiseEstimate0: f64);
        fn SetNumAdversarialQueries(self: Pin<&mut ParamsBFVRNS>, numAdversarialQueries0: u32);
        fn SetNumLargeDigits(self: Pin<&mut ParamsBFVRNS>, numLargeDigits0: u32);
        fn SetPREMode(self: Pin<&mut ParamsBFVRNS>, PREMode0: ProxyReEncryptionMode);
        fn SetPlaintextModulus(self: Pin<&mut ParamsBFVRNS>, ptModulus0: u64);
        fn SetRingDim(self: Pin<&mut ParamsBFVRNS>, ringDim0: u32);
        fn SetScalingModSize(self: Pin<&mut ParamsBFVRNS>, scalingModSize0: u32);
        fn SetScalingTechnique(self: Pin<&mut ParamsBFVRNS>, scalTech0: ScalingTechnique);
        fn SetSecretKeyDist(self: Pin<&mut ParamsBFVRNS>, secretKeyDist0: SecretKeyDist);
        fn SetSecurityLevel(self: Pin<&mut ParamsBFVRNS>, securityLevel0: SecurityLevel);
        fn SetStandardDeviation(self: Pin<&mut ParamsBFVRNS>, standardDeviation0: f32);
        fn SetStatisticalSecurity(self: Pin<&mut ParamsBFVRNS>, statisticalSecurity0: u32);
        fn SetThresholdNumOfParties(self: Pin<&mut ParamsBFVRNS>, thresholdNumOfParties0: u32);

        // Generator functions
        fn GenParamsBFVRNS() -> UniquePtr<ParamsBFVRNS>;
        fn GenParamsBFVRNSbyVectorOfString(vals: &CxxVector<CxxString>) -> UniquePtr<ParamsBFVRNS>;
    }

    // ParamsBGVRNS
    unsafe extern "C++" {
        fn GetBatchSize(self: &ParamsBGVRNS) -> u32;
        fn GetDecryptionNoiseMode(self: &ParamsBGVRNS) -> DecryptionNoiseMode;
        fn GetDesiredPrecision(self: &ParamsBGVRNS) -> f64;
        fn GetDigitSize(self: &ParamsBGVRNS) -> u32;
        fn GetEncryptionTechnique(self: &ParamsBGVRNS) -> EncryptionTechnique;
        fn GetEvalAddCount(self: &ParamsBGVRNS) -> u32;
        fn GetExecutionMode(self: &ParamsBGVRNS) -> ExecutionMode;
        fn GetFirstModSize(self: &ParamsBGVRNS) -> u32;
        fn GetInteractiveBootCompressionLevel(self: &ParamsBGVRNS) -> COMPRESSION_LEVEL;
        fn GetKeySwitchCount(self: &ParamsBGVRNS) -> u32;
        fn GetKeySwitchTechnique(self: &ParamsBGVRNS) -> KeySwitchTechnique;
        fn GetMaxRelinSkDeg(self: &ParamsBGVRNS) -> u32;
        fn GetMultipartyMode(self: &ParamsBGVRNS) -> MultipartyMode;
        fn GetMultiplicationTechnique(self: &ParamsBGVRNS) -> MultiplicationTechnique;
        fn GetMultiplicativeDepth(self: &ParamsBGVRNS) -> u32;
        fn GetNoiseEstimate(self: &ParamsBGVRNS) -> f64;
        fn GetNumAdversarialQueries(self: &ParamsBGVRNS) -> f64;
        fn GetNumLargeDigits(self: &ParamsBGVRNS) -> u32;
        fn GetPREMode(self: &ParamsBGVRNS) -> ProxyReEncryptionMode;
        fn GetPlaintextModulus(self: &ParamsBGVRNS) -> u64;
        fn GetRingDim(self: &ParamsBGVRNS) -> u32;
        fn GetScalingModSize(self: &ParamsBGVRNS) -> u32;
        fn GetScalingTechnique(self: &ParamsBGVRNS) -> ScalingTechnique;
        fn GetScheme(self: &ParamsBGVRNS) -> SCHEME;
        fn GetSecretKeyDist(self: &ParamsBGVRNS) -> SecretKeyDist;
        fn GetSecurityLevel(self: &ParamsBGVRNS) -> SecurityLevel;
        fn GetStandardDeviation(self: &ParamsBGVRNS) -> f32;
        fn GetStatisticalSecurity(self: &ParamsBGVRNS) -> f64;
        fn GetThresholdNumOfParties(self: &ParamsBGVRNS) -> u32;
        fn SetBatchSize(self: Pin<&mut ParamsBGVRNS>, batchSize0: u32);
        fn SetDecryptionNoiseMode(
            self: Pin<&mut ParamsBGVRNS>,
            decryptionNoiseMode0: DecryptionNoiseMode,
        );
        fn SetDesiredPrecision(self: Pin<&mut ParamsBGVRNS>, desiredPrecision0: f64);
        fn SetDigitSize(self: Pin<&mut ParamsBGVRNS>, digitSize0: u32);
        fn SetEncryptionTechnique(
            self: Pin<&mut ParamsBGVRNS>,
            encryptionTechnique0: EncryptionTechnique,
        );
        fn SetEvalAddCount(self: Pin<&mut ParamsBGVRNS>, evalAddCount0: u32);
        fn SetExecutionMode(self: Pin<&mut ParamsBGVRNS>, executionMode0: ExecutionMode);
        fn SetFirstModSize(self: Pin<&mut ParamsBGVRNS>, firstModSize0: u32);
        fn SetInteractiveBootCompressionLevel(
            self: Pin<&mut ParamsBGVRNS>,
            interactiveBootCompressionLevel0: COMPRESSION_LEVEL,
        );
        fn SetKeySwitchCount(self: Pin<&mut ParamsBGVRNS>, keySwitchCount0: u32);
        fn SetKeySwitchTechnique(self: Pin<&mut ParamsBGVRNS>, ksTech0: KeySwitchTechnique);
        fn SetMaxRelinSkDeg(self: Pin<&mut ParamsBGVRNS>, maxRelinSkDeg0: u32);
        fn SetMultipartyMode(self: Pin<&mut ParamsBGVRNS>, multipartyMode0: MultipartyMode);
        fn SetMultiplicationTechnique(
            self: Pin<&mut ParamsBGVRNS>,
            multiplicationTechnique0: MultiplicationTechnique,
        );
        fn SetMultiplicativeDepth(self: Pin<&mut ParamsBGVRNS>, multiplicativeDepth0: u32);
        fn SetNoiseEstimate(self: Pin<&mut ParamsBGVRNS>, noiseEstimate0: f64);
        fn SetNumAdversarialQueries(self: Pin<&mut ParamsBGVRNS>, numAdversarialQueries0: u32);
        fn SetNumLargeDigits(self: Pin<&mut ParamsBGVRNS>, numLargeDigits0: u32);
        fn SetPREMode(self: Pin<&mut ParamsBGVRNS>, PREMode0: ProxyReEncryptionMode);
        fn SetPlaintextModulus(self: Pin<&mut ParamsBGVRNS>, ptModulus0: u64);
        fn SetRingDim(self: Pin<&mut ParamsBGVRNS>, ringDim0: u32);
        fn SetScalingModSize(self: Pin<&mut ParamsBGVRNS>, scalingModSize0: u32);
        fn SetScalingTechnique(self: Pin<&mut ParamsBGVRNS>, scalTech0: ScalingTechnique);
        fn SetSecretKeyDist(self: Pin<&mut ParamsBGVRNS>, secretKeyDist0: SecretKeyDist);
        fn SetSecurityLevel(self: Pin<&mut ParamsBGVRNS>, securityLevel0: SecurityLevel);
        fn SetStandardDeviation(self: Pin<&mut ParamsBGVRNS>, standardDeviation0: f32);
        fn SetStatisticalSecurity(self: Pin<&mut ParamsBGVRNS>, statisticalSecurity0: u32);
        fn SetThresholdNumOfParties(self: Pin<&mut ParamsBGVRNS>, thresholdNumOfParties0: u32);

        // Generator functions
        fn GenParamsBGVRNS() -> UniquePtr<ParamsBGVRNS>;
        fn GenParamsBGVRNSbyVectorOfString(vals: &CxxVector<CxxString>) -> UniquePtr<ParamsBGVRNS>;
    }

    // ParamsCKKSRNS
    unsafe extern "C++" {
        fn GetBatchSize(self: &ParamsCKKSRNS) -> u32;
        fn GetDecryptionNoiseMode(self: &ParamsCKKSRNS) -> DecryptionNoiseMode;
        fn GetDesiredPrecision(self: &ParamsCKKSRNS) -> f64;
        fn GetDigitSize(self: &ParamsCKKSRNS) -> u32;
        fn GetEncryptionTechnique(self: &ParamsCKKSRNS) -> EncryptionTechnique;
        fn GetEvalAddCount(self: &ParamsCKKSRNS) -> u32;
        fn GetExecutionMode(self: &ParamsCKKSRNS) -> ExecutionMode;
        fn GetFirstModSize(self: &ParamsCKKSRNS) -> u32;
        fn GetInteractiveBootCompressionLevel(self: &ParamsCKKSRNS) -> COMPRESSION_LEVEL;
        fn GetKeySwitchCount(self: &ParamsCKKSRNS) -> u32;
        fn GetKeySwitchTechnique(self: &ParamsCKKSRNS) -> KeySwitchTechnique;
        fn GetMaxRelinSkDeg(self: &ParamsCKKSRNS) -> u32;
        fn GetMultipartyMode(self: &ParamsCKKSRNS) -> MultipartyMode;
        fn GetMultiplicationTechnique(self: &ParamsCKKSRNS) -> MultiplicationTechnique;
        fn GetMultiplicativeDepth(self: &ParamsCKKSRNS) -> u32;
        fn GetNoiseEstimate(self: &ParamsCKKSRNS) -> f64;
        fn GetNumAdversarialQueries(self: &ParamsCKKSRNS) -> f64;
        fn GetNumLargeDigits(self: &ParamsCKKSRNS) -> u32;
        fn GetPREMode(self: &ParamsCKKSRNS) -> ProxyReEncryptionMode;
        fn GetPlaintextModulus(self: &ParamsCKKSRNS) -> u64;
        fn GetRingDim(self: &ParamsCKKSRNS) -> u32;
        fn GetScalingModSize(self: &ParamsCKKSRNS) -> u32;
        fn GetScalingTechnique(self: &ParamsCKKSRNS) -> ScalingTechnique;
        fn GetScheme(self: &ParamsCKKSRNS) -> SCHEME;
        fn GetSecretKeyDist(self: &ParamsCKKSRNS) -> SecretKeyDist;
        fn GetSecurityLevel(self: &ParamsCKKSRNS) -> SecurityLevel;
        fn GetStandardDeviation(self: &ParamsCKKSRNS) -> f32;
        fn GetStatisticalSecurity(self: &ParamsCKKSRNS) -> f64;
        fn GetThresholdNumOfParties(self: &ParamsCKKSRNS) -> u32;
        fn SetBatchSize(self: Pin<&mut ParamsCKKSRNS>, batchSize0: u32);
        fn SetDecryptionNoiseMode(
            self: Pin<&mut ParamsCKKSRNS>,
            decryptionNoiseMode0: DecryptionNoiseMode,
        );
        fn SetDesiredPrecision(self: Pin<&mut ParamsCKKSRNS>, desiredPrecision0: f64);
        fn SetDigitSize(self: Pin<&mut ParamsCKKSRNS>, digitSize0: u32);
        fn SetEncryptionTechnique(
            self: Pin<&mut ParamsCKKSRNS>,
            encryptionTechnique0: EncryptionTechnique,
        );
        fn SetEvalAddCount(self: Pin<&mut ParamsCKKSRNS>, evalAddCount0: u32);
        fn SetExecutionMode(self: Pin<&mut ParamsCKKSRNS>, executionMode0: ExecutionMode);
        fn SetFirstModSize(self: Pin<&mut ParamsCKKSRNS>, firstModSize0: u32);
        fn SetInteractiveBootCompressionLevel(
            self: Pin<&mut ParamsCKKSRNS>,
            interactiveBootCompressionLevel0: COMPRESSION_LEVEL,
        );
        fn SetKeySwitchCount(self: Pin<&mut ParamsCKKSRNS>, keySwitchCount0: u32);
        fn SetKeySwitchTechnique(self: Pin<&mut ParamsCKKSRNS>, ksTech0: KeySwitchTechnique);
        fn SetMaxRelinSkDeg(self: Pin<&mut ParamsCKKSRNS>, maxRelinSkDeg0: u32);
        fn SetMultipartyMode(self: Pin<&mut ParamsCKKSRNS>, multipartyMode0: MultipartyMode);
        fn SetMultiplicationTechnique(
            self: Pin<&mut ParamsCKKSRNS>,
            multiplicationTechnique0: MultiplicationTechnique,
        );
        fn SetMultiplicativeDepth(self: Pin<&mut ParamsCKKSRNS>, multiplicativeDepth0: u32);
        fn SetNoiseEstimate(self: Pin<&mut ParamsCKKSRNS>, noiseEstimate0: f64);
        fn SetNumAdversarialQueries(self: Pin<&mut ParamsCKKSRNS>, numAdversarialQueries0: u32);
        fn SetNumLargeDigits(self: Pin<&mut ParamsCKKSRNS>, numLargeDigits0: u32);
        fn SetPREMode(self: Pin<&mut ParamsCKKSRNS>, PREMode0: ProxyReEncryptionMode);
        fn SetPlaintextModulus(self: Pin<&mut ParamsCKKSRNS>, ptModulus0: u64);
        fn SetRingDim(self: Pin<&mut ParamsCKKSRNS>, ringDim0: u32);
        fn SetScalingModSize(self: Pin<&mut ParamsCKKSRNS>, scalingModSize0: u32);
        fn SetScalingTechnique(self: Pin<&mut ParamsCKKSRNS>, scalTech0: ScalingTechnique);
        fn SetSecretKeyDist(self: Pin<&mut ParamsCKKSRNS>, secretKeyDist0: SecretKeyDist);
        fn SetSecurityLevel(self: Pin<&mut ParamsCKKSRNS>, securityLevel0: SecurityLevel);
        fn SetStandardDeviation(self: Pin<&mut ParamsCKKSRNS>, standardDeviation0: f32);
        fn SetStatisticalSecurity(self: Pin<&mut ParamsCKKSRNS>, statisticalSecurity0: u32);
        fn SetThresholdNumOfParties(self: Pin<&mut ParamsCKKSRNS>, thresholdNumOfParties0: u32);

        // Generator functions
        fn GenParamsCKKSRNS() -> UniquePtr<ParamsCKKSRNS>;
        fn GenParamsCKKSRNSbyVectorOfString(
            vals: &CxxVector<CxxString>,
        ) -> UniquePtr<ParamsCKKSRNS>;
    }

    // Plaintext
    unsafe extern "C++" {
        fn Decode(self: &Plaintext) -> bool;
        fn Encode(self: &Plaintext) -> bool;
        fn GetCoefPackedValue(self: &Plaintext) -> &CxxVector<i64>;
        fn GetCopyOfCKKSPackedValue(self: &Plaintext) -> UniquePtr<CxxVector<ComplexPair>>;
        fn GetLength(self: &Plaintext) -> usize;
        fn GetLevel(self: &Plaintext) -> usize;
        fn GetLogError(self: &Plaintext) -> f64;
        fn GetLogPrecision(self: &Plaintext) -> f64;
        fn GetNoiseScaleDeg(self: &Plaintext) -> usize;
        fn GetPackedValue(self: &Plaintext) -> &CxxVector<i64>;
        fn GetRealPackedValue(self: &Plaintext) -> UniquePtr<CxxVector<f64>>;
        fn GetScalingFactor(self: &Plaintext) -> f64;
        fn GetSchemeID(self: &Plaintext) -> SCHEME;
        fn GetSlots(self: &Plaintext) -> u32;
        fn GetString(self: &Plaintext) -> String;
        fn GetStringValue(self: &Plaintext) -> &CxxString;
        fn HighBound(self: &Plaintext) -> i64;
        fn IsEncoded(self: &Plaintext) -> bool;
        fn LowBound(self: &Plaintext) -> i64;
        fn SetFormat(self: &Plaintext, fmt: Format);
        fn SetIntVectorValue(self: &Plaintext, val: &CxxVector<i64>);
        fn SetLength(self: &Plaintext, newSize: usize);
        fn SetLevel(self: &Plaintext, l: usize);
        fn SetNoiseScaleDeg(self: &Plaintext, nsd: usize);
        fn SetScalingFactor(self: &Plaintext, sf: f64);
        fn SetSlots(self: &Plaintext, s: u32);
        fn SetStringValue(self: &Plaintext, value: &CxxString);

        // Generator functions
        fn GenNullPlainText() -> UniquePtr<Plaintext>;
    }

    // PublicKeyDCRTPoly
    unsafe extern "C++" {
        // Generator functions
        fn DCRTPolyGenNullPublicKey() -> UniquePtr<PublicKeyDCRTPoly>;
    }

    // PrivateKeyDCRTPoly
    unsafe extern "C++" {
        // Generator functions
        fn DCRTPolyGenNullPrivateKey() -> UniquePtr<PrivateKeyDCRTPoly>;
    }

    // TrapdoorPairDRCTPoly
    unsafe extern "C++" {
        fn GetMatrixR(self: &RLWETrapdoorPairDRCTPoly) -> UniquePtr<MatrixDCRTPoly>;
        fn GetMatrixE(self: &RLWETrapdoorPairDRCTPoly) -> UniquePtr<MatrixDCRTPoly>;
    }

    // Serialize / Deserialize
    unsafe extern "C++" {
        // Ciphertext
        fn DCRTPolyDeserializeCiphertextFromFile(
            ciphertextLocation: &CxxString,
            ciphertext: Pin<&mut CiphertextDCRTPoly>,
            serialMode: SerialMode,
        ) -> bool;
        fn DCRTPolySerializeCiphertextToFile(
            ciphertextLocation: &CxxString,
            ciphertext: &CiphertextDCRTPoly,
            serialMode: SerialMode,
        ) -> bool;

        // CryptoContextDCRTPoly
        fn DCRTPolyDeserializeCryptoContextFromFile(
            ccLocation: &CxxString,
            cryptoContext: Pin<&mut CryptoContextDCRTPoly>,
            serialMode: SerialMode,
        ) -> bool;
        fn DCRTPolySerializeCryptoContextToFile(
            ccLocation: &CxxString,
            cryptoContext: &CryptoContextDCRTPoly,
            serialMode: SerialMode,
        ) -> bool;

        // EvalAutomorphismKey
        fn DCRTPolyDeserializeEvalAutomorphismKeyFromFile(
            automorphismKeyLocation: &CxxString,
            serialMode: SerialMode,
        ) -> bool;
        fn DCRTPolySerializeEvalAutomorphismKeyByIdToFile(
            automorphismKeyLocation: &CxxString,
            serialMode: SerialMode,
            id: &CxxString,
        ) -> bool;
        fn DCRTPolySerializeEvalAutomorphismKeyToFile(
            automorphismKeyLocation: &CxxString,
            cryptoContext: &CryptoContextDCRTPoly,
            serialMode: SerialMode,
        ) -> bool;

        // EvalMultKey
        fn DCRTPolyDeserializeEvalMultKeyFromFile(
            multKeyLocation: &CxxString,
            serialMode: SerialMode,
        ) -> bool;
        fn DCRTPolySerializeEvalMultKeyByIdToFile(
            multKeyLocation: &CxxString,
            serialMode: SerialMode,
            id: &CxxString,
        ) -> bool;
        fn DCRTPolySerializeEvalMultKeyToFile(
            multKeyLocation: &CxxString,
            cryptoContext: &CryptoContextDCRTPoly,
            serialMode: SerialMode,
        ) -> bool;

        // EvalSumKey
        fn DCRTPolyDeserializeEvalSumKeyFromFile(
            sumKeyLocation: &CxxString,
            serialMode: SerialMode,
        ) -> bool;
        fn DCRTPolySerializeEvalSumKeyByIdToFile(
            sumKeyLocation: &CxxString,
            serialMode: SerialMode,
            id: &CxxString,
        ) -> bool;
        fn DCRTPolySerializeEvalSumKeyToFile(
            sumKeyLocation: &CxxString,
            cryptoContext: &CryptoContextDCRTPoly,
            serialMode: SerialMode,
        ) -> bool;

        // PublicKey
        fn DCRTPolyDeserializePublicKeyFromFile(
            publicKeyLocation: &CxxString,
            publicKey: Pin<&mut PublicKeyDCRTPoly>,
            serialMode: SerialMode,
        ) -> bool;
        fn DCRTPolySerializePublicKeyToFile(
            publicKeyLocation: &CxxString,
            publicKey: &PublicKeyDCRTPoly,
            serialMode: SerialMode,
        ) -> bool;

        // PrivateKey
        fn DCRTPolyDeserializePrivateKeyFromFile(
            privateKeyLocation: &CxxString,
            privateKey: Pin<&mut PrivateKeyDCRTPoly>,
            serialMode: SerialMode,
        ) -> bool;
        fn DCRTPolySerializePrivateKeyToFile(
            privateKeyLocation: &CxxString,
            privateKey: &PrivateKeyDCRTPoly,
            serialMode: SerialMode,
        ) -> bool;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    // TODO: add more tests
    #[test]
    fn SimpleIntegersExample() {
        let mut _cc_params_bfvrns = ffi::GenParamsBFVRNS();
        _cc_params_bfvrns.pin_mut().SetPlaintextModulus(65537);
        _cc_params_bfvrns.pin_mut().SetMultiplicativeDepth(2);

        let _cc = ffi::DCRTPolyGenCryptoContextByParamsBFVRNS(&_cc_params_bfvrns);
        _cc.EnableByFeature(ffi::PKESchemeFeature::PKE);
        _cc.EnableByFeature(ffi::PKESchemeFeature::KEYSWITCH);
        _cc.EnableByFeature(ffi::PKESchemeFeature::LEVELEDSHE);

        let _key_pair = _cc.KeyGen();
        _cc.EvalMultKeyGen(&_key_pair.GetPrivateKey());

        let mut _index_list = CxxVector::<i32>::new();
        _index_list.pin_mut().push(1);
        _index_list.pin_mut().push(2);
        _index_list.pin_mut().push(-1);
        _index_list.pin_mut().push(-2);
        _cc.EvalRotateKeyGen(
            &_key_pair.GetPrivateKey(),
            &_index_list,
            &ffi::DCRTPolyGenNullPublicKey(),
        );

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

        let _cipher_text_1 = _cc.EncryptByPublicKey(&_key_pair.GetPublicKey(), &_plain_text_1);
        let _cipher_text_2 = _cc.EncryptByPublicKey(&_key_pair.GetPublicKey(), &_plain_text_2);
        let _cipher_text_3 = _cc.EncryptByPublicKey(&_key_pair.GetPublicKey(), &_plain_text_3);

        let _cipher_text_add_1_2 = _cc.EvalAddByCiphertexts(&_cipher_text_1, &_cipher_text_2);
        let _cipher_text_add_result =
            _cc.EvalAddByCiphertexts(&_cipher_text_add_1_2, &_cipher_text_3);

        let _cipher_text_mul_1_2 = _cc.EvalMultByCiphertexts(&_cipher_text_1, &_cipher_text_2);
        let _cipher_text_mult_result =
            _cc.EvalMultByCiphertexts(&_cipher_text_mul_1_2, &_cipher_text_3);

        let _cipher_text_rot_1 = _cc.EvalRotate(&_cipher_text_1, 1);
        let _cipher_text_rot_2 = _cc.EvalRotate(&_cipher_text_1, 2);
        let _cipher_text_rot_3 = _cc.EvalRotate(&_cipher_text_1, -1);
        let _cipher_text_rot_4 = _cc.EvalRotate(&_cipher_text_1, -2);

        let mut _plain_text_add_result = ffi::GenNullPlainText();
        _cc.DecryptByPrivateKeyAndCiphertext(
            &_key_pair.GetPrivateKey(),
            &_cipher_text_add_result,
            _plain_text_add_result.pin_mut(),
        );
        let mut _plain_text_mult_result = ffi::GenNullPlainText();
        _cc.DecryptByPrivateKeyAndCiphertext(
            &_key_pair.GetPrivateKey(),
            &_cipher_text_mult_result,
            _plain_text_mult_result.pin_mut(),
        );
        let mut _plain_text_rot_1 = ffi::GenNullPlainText();
        _cc.DecryptByPrivateKeyAndCiphertext(
            &_key_pair.GetPrivateKey(),
            &_cipher_text_rot_1,
            _plain_text_rot_1.pin_mut(),
        );
        let mut _plain_text_rot_2 = ffi::GenNullPlainText();
        _cc.DecryptByPrivateKeyAndCiphertext(
            &_key_pair.GetPrivateKey(),
            &_cipher_text_rot_2,
            _plain_text_rot_2.pin_mut(),
        );
        let mut _plain_text_rot_3 = ffi::GenNullPlainText();
        _cc.DecryptByPrivateKeyAndCiphertext(
            &_key_pair.GetPrivateKey(),
            &_cipher_text_rot_3,
            _plain_text_rot_3.pin_mut(),
        );
        let mut _plain_text_rot_4 = ffi::GenNullPlainText();
        _cc.DecryptByPrivateKeyAndCiphertext(
            &_key_pair.GetPrivateKey(),
            &_cipher_text_rot_4,
            _plain_text_rot_4.pin_mut(),
        );

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
        println!(
            "Left rotation of #1 by 1: {}",
            _plain_text_rot_1.GetString()
        );
        println!(
            "Left rotation of #1 by 2: {}",
            _plain_text_rot_2.GetString()
        );
        println!(
            "Right rotation of #1 by -1: {}",
            _plain_text_rot_3.GetString()
        );
        println!(
            "Right rotation of #1 by -2: {}",
            _plain_text_rot_4.GetString()
        );
    }

    #[test]
    fn SimpleRealNumbersExample() {
        let _mult_depth: u32 = 1;
        let _scale_mod_size: u32 = 50;
        let _batch_size: u32 = 8;

        let mut _cc_params_ckksrns = ffi::GenParamsCKKSRNS();
        _cc_params_ckksrns
            .pin_mut()
            .SetMultiplicativeDepth(_mult_depth);
        _cc_params_ckksrns
            .pin_mut()
            .SetScalingModSize(_scale_mod_size);
        _cc_params_ckksrns.pin_mut().SetBatchSize(_batch_size);

        let _cc = ffi::DCRTPolyGenCryptoContextByParamsCKKSRNS(&_cc_params_ckksrns);
        _cc.EnableByFeature(ffi::PKESchemeFeature::PKE);
        _cc.EnableByFeature(ffi::PKESchemeFeature::KEYSWITCH);
        _cc.EnableByFeature(ffi::PKESchemeFeature::LEVELEDSHE);

        println!(
            "CKKS scheme is using ring dimension {}\n",
            _cc.GetRingDimension()
        );

        let _key_pair = _cc.KeyGen();
        _cc.EvalMultKeyGen(&_key_pair.GetPrivateKey());
        let mut _index_list = CxxVector::<i32>::new();
        _index_list.pin_mut().push(1);
        _index_list.pin_mut().push(-2);
        _cc.EvalRotateKeyGen(
            &_key_pair.GetPrivateKey(),
            &_index_list,
            &ffi::DCRTPolyGenNullPublicKey(),
        );

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

        let _dcrt_poly_params = ffi::DCRTPolyGenNullParams();
        let _p_txt_1 =
            _cc.MakeCKKSPackedPlaintextByVectorOfDouble(&_x_1, 1, 0, &_dcrt_poly_params, 0);
        let _p_txt_2 =
            _cc.MakeCKKSPackedPlaintextByVectorOfDouble(&_x_2, 1, 0, &_dcrt_poly_params, 0);

        println!("Input x1: {}", _p_txt_1.GetString());
        println!("Input x2: {}", _p_txt_2.GetString());

        let _c1 = _cc.EncryptByPublicKey(&_key_pair.GetPublicKey(), &_p_txt_1);
        let _c2 = _cc.EncryptByPublicKey(&_key_pair.GetPublicKey(), &_p_txt_2);

        let _c_add = _cc.EvalAddByCiphertexts(&_c1, &_c2);
        let _c_sub = _cc.EvalSubByCiphertexts(&_c1, &_c2);
        let _c_scalar = _cc.EvalMultByCiphertextAndConst(&_c1, 4.0);
        let _c_mul = _cc.EvalMultByCiphertexts(&_c1, &_c2);
        let _c_rot_1 = _cc.EvalRotate(&_c1, 1);
        let _c_rot_2 = _cc.EvalRotate(&_c1, -2);

        let mut _result = ffi::GenNullPlainText();
        println!("\nResults of homomorphic computations:");

        _cc.DecryptByPrivateKeyAndCiphertext(&_key_pair.GetPrivateKey(), &_c1, _result.pin_mut());
        _result.SetLength(_batch_size.try_into().unwrap());
        println!(
            "x1 = {}Estimated precision in bits: {}",
            _result.GetString(),
            _result.GetLogPrecision()
        );

        _cc.DecryptByPrivateKeyAndCiphertext(
            &_key_pair.GetPrivateKey(),
            &_c_add,
            _result.pin_mut(),
        );
        _result.SetLength(_batch_size.try_into().unwrap());
        println!(
            "x1 + x2 = {}Estimated precision in bits: {}",
            _result.GetString(),
            _result.GetLogPrecision()
        );

        _cc.DecryptByPrivateKeyAndCiphertext(
            &_key_pair.GetPrivateKey(),
            &_c_sub,
            _result.pin_mut(),
        );
        _result.SetLength(_batch_size.try_into().unwrap());
        println!("x1 - x2 = {}", _result.GetString());

        _cc.DecryptByPrivateKeyAndCiphertext(
            &_key_pair.GetPrivateKey(),
            &_c_scalar,
            _result.pin_mut(),
        );
        _result.SetLength(_batch_size.try_into().unwrap());
        println!("4 * x1 = {}", _result.GetString());

        _cc.DecryptByPrivateKeyAndCiphertext(
            &_key_pair.GetPrivateKey(),
            &_c_mul,
            _result.pin_mut(),
        );
        _result.SetLength(_batch_size.try_into().unwrap());
        println!("x1 * x2 = {}", _result.GetString());

        _cc.DecryptByPrivateKeyAndCiphertext(
            &_key_pair.GetPrivateKey(),
            &_c_rot_1,
            _result.pin_mut(),
        );
        _result.SetLength(_batch_size.try_into().unwrap());
        println!("\nIn rotations, very small outputs (~10^-10 here) correspond to 0's:");
        println!("x1 rotate by 1 = {}", _result.GetString());

        _cc.DecryptByPrivateKeyAndCiphertext(
            &_key_pair.GetPrivateKey(),
            &_c_rot_2,
            _result.pin_mut(),
        );
        _result.SetLength(_batch_size.try_into().unwrap());
        println!("x1 rotate by -2 = {}", _result.GetString());
    }

    #[test]
    fn PolynomialEvaluationExample() {
        use std::time::Instant;
        println!("\n======EXAMPLE FOR EVALPOLY========\n");

        let mut _cc_params_ckksrns = ffi::GenParamsCKKSRNS();
        _cc_params_ckksrns.pin_mut().SetMultiplicativeDepth(6);
        _cc_params_ckksrns.pin_mut().SetScalingModSize(50);

        let _cc = ffi::DCRTPolyGenCryptoContextByParamsCKKSRNS(&_cc_params_ckksrns);
        _cc.EnableByFeature(ffi::PKESchemeFeature::PKE);
        _cc.EnableByFeature(ffi::PKESchemeFeature::KEYSWITCH);
        _cc.EnableByFeature(ffi::PKESchemeFeature::LEVELEDSHE);
        _cc.EnableByFeature(ffi::PKESchemeFeature::ADVANCEDSHE);

        let mut _input = CxxVector::<ffi::ComplexPair>::new();
        _input.pin_mut().push(ffi::ComplexPair { re: 0.5, im: 0.0 });
        _input.pin_mut().push(ffi::ComplexPair { re: 0.7, im: 0.0 });
        _input.pin_mut().push(ffi::ComplexPair { re: 0.9, im: 0.0 });
        _input
            .pin_mut()
            .push(ffi::ComplexPair { re: 0.95, im: 0.0 });
        _input
            .pin_mut()
            .push(ffi::ComplexPair { re: 0.93, im: 0.0 });
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

        let _dcrt_poly_params = ffi::DCRTPolyGenNullParams();
        let _plain_text_1 =
            _cc.MakeCKKSPackedPlaintextByVectorOfComplex(&_input, 1, 0, &_dcrt_poly_params, 0);
        let _key_pair = _cc.KeyGen();
        print!("Generating evaluation key for homomorphic multiplication...");
        _cc.EvalMultKeyGen(&_key_pair.GetPrivateKey());
        println!("Completed.\n");
        let _cipher_text_1 = _cc.EncryptByPublicKey(&_key_pair.GetPublicKey(), &_plain_text_1);

        let mut _start = Instant::now();
        let _result = _cc.EvalPoly(&_cipher_text_1, &_coefficients_1);
        let _time_eval_poly_1 = _start.elapsed();

        _start = Instant::now();
        let _result_2 = _cc.EvalPoly(&_cipher_text_1, &_coefficients_2);
        let _time_eval_poly_2 = _start.elapsed();

        let mut _plain_text_dec = ffi::GenNullPlainText();
        _cc.DecryptByPrivateKeyAndCiphertext(
            &_key_pair.GetPrivateKey(),
            &_result,
            _plain_text_dec.pin_mut(),
        );
        _plain_text_dec.SetLength(_encoded_length);
        let mut _plain_text_dec_2 = ffi::GenNullPlainText();
        _cc.DecryptByPrivateKeyAndCiphertext(
            &_key_pair.GetPrivateKey(),
            &_result_2,
            _plain_text_dec_2.pin_mut(),
        );
        _plain_text_dec_2.SetLength(_encoded_length);

        println!("\n Original Plaintext #1:");
        println!("{}", _plain_text_1.GetString());
        println!(
            "\n Result of evaluating a polynomial with coefficients [{} ]",
            _coefficients_1
                .iter()
                .fold(String::new(), |acc, &arg| acc + " " + &arg.to_string())
        );
        println!("{}", _plain_text_dec.GetString());
        println!(
            "\n Expected result: (0.70519107, 1.38285078, 3.97211180, 5.60215665, 4.86357575)"
        );
        println!("\n Evaluation time: {:.0?}", _time_eval_poly_1);
        println!(
            "\n Result of evaluating a polynomial with coefficients [{} ]",
            _coefficients_2
                .iter()
                .fold(String::new(), |acc, &arg| acc + " " + &arg.to_string())
        );
        println!("{}\n", _plain_text_dec_2.GetString());
        println!(" Expected result: (3.4515092326, 5.3752765397, 4.8993108833, 3.2495023573, 4.0485229982)");
        print!("\n Evaluation time: {:.0?}\n", _time_eval_poly_2);
    }
}
