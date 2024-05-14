fn main()
{
    cxx_build::bridge("src/lib.rs")
        .file("src/bindings.cc")
        .include("/usr/local/include/openfhe")
        .include("/usr/local/include/openfhe/third-party/include")
        .include("/usr/local/include/openfhe/core")
        .include("/usr/local/include/openfhe/pke")
        .include("/usr/local/include/openfhe/binfhe")
        .flag_if_supported("-std=c++17")
        .flag_if_supported("-Wall")
        .flag_if_supported("-Werror")
        .flag_if_supported("-O3")
        .flag_if_supported("-Wno-parentheses") // [-Wparentheses]
        .flag_if_supported("-Wno-unused-parameter") // [-Wunused-parameter]
        .flag_if_supported("-Wno-missing-field-initializers") // [-Wmissing-field-initializers]
        .flag_if_supported("-Wno-unused-function") // [-Wunused-function]
        .compile("openfhe");

    println!("cargo::rerun-if-changed=src/lib.rs");
    println!("cargo::rerun-if-changed=src/bindings.hpp");
    println!("cargo::rerun-if-changed=src/bindings.cc");

    // linking openFHE
    println!("cargo::rustc-link-arg=-L/usr/local/lib");
    println!("cargo::rustc-link-arg=-lOPENFHEpke");
    println!("cargo::rustc-link-arg=-lOPENFHEbinfhe");
    println!("cargo::rustc-link-arg=-lOPENFHEcore");

    // linking OpenMP
    println!("cargo::rustc-link-arg=-fopenmp");
    
    // necessary to avoid LD_LIBRARY_PATH
    println!("cargo::rustc-link-arg=-Wl,-rpath=/usr/local/lib");
}
