---
description: Our toolchain is not perfect (yet)
---

# Limitations

The backbone of our ecosystem is the [OpenFHE-rs](../) crate for FHE-enabled apps development. We are developing it in collaboration with the [OpenFHE](https://www.openfhe.org/) research team, which allows us to concentrate on developing web3-related dev-tools and perform advanced protocol research.

In other words, we develop the crate as a Rust binding to the core [C++ OpenFHE library](https://github.com/openfheorg/openfhe-development/). This gives us the ability to reuse vast results of the OpenFHE team and give the Rust community access to the most advanced existing cryptography library.

At the same time, we do have some limitations in the interfaces, as we seek to avoid any extra memory consumption and computational overheads. FHE algorithms often operate with huge data containers and its crucial not to copy them unless absolutely necessary.

At the moment, only a certain set of OpenFHE functionality has been implemented.
We use [CXX crate](https://cxx.rs/) for our Rust binding to reduce the amount of abstraction levels.
OpenFHE types represented as opaque types on the Rust side using [cxx::UniquePtr](https://docs.rs/cxx/latest/cxx/struct.UniquePtr.html) from the CXX crate.
Instead of the usual [std::vec](https://doc.rust-lang.org/std/vec/), we use [cxx::vector](https://docs.rs/cxx/latest/cxx/struct.CxxVector.html).
The main difference lies in the initialization method: you need to init the vector element by element, otherwise it will be stored in memory twice.
Currently only supported CxxVector of the primitive and "ComplexPair" types.
Since Rust does not support default parameters and function overloading, default parameters are mentioned in comments after the
corresponding parameter name and overloaded library functions are represented by slightly different names.
Calling member functions on generated empty types (those generated with GenEmptyPlainText() and GenEmptyCryptoContext()) results in undefined behavior.
Since CXX crate has limited support for function pointers (only functions without a return type are supported), EvalChebychevFunction expects fn(f64, ret: &mut f64) as the callable object.
