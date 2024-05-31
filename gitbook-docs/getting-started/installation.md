# Installation

You can use this library as a cargo crate from [crates.io](https://crates.io/crates/openfhe) or build it from the source.

In both cases, you need to have the core OpenFHE library installed on your system to support the low-level optimizations.

## Install dependencies
    
* CMake >= `3.5.1`
* Clang >= `12.0` or GCC >= `11.4`
* Rust >= `1.78`
* Git

### Unix

On Debian systems, everything can be installed with the following command:

```bash
sudo apt install build-essential libssl-dev cmake clang git
```

## Installation process
### Core OpenFHE library installation

Right now you need to use the Fair Math's fork of the OpenFHE library. It contains the required features, which will be included in the next planned release (`v1.1.5`):

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

4. Configure your dynamic linker

```bash
sudo ldconfig
```

## Configuring your project to use the crate

To get the cargo crate from [crates.io](https://crates.io/crates/openfhe), you need to add it as a dependency to your project:

```bash
cargo add openfhe
```

You also need to add a small piece of code for core dependencies configuration in your `build.rs` file:

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

Instead of doing it manually, you can start your project by forking our [template repository](https://github.com/fairmath/openfhe-rs-template/tree/main).

# Custom crate installation from the source

You can adjust the installation process by building the crate manually. In that case, you need to clone the Fair Math [openfhe-rs](https://github.com/fairmath/openfhe-rs) repo to your local machine and build it:

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
