Homomorphic additions, multiplications, and rotations for vectors of real numbers via CKKS
===========================================================================================

Overview
--------

Homomorphic encryption allows computations on encrypted data without decrypting it. The CKKS (Cheon-Kim-Kim-Song) scheme supports approximate arithmetic operations on encrypted data, making it suitable for real number calculations.

The example walks through the setup of cryptographic parameters, key generation, encryption of plaintext vectors, performing homomorphic operations, and decrypting the results. The example for this code is located in :code:`examples/simple_real_numbers.rs <https://github.com/fairmath/openfhe-rs/blob/master/examples/simple_real_numbers.rs>`_.

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

The :code:`main` function contains the entire workflow for setting up the CKKS scheme, performing encryption, executing homomorphic operations, and decrypting the results.

.. code-block:: rust

    fn main()
    {
        // Define cryptographic parameters for CKKS
        let _mult_depth: u32 = 1;
        let _scale_mod_size: u32 = 50;
        let _batch_size: u32 = 8;

Generating Parameters
~~~~~~~~~~~~~~~~~~~~

We define the cryptographic parameters for the CKKS scheme, including multiplicative depth, scaling modulus size, and batch size.

.. code-block:: rust

    // Generate parameters for CKKS scheme
    let mut _cc_params_ckksrns = ffi::GenParamsCKKSRNS();
    _cc_params_ckksrns.pin_mut().SetMultiplicativeDepth(_mult_depth);
    _cc_params_ckksrns.pin_mut().SetScalingModSize(_scale_mod_size);
    _cc_params_ckksrns.pin_mut().SetBatchSize(_batch_size);

Creating Crypto Context
~~~~~~~~~~~~~~~~~~~~~~~

We create a crypto context based on the defined parameters and enable necessary features.

.. code-block:: rust

    // Create crypto context based on parameters
    let _cc = ffi::DCRTPolyGenCryptoContextByParamsCKKSRNS(&_cc_params_ckksrns);
    _cc.EnableByFeature(ffi::PKESchemeFeature::PKE);
    _cc.EnableByFeature(ffi::PKESchemeFeature::KEYSWITCH);
    _cc.EnableByFeature(ffi::PKESchemeFeature::LEVELEDSHE);

    // Outputing the ring dimension for clarity
    println!("CKKS scheme is using ring dimension {}\n", _cc.GetRingDimension());

Key Generation
~~~~~~~~~~~~~~

We generate the necessary keys for encryption, including evaluation keys for multiplication and rotation.

.. code-block:: rust

    // Key generation
    let _key_pair = _cc.KeyGen();
    _cc.EvalMultKeyGen(&_key_pair.GetPrivateKey());

    // Generate rotation keys
    let mut _index_list = CxxVector::<i32>::new();
    _index_list.pin_mut().push(1);
    _index_list.pin_mut().push(-2);
    _cc.EvalRotateKeyGen(&_key_pair.GetPrivateKey(), &_index_list, &ffi::DCRTPolyGenNullPublicKey());

Creating Input Vectors
~~~~~~~~~~~~~~~~~~~~~~

We create two input vectors for the demonstration.

.. code-block:: rust

    // Create input vectors
    let mut _x_1 = CxxVector::<f64>::new();
    _x_1.pin_mut().push(0.25);
    ...
    _x_1.pin_mut().push(5.0);

    let mut _x_2 = CxxVector::<f64>::new();
    _x_2.pin_mut().push(5.0);
    ...
    _x_2.pin_mut().push(0.25);

Creating Plaintext Objects
~~~~~~~~~~~~~~~~~~~~~~~~~~

We convert the input vectors into plaintext objects.

.. code-block:: rust

    // Create plaintext objects from vectors
    let _dcrt_poly_params = ffi::DCRTPolyGenNullParams();
    let _p_txt_1 = _cc.MakeCKKSPackedPlaintextByVectorOfDouble(&_x_1, 1, 0, &_dcrt_poly_params, 0);
    let _p_txt_2 = _cc.MakeCKKSPackedPlaintextByVectorOfDouble(&_x_2, 1, 0, &_dcrt_poly_params, 0);

    // Outputing the vectors for clarity
    println!("Input x1: {}", _p_txt_1.GetString());
    println!("Input x2: {}", _p_txt_2.GetString());

Encrypting Plaintext Vectors
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

We encrypt the plaintext vectors using the generated public key.

.. code-block:: rust

    // Encrypt plaintext vectors
    let _c1 = _cc.EncryptByPublicKey(&_key_pair.GetPublicKey(), &_p_txt_1);
    let _c2 = _cc.EncryptByPublicKey(&_key_pair.GetPublicKey(), &_p_txt_2);

Performing Homomorphic Operations
----------------------------------

We perform various homomorphic operations on the encrypted data, including addition, subtraction, multiplication by a constant, multiplication of ciphertexts, and rotations.

.. code-block:: rust

    // Perform homomorphic operations
    let _c_add = _cc.EvalAddByCiphertexts(&_c1, &_c2);
    let _c_sub = _cc.EvalSubByCiphertexts(&_c1, &_c2);
    let _c_scalar = _cc.EvalMultByCiphertextAndConst(&_c1, 4.0);
    let _c_mul = _cc.EvalMultByCiphertexts(&_c1, &_c2);
    let _c_rot_1 = _cc.EvalRotate(&_c1, 1);
    let _c_rot_2 = _cc.EvalRotate(&_c1, -2);

Decrypting and Printing Results
--------------------------------

Finally, we decrypt the results of the homomorphic computations and print them.

.. code-block:: rust

    // Prepare for decryption
    let mut _result = ffi::GenNullPlainText();
    println!("\nResults of homomorphic computations:");

    // Decrypt and print results
    _cc.DecryptByPrivateKeyAndCiphertext(&_key_pair.GetPrivateKey(), &_c1, _result.pin_mut());
    _result.SetLength(_batch_size.try_into().unwrap());
    println!("x1 = {}Estimated precision in bits: {}", _result.GetString(), _result.GetLogPrecision());

    _cc.DecryptByPrivateKeyAndCiphertext(&_key_pair.GetPrivateKey(), &_c_add, _result.pin_mut());
    _result.SetLength(_batch_size.try_into().unwrap());
    println!("x1 + x2 = {}Estimated precision in bits: {}",_result.GetString(), _result.GetLogPrecision());

    _cc.DecryptByPrivateKeyAndCiphertext(&_key_pair.GetPrivateKey(), &_c_sub, _result.pin_mut());
    _result.SetLength(_batch_size.try_into().unwrap());
    println!("x1 - x2 = {}", _result.GetString());

    _cc.DecryptByPrivateKeyAndCiphertext(&_key_pair.GetPrivateKey(), &_c_scalar, _result.pin_mut());
    _result.SetLength(_batch_size.try_into().unwrap());
    println!("4 * x1 = {}", _result.GetString());

    _cc.DecryptByPrivateKeyAndCiphertext(&_key_pair.GetPrivateKey(), &_c_mul, _result.pin_mut());
    _result.SetLength(_batch_size.try_into().unwrap());
    println!("x1 * x2 = {}", _result.GetString());

    _cc.DecryptByPrivateKeyAndCiphertext(&_key_pair.GetPrivateKey(), &_c_rot_1, _result.pin_mut());
    _result.SetLength(_batch_size.try_into().unwrap());
    println!("\nIn rotations, very small outputs (~10^-10 here) correspond to 0's:");
    println!("x1 rotate by 1 = {}", _result.GetString());

    _cc.DecryptByPrivateKeyAndCiphertext(&_key_pair.GetPrivateKey(), &_c_rot_2, _result.pin_mut());
    _result.SetLength(_batch_size.try_into().unwrap());
    println!("x1 rotate by -2 = {}", _result.GetString());

Running the example
~~~~~~~~~~~~~~~~~~~~

1. Ensure the `openfhe-rs` library is installed and properly configured, see the :doc:`intro` section.
2. Go to the `openfhe-rs` directory.
3. Compile and run the `simple_real_numbers.rs` example:

.. code-block:: sh

    cargo run --example simple_real_numbers

This should output the results of the homomorphic computations to the console.
