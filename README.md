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

## Install Dependencies
    
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

1. Build and install OpenFHE library. Right now you need to use the Fair Math fork. It contains required features, which will be included in the next planned release (v1.1.5):

   1. Clone the repository

   ```bash
   git clone https://github.com/fairmath/openfhe.git
   cd openfhe
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
2. Make sure you have [rustc](https://www.rust-lang.org/tools/install) with `cargo` installed first.

3. Clone the Fair Math [openfhe-rs](https://github.com/fairmath/openfhe-rs) repo to your local machine and build:
   1. Clone the repository
   ```bash
   git clone https://github.com/fairmath/openfhe-rs.git
   cd openfhe-rs
   ```

   2. Configure your dynamic linker
   ```bash
   sudo ldconfig
   ```

   3. Build the library
   ```bash
   cargo build
   ```

   4. Run tests
   ```bash
   cargo test -- --test-threads=1
   ```

   5. Run the examples

   ```bash
   cargo run --example polynomial_evaluation
   ```
