# Installation

You can use this library as a cargo crate from [crates.io](https://crates.io/crates/openfhe) or build it from the source.

In both cases, you need to have the core OpenFHE library installed on your system to support the low-level optimizations.

## Prerequisites
    
Ensure you have the following dependencies installed:

* `CMake >= 3.5.1`
* `Clang >= 12.0` or `GCC >= 11.4`
* `Rust >= 1.78`
* `Git`

### Unix

On Debian-based systems, you can install the necessary dependencies using:

```bash
sudo apt install build-essential libssl-dev cmake clang git
```

## Installation process
### Core OpenFHE library installation

To build and install the OpenFHE library, follow the steps below or refer to [OpenFHE's installation documentation](https://openfhe-development.readthedocs.io/en/latest/sphinx_rsts/intro/installation/installation.html).

1. Clone the repository

```bash
git clone https://github.com/openfheorg/openfhe-development.git
cd openfhe-development
```

2. Configure CMake

```bash
cmake -B ${OPENFHE_BUILD:-build} -DBUILD_SHARED=ON .       
```

3. Build and install the C++ OpenFHE library

```bash
make -C ${OPENFHE_BUILD:-build} -j$(nproc)
make -C ${OPENFHE_BUILD:-build} install
```

4. Update the cache for the linker

```bash
sudo ldconfig
```

## Configuring your project to use the crate

To use the OpenFHE crate in your Rust project, add it as a dependency from [crates.io](https://crates.io/crates/openfhe):

```bash
cargo add openfhe
```

You also need to add a small piece of code for the core dependencies' configuration in your `build.rs` file:

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

You can adjust the installation process by building the crate manually.
In that case, you need to clone the Fair Math's [openfhe-rs](https://github.com/fairmath/openfhe-rs) repo to your local machine and build it:

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
cargo run --example function_evaluation
cargo run --example polynomial_evaluation
cargo run --example simple_integers
cargo run --example simple_real_integers
```

# License

`OpenFHE-rs` is licensed under the **BSD 2-Clause License**.
See the [LICENSE](LICENSE) file for more details.
