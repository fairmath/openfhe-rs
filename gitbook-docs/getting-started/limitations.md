---
description:
---

# Limitations
## OpenFHE

See the [Security Notes for Homomorphic Encryption](https://openfhe-development.readthedocs.io/en/latest/sphinx_rsts/intro/security.html) in OpenFHE's documentation.

## Rust wrapper

The library is WIP and may contain some unpolished interfaces. If you struggle with anything or have suggestions, feel free to ping us on our Discord server or open a new issue in the [Github repository](https://github.com/fairmath/openfhe-rs/tree/master). 

At the moment, only a certain set of OpenFHE functionality has been implemented.
We use [CXX crate](https://cxx.rs/) for our Rust binding to reduce the amount of abstraction levels.OpenFHE types are represented as opaque types on the Rust side using [cxx::UniquePtr](https://docs.rs/cxx/latest/cxx/struct.UniquePtr.html) from the CXX crate.
Instead of the usual [std::vec](https://doc.rust-lang.org/std/vec/), we use [cxx::vector](https://docs.rs/cxx/latest/cxx/struct.CxxVector.html).
The main difference lies in the initialization method: you need to init the vector element by element, otherwise, it will be stored in memory twice.
Currently only supported CxxVector of the primitive and "ComplexPair" types.
Since Rust does not support default parameters and function overloading, default parameters are mentioned in comments after the
corresponding parameter name and overloaded library functions are represented by slightly different names.
Calling member functions on generated empty types (those generated with GenEmptyPlainText() and GenEmptyCryptoContext()) results in undefined behavior.
Since CXX crate has limited support for function pointers (only functions without a return type are supported), EvalChebychevFunction expects fn(f64, ret: &mut f64) as the callable object.
