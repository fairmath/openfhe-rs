# Homomorphic additions, multiplications, and rotations for vectors of integers via BFV
## Overview

This Rust example demonstrates basic homomorphic encryption operations such as addition, multiplication, and rotation on vectors of integers using the BFVrns3 scheme provided by the `openfhe` library. The example walks through the setup of cryptographic parameters, key generation, encryption of plaintext vectors, performing homomorphic operations, and decrypting the results.
The example for this code is located in [examples/simple_integers.rs](../../examples/simple_integers.rs).

## Code breakdown
### Importing libraries

We start by importing the necessary libraries and modules:

```rust
use openfhe::cxx::{CxxVector};
use openfhe::ffi as ffi;
```

### The code example

The `main` function contains the entire workflow for setting up the BFV scheme, performing encryption, executing homomorphic operations, and decrypting the results.

#### Generating Parameters

We define the cryptographic parameters for the BFV scheme, namely plaintext modulus and multiplicative depth.

```rust
let mut _cc_params_bfvrns = ffi::GenParamsBFVRNS();
_cc_params_bfvrns.pin_mut().SetPlaintextModulus(65537);
_cc_params_bfvrns.pin_mut().SetMultiplicativeDepth(2);
```

#### Creating Crypto Context

We create a crypto context based on the defined parameters and enable necessary features.

```rust
let _cc = ffi::GenCryptoContextByParamsBFVRNS(&_cc_params_bfvrns);
_cc.Enable(ffi::PKESchemeFeature::PKE);
_cc.Enable(ffi::PKESchemeFeature::KEYSWITCH);
_cc.Enable(ffi::PKESchemeFeature::LEVELEDSHE);
```

#### Key Generation

We generate the necessary keys for encryption, including evaluation keys for multiplication and rotation.

```rust
let _key_pair = _cc.KeyGen();
_cc.EvalMultKeyGen(&_key_pair.GetPrivateKey());

let mut _index_list = CxxVector::<i32>::new();
_index_list.pin_mut().push(1);
_index_list.pin_mut().push(2);
_index_list.pin_mut().push(-1);
_index_list.pin_mut().push(-2);
_cc.EvalRotateKeyGen(&_key_pair.GetPrivateKey(), &_index_list, &ffi::GenNullPublicKey());
```

#### Plaintext Vector Creation

```rust
let mut _vector_of_ints_1 = CxxVector::<i64>::new();
_vector_of_ints_1.pin_mut().push(1);
_vector_of_ints_1.pin_mut().push(2);
_vector_of_ints_1.pin_mut().push(3);
_vector_of_ints_1.pin_mut().push(4);
_vector_of_ints_1.pin_mut().push(5);
_vector_of_ints_1.pin_mut().push(6);
_vector_of_ints_1.pin_mut().push(7);
_vector_of_ints_1.pin_mut().push(8);
_vector_of_ints_1.pin_mut().push(9);
_vector_of_ints_1.pin_mut().push(10);
_vector_of_ints_1.pin_mut().push(11);
_vector_of_ints_1.pin_mut().push(12);
let _plain_text_1 = _cc.MakePackedPlaintext(&_vector_of_ints_1, 1, 0);
```

#### Encrypting Plaintext Vectors

We encrypt the plaintext vectors using the generated public key.

```rust
let _cipher_text_1 = _cc.EncryptByPublicKey(&_key_pair.GetPublicKey(), &_plain_text_1);
```

#### Performing Homomorphic Operations

We perform various homomorphic operations on the encrypted data, including addition, multiplication, and rotations.

```rust
let _cipher_text_add_1_2 = _cc.EvalAddByCiphertexts(&_cipher_text_1, &_cipher_text_2);
let _cipher_text_mult_result = _cc.EvalMultByCiphertexts(&_cipher_text_mul_1_2, &_cipher_text_3);
let _cipher_text_rot_1 = _cc.EvalRotate(&_cipher_text_1, 1);
```

#### Decrypting and Printing Results

Finally, we decrypt the results of the homomorphic computations and print them.

```rust
let mut _plain_text_add_result = ffi::GenNullPlainText();
_cc.DecryptByPrivateKeyAndCiphertext(&_key_pair.GetPrivateKey(), &_cipher_text_add_result, _plain_text_add_result.pin_mut());
println!("Plaintext #1: {}", _plain_text_1.GetString());
```

## Running the example

1. Ensure the `openfhe-rs` library is installed and properly configured, see the [Installation guide](../getting-started/installation.md)
2. Go to the `examples` directory and make sure that the needed example is there - `simple_integers.rs`.
3. Compile and run the Rust file:
    ```sh
    rustc simple_integers.rs -o simple_integers
    ./simple_integers
    ```

This should output the results of the homomorphic computations to the console.
