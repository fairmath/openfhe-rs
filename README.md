# About OpenFHE-rs
☀️ *OpenFHE-rs is a joint project by [FairMath](https://fairmath.xyz/) & [OpenFHE](https://www.openfhe.org/)*

---
[![Discord](https://img.shields.io/discord/1163764915803279360?logo=discord&label=Fair%20Math)](https://discord.com/invite/NfhXwyr9M5)
[![Twitter](https://img.shields.io/twitter/follow/FairMath)](https://twitter.com/FairMath)

🔔 *Keep in mind that the library is WIP and may contain some unpolished interfaces. If you struggle with anything or have suggestions, feel free to ping us on our Discord server or open a new issue in the [Github repository](https://github.com/fairmath/openfhe-rs/tree/master).*

---

OpenFHE-rs is a Rust interface for the OpenFHE library. OpenFHE is known for its wide range of Fully Homomorphic Encryption (FHE) schemes, 
all implemented in C++. We're bringing this capability to Rust developers.

By offering a Rust wrapper for OpenFHE, we make it easier for Rust devs to use advanced FHE schemes in their projects. 
Whether you're building secure data processing apps or privacy-focused tools, OpenFHE-rs helps you do that with the power of OpenFHE's encryption technology.

# Installation

You can use this library as a cargo crate from [crates.io](https://crates.io/crates/openfhe) or build it from the source.

In both cases you need to have the core OpenFHE library installed on your system to support the low-level optimizations.

## Install dependencies
    
* CMake >= 3.5.1
* Clang >= 12.0 or GCC >= 11.4
* Rust >= 1.78
* Git

### Unix

On Debian systems, everything can be installed with the following command:

```bash
sudo apt install build-essential libssl-dev cmake clang git
```

## Installation process

### Core OpenFHE library installation

Build and install OpenFHE library. Right now you need to use the Fair Math fork. It contains the required features, which will be included in the next planned release (v1.1.5):

1. Clone the repository

```bash
git clone https://github.com/openfheorg/openfhe-development.git
cd openfhe-development
```

2. Configure CMake

```bash
cmake -B ${OPENFHE_BUILD:-build} -DBUILD_EXAMPLES=ON -DBUILD_EXTRAS=ON -DBUILD_SHARED=ON .       
```

3. Build and install the C++ OpenFHE library

```bash
make -C ${OPENFHE_BUILD:-build} -j$(nproc)
make -C ${OPENFHE_BUILD:-build} install
```

4. Configure your dynamic linker

```bash
sudo ldconfig
```

## Configuring your project to use the crate

To get the cargo crate from [crates.io](https://crates.io/crates/openfhe), you need to add it as a dependency to you project:

```bash
cargo add openfhe
```

You also need to add a small piece of code for core dependencies configuration in your build.rs file:

```rs
fn main
{
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
```

### Template repository

Instead of doing it manually, you start your project by forking our [template repository](https://github.com/fairmath/openfhe-rs-template/tree/main).

# Custom crate installation from source

You can adjust the installation process by building the crate mannually. In that case you need to clone the Fair Math [openfhe-rs](https://github.com/fairmath/openfhe-rs) repo to your local machine and build it:

1. Clone the repository
```bash
git clone https://github.com/fairmath/openfhe-rs.git
cd openfhe-rs
```

2. Build the library
```bash
cargo build
```

3. Run tests
```bash
cargo test -- --test-threads=1
```

4. Run the examples
```bash
cargo run --example polynomial_evaluation
```
