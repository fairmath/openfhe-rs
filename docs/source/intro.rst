
About OpenFHE-rs
================

☀️ *OpenFHE-rs is a joint project by `FairMath <https://fairmath.xyz/>`__ & `OpenFHE <https://www.openfhe.org/>`__.*

---

🔔 *Keep in mind that the library is WIP and may contain some unpolished interfaces. If you encounter any issues or have any suggestions, feel free to ping us on our Discord server or open a new issue in the `GitHub repository <https://github.com/fairmath/openfhe-rs/tree/master>`__.*

---

OpenFHE-rs is a Rust interface for the OpenFHE library, which is renowned for its comprehensive suite of Fully Homomorphic Encryption (FHE) schemes, all implemented in C++. By providing a Rust wrapper for OpenFHE, we aim to make these advanced FHE capabilities easily accessible to Rust developers.

Whether you're developing secure data processing applications or privacy-focused tools, OpenFHE-rs enables you to leverage the powerful encryption technologies of OpenFHE seamlessly within your Rust projects.

Installation
============

To use OpenFHE-rs, you'll need to install several dependencies and follow the installation steps for both the core OpenFHE library and the Rust crate.

Prerequisites
-------------

Ensure you have the following dependencies installed:

- `CMake >= 3.5.1`
- `Clang >= 12.0` or `GCC >= 11.4`
- `Rust >= 1.78`
- `Git`

Unix
~~~~

On Debian-based systems, you can install the necessary dependencies using:

.. code-block:: bash

    sudo apt install build-essential libssl-dev cmake clang git

Installation process
---------------------

Core OpenFHE library installation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To build and install the OpenFHE library, follow the steps below or refer to `OpenFHE's installation documentation <https://openfhe-development.readthedocs.io/en/latest/sphinx_rsts/intro/installation/installation.html>`__.

1. Clone the repository

.. code-block:: bash

    git clone https://github.com/openfheorg/openfhe-development.git
    cd openfhe-development

2. Configure CMake

.. code-block:: bash

    cmake -B ${OPENFHE_BUILD:-build} -DBUILD_SHARED=ON .

3. Build and install the C++ OpenFHE library

.. code-block:: bash

    make -C ${OPENFHE_BUILD:-build} -j$(nproc)
    make -C ${OPENFHE_BUILD:-build} install

4. Update the cache for the linker

.. code-block:: bash

    sudo ldconfig

Configuring your project to use the crate
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To use the OpenFHE crate in your Rust project, add it as a dependency from `crates.io <https://crates.io/crates/openfhe>`__:

.. code-block:: bash

    cargo add openfhe

You also need to add a small piece of code for the core dependencies' configuration in your `build.rs` file:

.. code-block:: rust

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

Template repository
~~~~~~~~~~~~~~~~~~~

Instead of doing it manually, you can start your project by forking our `template repository <https://github.com/fairmath/openfhe-rs-template/tree/main>`__.

Custom crate installation from the source
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can adjust the installation process by building the crate manually. In that case, you need to clone the Fair Math's `openfhe-rs <https://github.com/fairmath/openfhe-rs>`__ repo to your local machine and build it:

1. Clone the repository

.. code-block:: bash

    git clone https://github.com/fairmath/openfhe-rs.git
    cd openfhe-rs

2. Build the library

.. code-block:: bash

    cargo build

3. Run tests

.. code-block:: bash

    cargo test -- --test-threads=1

4. Run the examples

.. code-block:: bash

    cargo run --example function_evaluation
    cargo run --example polynomial_evaluation
    cargo run --example simple_integers
    cargo run --example simple_real_integers

Contributing
============

Contributions are always welcome! If you find bugs, have feature requests, or want to contribute code, please open an issue or pull request on the `GitHub repository <https://github.com/fairmath/openfhe-rs/tree/master>`__.

License
=======

`OpenFHE-rs` is licensed under the **BSD 2-Clause License**. See the `LICENSE <LICENSE>`__ file for more details.

