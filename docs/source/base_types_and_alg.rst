Base types and algorithms
=========================

There are a couple of base types used around all the FHE-enabled applications. You can check this section or jump directly into our examples and figure out everything through experience.

Remember: if you have any questions not covered on this page - feel free to ping us on our `Discord server <https://discord.com/invite/NfhXwyr9M5>`_.

Cryptography schemes supported
-------------------------------

We currently support three so-called PKE schemes:

- CKKS
- BFV
- BGV

Many of our methods and algorithms contain the suffix referring to the scheme used. This section provides examples.

Params
------

The Params policy type stores flags and parameters for the FHE algorithms to use.

There are different ways to generate a Params type instance, but the main way is to create a mutable object by calling ``GenParams%scheme_name%`` and setting the options after that. For the CKKS scheme, it will be ``GenParamsCKKSRNS``.

CryptoContext
-------------

CryptoContext type, as its name stands, stores the metadata of your FHE context. You usually create its instance using one of the following functions:

- By generating the CryptoContext directly - ``ffi::DCRTPolyGenCryptoContextByParams%scheme_name%``
- By deserializing a CryptoContext generated somewhere else - ``ffi::DCRTPolyDeserializeCryptoContextFromFile``

