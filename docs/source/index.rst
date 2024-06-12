Welcome to OpenFHE Rust wrapper's documentation!
===================================

OpenFHE
--------

Fully Homomorphic Encryption (FHE) is a powerful cryptographic primitive that enables performing computations over encrypted data without having access to the secret key.
OpenFHE is an open-source FHE library that includes efficient implementations of all common FHE schemes:
  - Brakerski/Fan-Vercauteren (BFV) scheme for integer arithmetic
  - Brakerski-Gentry-Vaikuntanathan (BGV) scheme for integer arithmetic
  - Cheon-Kim-Kim-Song (CKKS) scheme for real-number arithmetic (includes approximate bootstrapping)
  - Ducas-Micciancio (DM/FHEW) and Chillotti-Gama-Georgieva-Izabachene (CGGI/TFHE), and Lee-Micciancio-Kim-Choi-Deryabin-Eom-Yoo (LMKCDEY) schemes for evaluating Boolean circuits and arbitrary functions over larger plaintext spaces using lookup tables

About OpenFHE-rs
================

OpenFHE-rs is a joint project by `Fair Math <https://fairmath.xyz/>`_ & `OpenFHE <https://www.openfhe.org/>`_

.. image:: https://img.shields.io/discord/1163764915803279360?logo=discord&label=Fair%20Math
   :target: https://discord.com/invite/NfhXwyr9M5

.. image:: https://img.shields.io/twitter/follow/FairMath
   :target: https://twitter.com/FairMath

.. note::

   🔔 Keep in mind that the library is WIP and may contain some unpolished interfaces. If you encounter any issues or have any suggestions, feel free to ping us on our Discord server or open a new issue in the `GitHub repository <https://github.com/fairmath/openfhe-rs/tree/master>`_.

OpenFHE-rs is a Rust interface for the OpenFHE library, which is renowned for its comprehensive suite of Fully Homomorphic Encryption (FHE) schemes, all implemented in C++. By providing a Rust wrapper for OpenFHE, we aim to make these advanced FHE capabilities easily accessible to Rust developers.

Whether you're developing secure data processing applications or privacy-focused tools, OpenFHE-rs enables you to leverage the powerful encryption technologies of OpenFHE seamlessly within your Rust projects.

Check out the :doc:`intro` section for quick start information, including installation instructions.

Contents
--------

.. toctree::

   intro
   limitations
   base_types_and_alg
   simple_integers
   simple_real_numbers
