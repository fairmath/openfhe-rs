# About OpenFHE-rs
☀️ *OpenFHE-rs is a joint project by [FairMath](https://fairmath.xyz/) & [OpenFHE](https://www.openfhe.org/)*

---

OpenFHE-rs is a Rust interface for the OpenFHE library. OpenFHE is known for its wide range of Fully Homomorphic Encryption (FHE) schemes, 
all implemented in C++. We're bringing this capability to Rust developers.

By offering a Rust wrapper for OpenFHE, we make it easier for Rust devs to use advanced FHE schemes in their projects. 
Whether you're building secure data processing apps or privacy-focused tools, OpenFHE-rs helps you do that with the power of OpenFHE's encryption technology.

# Current status

The library is under development and the ETA of the first version is set to Q2 2024.

# Installation from source

1. Build and install OpenFHE library using the [official docs](https://openfhe-development.readthedocs.io/en/latest/sphinx_rsts/intro/installation/installation.html#):
   1. Build OpenFHE as shared libraries;
   2. Don't specify an installation path (If no installation path is provided in Ubuntu (and many other Unix-based OSes),
        the header and library binary files will be placed in /usr/local/include/openfhe and /usr/local/lib, respectively);
2. Make sure that `build.rs` file has the correct paths to shared libraries(OpenFHE) and libgomp(GNU Offloading and Multi Processing Runtime Library);
3. run `cargo build`