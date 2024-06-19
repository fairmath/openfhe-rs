Homomorphic additions, multiplications, and rotations for vectors of integers via BFV
=======================================================================================

Overview
--------

This Rust example demonstrates basic homomorphic encryption operations such as addition, multiplication, and rotation on vectors of integers using the BFVrns3 scheme provided by the `openfhe` library. The example walks through the setup of cryptographic parameters, key generation, encryption of plaintext vectors, performing homomorphic operations, and decrypting the results. The example for this code is located in :code:`examples/simple_integers.rs <https://github.com/fairmath/openfhe-rs/blob/master/examples/simple_integers.rs>`_.

Code breakdown
--------------

Importing libraries
~~~~~~~~~~~~~~~~~~

We start by importing the necessary libraries and modules:

.. code-block:: rust

    use openfhe::cxx::{CxxVector};
    use openfhe::ffi as ffi;

The code example
~~~~~~~~~~~~~~~~

The `main` function contains the entire workflow for setting up the BFV scheme, performing encryption, executing homomorphic operations, and decrypting the results.

Generating Parameters
~~~~~~~~~~~~~~~~~~~~

We define the cryptographic parameters for the BFV scheme, namely plaintext modulus and multiplicative depth.

.. code-block:: rust

    let mut _cc_params_bfvrns = ffi::GenParamsBFVRNS();
    _cc_params_bfvrns.pin_mut().SetPlaintextModulus(65537);
    _cc_params_bfvrns.pin_mut().SetMultiplicativeDepth(2);

Creating Crypto Context
~~~~~~~~~~~~~~~~~~~~~~~

We create a crypto context based on the defined parameters and enable necessary features.

.. code-block:: rust

    let _cc = ffi::DCRTPolyGenCryptoContextByParamsBFVRNS(&_cc_params_bfvrns);
    _cc.EnableByFeature(ffi::PKESchemeFeature::PKE);
    _cc.EnableByFeature(ffi::PKESchemeFeature::KEYSWITCH);
    _cc.EnableByFeature(ffi::PKESchemeFeature::LEVELEDSHE);

Key Generation
~~~~~~~~~~~~~~

We generate the necessary keys for encryption, including evaluation keys for multiplication and rotation.

.. code-block:: rust

    let _key_pair = _cc.KeyGen();
    _cc.EvalMultKeyGen(&_key_pair.GetPrivateKey());

    let mut _index_list = CxxVector::<i32>::new();
    _index_list.pin_mut().push(1);
    _index_list.pin_mut().push(2);
    _index_list.pin_mut().push(-1);
    _index_list.pin_mut().push(-2);
    _cc.EvalRotateKeyGen(&_key_pair.GetPrivateKey(), &_index_list, &ffi::DCRTPolyGenNullPublicKey());

Plaintext Vector Creation
~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: rust

    let mut _vector_of_ints_1 = CxxVector::<i64>::new();
    _vector_of_ints_1.pin_mut().push(1);
    _vector_of_ints_1.pin_mut().push(2);
    ...
    let _plain_text_1 = _cc.MakePackedPlaintext(&_vector_of_ints_1, 1, 0);

Encrypting Plaintext Vectors
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

We encrypt the plaintext vectors using the generated public key.

.. code-block:: rust

    let _cipher_text_1 = _cc.EncryptByPublicKey(&_key_pair.GetPublicKey(), &_plain_text_1);

Performing Homomorphic Operations
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

We perform various homomorphic operations on the encrypted data, including addition, multiplication, and rotations.

.. code-block:: rust

    let _cipher_text_add_1_2 = _cc.EvalAddByCiphertexts(&_cipher_text_1, &_cipher_text_2);
    let _cipher_text_mult_result = _cc.EvalMultByCiphertexts(&_cipher_text_mul_1_2, &_cipher_text_3);
    let _cipher_text_rot_1 = _cc.EvalRotate(&_cipher_text_1, 1);

Decrypting and Printing Results
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Finally, we decrypt the results of the homomorphic computations and print them.

.. code-block:: rust

    let mut _plain_text_add_result = ffi::GenNullPlainText();
    _cc.DecryptByPrivateKeyAndCiphertext(&_key_pair.GetPrivateKey(), &_cipher_text_add_result, _plain_text_add_result.pin_mut());
    println!("Plaintext #1: {}", _plain_text_1.GetString());

Running the example
~~~~~~~~~~~~~~~~~~~~

1. Ensure the `openfhe-rs` library is installed and properly configured, see the :doc:`intro` section.
2. Go to the `openfhe-rs` directory.
3. Compile and run the `simple_integers.rs` example:

.. code-block:: sh

    cargo run --example simple_integers

This should output the results of the homomorphic computations to the console.
