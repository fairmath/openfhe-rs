use openfhe::cxx::{CxxVector};
use openfhe::ffi as ffi;

fn main()
{
    let mut _cc_params_bfvrns = ffi::GenParamsBFVRNS();
    _cc_params_bfvrns.pin_mut().SetPlaintextModulus(65537);
    _cc_params_bfvrns.pin_mut().SetMultiplicativeDepth(2);

    let _cc = ffi::DCRTPolyGenCryptoContextByParamsBFVRNS(&_cc_params_bfvrns);
    _cc.EnableByFeature(ffi::PKESchemeFeature::PKE);
    _cc.EnableByFeature(ffi::PKESchemeFeature::KEYSWITCH);
    _cc.EnableByFeature(ffi::PKESchemeFeature::LEVELEDSHE);

    let _key_pair = _cc.KeyGen();
    _cc.EvalMultKeyGen(&_key_pair.GetPrivateKey());

    let mut _index_list = CxxVector::<i32>::new();
    _index_list.pin_mut().push(1);
    _index_list.pin_mut().push(2);
    _index_list.pin_mut().push(-1);
    _index_list.pin_mut().push(-2);
    _cc.EvalRotateKeyGen(&_key_pair.GetPrivateKey(), &_index_list, &ffi::DCRTPolyGenNullPublicKey());

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

    let mut _vector_of_ints_2 = CxxVector::<i64>::new();
    _vector_of_ints_2.pin_mut().push(3);
    _vector_of_ints_2.pin_mut().push(2);
    _vector_of_ints_2.pin_mut().push(1);
    _vector_of_ints_2.pin_mut().push(4);
    _vector_of_ints_2.pin_mut().push(5);
    _vector_of_ints_2.pin_mut().push(6);
    _vector_of_ints_2.pin_mut().push(7);
    _vector_of_ints_2.pin_mut().push(8);
    _vector_of_ints_2.pin_mut().push(9);
    _vector_of_ints_2.pin_mut().push(10);
    _vector_of_ints_2.pin_mut().push(11);
    _vector_of_ints_2.pin_mut().push(12);
    let _plain_text_2 = _cc.MakePackedPlaintext(&_vector_of_ints_2, 1, 0);

    let mut _vector_of_ints_3 = CxxVector::<i64>::new();
    _vector_of_ints_3.pin_mut().push(1);
    _vector_of_ints_3.pin_mut().push(2);
    _vector_of_ints_3.pin_mut().push(5);
    _vector_of_ints_3.pin_mut().push(2);
    _vector_of_ints_3.pin_mut().push(5);
    _vector_of_ints_3.pin_mut().push(6);
    _vector_of_ints_3.pin_mut().push(7);
    _vector_of_ints_3.pin_mut().push(8);
    _vector_of_ints_3.pin_mut().push(9);
    _vector_of_ints_3.pin_mut().push(10);
    _vector_of_ints_3.pin_mut().push(11);
    _vector_of_ints_3.pin_mut().push(12);
    let _plain_text_3 = _cc.MakePackedPlaintext(&_vector_of_ints_3, 1, 0);

    let _cipher_text_1 = _cc.EncryptByPublicKey(&_key_pair.GetPublicKey(), &_plain_text_1);
    let _cipher_text_2 = _cc.EncryptByPublicKey(&_key_pair.GetPublicKey(), &_plain_text_2);
    let _cipher_text_3 = _cc.EncryptByPublicKey(&_key_pair.GetPublicKey(), &_plain_text_3);

    let _cipher_text_add_1_2 = _cc.EvalAddByCiphertexts(&_cipher_text_1, &_cipher_text_2);
    let _cipher_text_add_result = _cc.EvalAddByCiphertexts(&_cipher_text_add_1_2, &_cipher_text_3);

    let _cipher_text_mul_1_2 = _cc.EvalMultByCiphertexts(&_cipher_text_1, &_cipher_text_2);
    let _cipher_text_mult_result = _cc.EvalMultByCiphertexts(&_cipher_text_mul_1_2, &_cipher_text_3);

    let _cipher_text_rot_1 = _cc.EvalRotate(&_cipher_text_1, 1);
    let _cipher_text_rot_2 = _cc.EvalRotate(&_cipher_text_1, 2);
    let _cipher_text_rot_3 = _cc.EvalRotate(&_cipher_text_1, -1);
    let _cipher_text_rot_4 = _cc.EvalRotate(&_cipher_text_1, -2);

    let mut _plain_text_add_result = ffi::GenNullPlainText();
    _cc.DecryptByPrivateKeyAndCiphertext(&_key_pair.GetPrivateKey(), &_cipher_text_add_result, _plain_text_add_result.pin_mut());
    let mut _plain_text_mult_result = ffi::GenNullPlainText();
    _cc.DecryptByPrivateKeyAndCiphertext(&_key_pair.GetPrivateKey(), &_cipher_text_mult_result, _plain_text_mult_result.pin_mut());
    let mut _plain_text_rot_1 = ffi::GenNullPlainText();
    _cc.DecryptByPrivateKeyAndCiphertext(&_key_pair.GetPrivateKey(), &_cipher_text_rot_1, _plain_text_rot_1.pin_mut());
    let mut _plain_text_rot_2 = ffi::GenNullPlainText();
    _cc.DecryptByPrivateKeyAndCiphertext(&_key_pair.GetPrivateKey(), &_cipher_text_rot_2, _plain_text_rot_2.pin_mut());
    let mut _plain_text_rot_3 = ffi::GenNullPlainText();
    _cc.DecryptByPrivateKeyAndCiphertext(&_key_pair.GetPrivateKey(), &_cipher_text_rot_3, _plain_text_rot_3.pin_mut());
    let mut _plain_text_rot_4 = ffi::GenNullPlainText();
    _cc.DecryptByPrivateKeyAndCiphertext(&_key_pair.GetPrivateKey(), &_cipher_text_rot_4, _plain_text_rot_4.pin_mut());

    _plain_text_rot_1.SetLength(_vector_of_ints_1.len());
    _plain_text_rot_2.SetLength(_vector_of_ints_1.len());
    _plain_text_rot_3.SetLength(_vector_of_ints_1.len());
    _plain_text_rot_4.SetLength(_vector_of_ints_1.len());

    println!("Plaintext #1: {}", _plain_text_1.GetString());
    println!("Plaintext #2: {}", _plain_text_2.GetString());
    println!("Plaintext #3: {}", _plain_text_3.GetString());

    println!("\nResults of homomorphic computations");
    println!("#1 + #2 + #3: {}", _plain_text_add_result.GetString());
    println!("#1 * #2 * #3: {}", _plain_text_mult_result.GetString());
    println!("Left rotation of #1 by 1: {}", _plain_text_rot_1.GetString());
    println!("Left rotation of #1 by 2: {}", _plain_text_rot_2.GetString());
    println!("Right rotation of #1 by -1: {}", _plain_text_rot_3.GetString());
    println!("Right rotation of #1 by -2: {}", _plain_text_rot_4.GetString());
}
