fn main()
{
    cxx_build::bridge("src/lib.rs")
        .file("src/AssociativeContainers.cc")
        .file("src/Ciphertext.cc")
        .file("src/CryptoContext.cc")
        .file("src/CryptoParametersBase.cc")
        .file("src/DCRTPoly.cc")
        .file("src/DecryptResult.cc")
        .file("src/EncodingParams.cc")
        .file("src/EvalKey.cc")
        .file("src/KeyPair.cc")
        .file("src/LWEPrivateKey.cc")
        .file("src/Params.cc")
        .file("src/Plaintext.cc")
        .file("src/PrivateKey.cc")
        .file("src/PublicKey.cc")
        .file("src/SchemeBase.cc")
        .file("src/SequenceContainers.cc")
        .file("src/SerialDeserial.cc")
        .include("/usr/local/include/openfhe")
        .include("/usr/local/include/openfhe/third-party/include")
        .include("/usr/local/include/openfhe/core")
        .include("/usr/local/include/openfhe/pke")
        .include("/usr/local/include/openfhe/binfhe")
        .include("./openfhe-development/install/include")
        .include("./openfhe-development/install/include/openfhe")
        .include("./openfhe-development/install/include/openfhe/third-party/include")
        .include("./openfhe-development/install/include/openfhe/core")
        .include("./openfhe-development/install/include/openfhe/pke")
        .include("./openfhe-development/install/include/openfhe/binfhe")
        .flag_if_supported("-std=c++17")
        .flag_if_supported("-Wall")
        .flag_if_supported("-Werror")
        .flag_if_supported("-O3")
        .flag_if_supported("-fopenmp") // [-Wunknown-pragmas]
        .flag_if_supported("-Wno-parentheses") // [-Wparentheses]
        .flag_if_supported("-Wno-unused-parameter") // [-Wunused-parameter]
        .flag_if_supported("-Wno-missing-field-initializers") // [-Wmissing-field-initializers]
        .flag_if_supported("-Wno-unused-function") // [-Wunused-function]
        .compile("openfhe");

    println!("cargo::rerun-if-changed=src/lib.rs");
    println!("cargo::rerun-if-changed=src/AssociativeContainers.h");
    println!("cargo::rerun-if-changed=src/AssociativeContainers.cc");
    println!("cargo::rerun-if-changed=src/Ciphertext.h");
    println!("cargo::rerun-if-changed=src/Ciphertext.cc");
    println!("cargo::rerun-if-changed=src/CryptoContext.h");
    println!("cargo::rerun-if-changed=src/CryptoContext.cc");
    println!("cargo::rerun-if-changed=src/CryptoParametersBase.h");
    println!("cargo::rerun-if-changed=src/CryptoParametersBase.cc");
    println!("cargo::rerun-if-changed=src/DCRTPoly.h");
    println!("cargo::rerun-if-changed=src/DCRTPoly.cc");
    println!("cargo::rerun-if-changed=src/DecryptResult.h");
    println!("cargo::rerun-if-changed=src/DecryptResult.cc");
    println!("cargo::rerun-if-changed=src/EncodingParams.h");
    println!("cargo::rerun-if-changed=src/EncodingParams.cc");
    println!("cargo::rerun-if-changed=src/EvalKey.h");
    println!("cargo::rerun-if-changed=src/EvalKey.cc");
    println!("cargo::rerun-if-changed=src/KeyPair.h");
    println!("cargo::rerun-if-changed=src/KeyPair.cc");
    println!("cargo::rerun-if-changed=src/LWEPrivateKey.h");
    println!("cargo::rerun-if-changed=src/LWEPrivateKey.cc");
    println!("cargo::rerun-if-changed=src/Params.h");
    println!("cargo::rerun-if-changed=src/Params.cc");
    println!("cargo::rerun-if-changed=src/Plaintext.h");
    println!("cargo::rerun-if-changed=src/Plaintext.cc");
    println!("cargo::rerun-if-changed=src/PrivateKey.h");
    println!("cargo::rerun-if-changed=src/PrivateKey.cc");
    println!("cargo::rerun-if-changed=src/PublicKey.h");
    println!("cargo::rerun-if-changed=src/PublicKey.cc");
    println!("cargo::rerun-if-changed=src/SchemeBase.h");
    println!("cargo::rerun-if-changed=src/SchemeBase.cc");
    println!("cargo::rerun-if-changed=src/SequenceContainers.h");
    println!("cargo::rerun-if-changed=src/SequenceContainers.cc");
    println!("cargo::rerun-if-changed=src/SerialDeserial.h");
    println!("cargo::rerun-if-changed=src/SerialDeserial.cc");

    // linking openFHE
    println!("cargo::rustc-link-arg=-L/usr/local/lib");
    println!("cargo::rustc-link-arg=-L./openfhe-development/install/lib");
    println!("cargo::rustc-link-arg=-lOPENFHEpke");
    println!("cargo::rustc-link-arg=-lOPENFHEbinfhe");
    println!("cargo::rustc-link-arg=-lOPENFHEcore");

    // linking OpenMP
    println!("cargo::rustc-link-arg=-fopenmp");
    
    // necessary to avoid LD_LIBRARY_PATH
    println!("cargo::rustc-link-arg=-Wl,-rpath=/usr/local/lib");
}
