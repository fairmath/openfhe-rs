use openfhe::cxx::{CxxVector};
use openfhe::ffi as ffi;

fn main()
{
    let _mult_depth: u32 = 1;
    let _scale_mod_size: u32 = 50;
    let _batch_size: u32 = 8;

    let mut _cc_params_ckksrns = ffi::GenParamsCKKSRNS();
    _cc_params_ckksrns.pin_mut().SetMultiplicativeDepth(_mult_depth);
    _cc_params_ckksrns.pin_mut().SetScalingModSize(_scale_mod_size);
    _cc_params_ckksrns.pin_mut().SetBatchSize(_batch_size);

    let _cc = ffi::GenCryptoContextByParamsCKKSRNS(&_cc_params_ckksrns);
    _cc.Enable(ffi::PKESchemeFeature::PKE);
    _cc.Enable(ffi::PKESchemeFeature::KEYSWITCH);
    _cc.Enable(ffi::PKESchemeFeature::LEVELEDSHE);

    println!("CKKS scheme is using ring dimension {}\n", _cc.GetRingDimension());

    let _key_pair = _cc.KeyGen();
    _cc.EvalMultKeyGen(&_key_pair.GetPrivateKey());
    let mut _index_list = CxxVector::<i32>::new();
    _index_list.pin_mut().push(1);
    _index_list.pin_mut().push(-2);
    _cc.EvalRotateKeyGen(&_key_pair.GetPrivateKey(), &_index_list, &ffi::GenNullPublicKey());

    let mut _x_1 = CxxVector::<f64>::new();
    _x_1.pin_mut().push(0.25);
    _x_1.pin_mut().push(0.5);
    _x_1.pin_mut().push(0.75);
    _x_1.pin_mut().push(1.0);
    _x_1.pin_mut().push(2.0);
    _x_1.pin_mut().push(3.0);
    _x_1.pin_mut().push(4.0);
    _x_1.pin_mut().push(5.0);

    let mut _x_2 = CxxVector::<f64>::new();
    _x_2.pin_mut().push(5.0);
    _x_2.pin_mut().push(4.0);
    _x_2.pin_mut().push(3.0);
    _x_2.pin_mut().push(2.0);
    _x_2.pin_mut().push(1.0);
    _x_2.pin_mut().push(0.75);
    _x_2.pin_mut().push(0.5);
    _x_2.pin_mut().push(0.25);

    let _dcrt_poly_params = ffi::GenNullDCRTPolyParams();
    let _p_txt_1 = _cc.MakeCKKSPackedPlaintext(&_x_1, 1, 0, &_dcrt_poly_params, 0);
    let _p_txt_2 = _cc.MakeCKKSPackedPlaintext(&_x_2, 1, 0, &_dcrt_poly_params, 0);

    println!("Input x1: {}", _p_txt_1.GetString());
    println!("Input x2: {}", _p_txt_2.GetString());

    let _c1 = _cc.EncryptByPublicKey(&_key_pair.GetPublicKey(), &_p_txt_1);
    let _c2 = _cc.EncryptByPublicKey(&_key_pair.GetPublicKey(), &_p_txt_2);

    let _c_add = _cc.EvalAddByCiphertexts(&_c1, &_c2);
    let _c_sub = _cc.EvalSubByCiphertexts(&_c1, &_c2);
    let _c_scalar = _cc.EvalMultByCiphertextAndConst(&_c1, 4.0);
    let _c_mul = _cc.EvalMultByCiphertexts(&_c1, &_c2);
    let _c_rot_1 = _cc.EvalRotate(&_c1, 1);
    let _c_rot_2 = _cc.EvalRotate(&_c1, -2);

    let mut _result = ffi::GenNullPlainText();
    println!("\nResults of homomorphic computations:");

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
}
