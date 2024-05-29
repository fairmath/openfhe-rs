#![allow(non_snake_case)]
use openfhe::cxx::{CxxVector, SharedPtr};
use openfhe::ffi as ffi;

// In this example, we evaluate the logistic function 1 / (1 + exp(-x)) on an input of doubles

fn EvalLogisticExample()
{
    println!("--------------------------------- EVAL LOGISTIC FUNCTION ---------------------------------");
    let mut _cc_params_ckksrns = ffi::GetParamsCKKSRNS();

    // We set a smaller ring dimension to improve performance for this example.
    // In production environments, the security level should be set to
    // HEStd_128_classic, HEStd_192_classic, or HEStd_256_classic for 128-bit, 192-bit,
    // or 256-bit security, respectively.
    _cc_params_ckksrns.pin_mut().SetSecurityLevel(ffi::SecurityLevel::HEStd_NotSet);
    _cc_params_ckksrns.pin_mut().SetRingDim(1 << 10);
    // #if NATIVEINT == 128
    // let _scaling_mod_size: u32 = 78;
    // let _first_mod_size: u32 = 89;
    let _scaling_mod_size: u32 = 50;
    let _first_mod_size: u32 = 60;
    _cc_params_ckksrns.pin_mut().SetScalingModSize(_scaling_mod_size);
    _cc_params_ckksrns.pin_mut().SetFirstModSize(_first_mod_size);
    
    // Choosing a higher degree yields better precision, but a longer runtime.
    let _poly_degree: u32 = 16;

    // The multiplicative depth depends on the polynomial degree.
    // See the [FUNCTION_EVALUATION.md](../../gitbook-docs/examples/function_evaluation.rs) file
    // for a table mapping polynomial degrees to multiplicative depths.
    let _mult_depth: u32 = 6;    
    _cc_params_ckksrns.pin_mut().SetMultiplicativeDepth(_mult_depth);

    let _cc = ffi::GenCryptoContextByParamsCKKSRNS(&_cc_params_ckksrns);
    _cc.Enable(ffi::PKESchemeFeature::PKE);
    _cc.Enable(ffi::PKESchemeFeature::KEYSWITCH);
    _cc.Enable(ffi::PKESchemeFeature::LEVELEDSHE);

    // We need to enable Advanced SHE to use the Chebyshev approximation.
    _cc.Enable(ffi::PKESchemeFeature::ADVANCEDSHE);

    // We need to generate mult keys to run Chebyshev approximations.
    let _key_pair = _cc.KeyGen();
    _cc.EvalMultKeyGen(_key_pair.GetPrivateKey());

    let mut _input = CxxVector::<ffi::ComplexPair>::new();
    _input.pin_mut().push(ffi::ComplexPair{re: -4.0, im: 0.0});
    _input.pin_mut().push(ffi::ComplexPair{re: -3.0, im: 0.0});
    _input.pin_mut().push(ffi::ComplexPair{re: -2.0, im: 0.0});
    _input.pin_mut().push(ffi::ComplexPair{re: -1.0, im: 0.0});
    _input.pin_mut().push(ffi::ComplexPair{re: 0.0, im: 0.0});
    _input.pin_mut().push(ffi::ComplexPair{re: 1.0, im: 0.0});
    _input.pin_mut().push(ffi::ComplexPair{re: 2.0, im: 0.0});
    _input.pin_mut().push(ffi::ComplexPair{re: 3.0, im: 0.0});
    _input.pin_mut().push(ffi::ComplexPair{re: 4.0, im: 0.0});
    let _encoded_length: usize = _input.len();
    let _plain_text = _cc.MakeCKKSPackedPlaintextByVectorOfComplex(&_input, 1, 0, SharedPtr::<ffi::DCRTPolyParams>::null(), 0);
    let _cipher_text = _cc.EncryptByPublicKey(_key_pair.GetPublicKey(), &_plain_text);
    let _lower_bound: f64 = -5.0;
    let _upper_bound: f64 = 5.0;
    let _result = _cc.EvalLogistic(&_cipher_text, _lower_bound, _upper_bound, _poly_degree);

    let mut _plain_text_dec = ffi::GenEmptyPlainText();
    _cc.DecryptByPrivateKeyAndCiphertext(_key_pair.GetPrivateKey(), &_result, _plain_text_dec.pin_mut());
    _plain_text_dec.SetLength(_encoded_length);

    let mut _expected_output = CxxVector::<ffi::ComplexPair>::new();
    _expected_output.pin_mut().push(ffi::ComplexPair{re: 0.0179885, im: 0.0});
    _expected_output.pin_mut().push(ffi::ComplexPair{re: 0.0474289, im: 0.0});
    _expected_output.pin_mut().push(ffi::ComplexPair{re: 0.119205, im: 0.0});
    _expected_output.pin_mut().push(ffi::ComplexPair{re: 0.268936, im: 0.0});
    _expected_output.pin_mut().push(ffi::ComplexPair{re: 0.5, im: 0.0});
    _expected_output.pin_mut().push(ffi::ComplexPair{re: 0.731064, im: 0.0});
    _expected_output.pin_mut().push(ffi::ComplexPair{re: 0.880795, im: 0.0});
    _expected_output.pin_mut().push(ffi::ComplexPair{re: 0.952571, im: 0.0});
    _expected_output.pin_mut().push(ffi::ComplexPair{re: 0.982011, im: 0.0});
    println!("Expected output\n\t[{} ]", _expected_output.iter().fold(String::new(), |acc, arg| acc + " " + "(" + &arg.re.to_string() + "," + &arg.im.to_string() + ")"));

    let _final_result = _plain_text_dec.GetCopyOfCKKSPackedValue();
    println!("Actual output\n\t[{} ]", _final_result.iter().fold(String::new(), |acc, arg| acc + " " + "(" + &arg.re.to_string() + "," + &arg.im.to_string() + ")"));
}

fn GetSqrt(x: f64, ret: &mut f64)
{
    *ret = x.sqrt();
}

fn EvalFunctionExample()
{
    println!("--------------------------------- EVAL SQUARE ROOT FUNCTION ---------------------------------");
    let mut _cc_params_ckksrns = ffi::GetParamsCKKSRNS();

    // We set a smaller ring dimension to improve performance for this example.
    // In production environments, the security level should be set to
    // HEStd_128_classic, HEStd_192_classic, or HEStd_256_classic for 128-bit, 192-bit,
    // or 256-bit security, respectively.
    _cc_params_ckksrns.pin_mut().SetSecurityLevel(ffi::SecurityLevel::HEStd_NotSet);
    _cc_params_ckksrns.pin_mut().SetRingDim(1 << 10);
    // #if NATIVEINT == 128
    // let _scaling_mod_size: u32 = 78;
    // let _first_mod_size: u32 = 89;
    let _scaling_mod_size: u32 = 50;
    let _first_mod_size: u32 = 60;
    _cc_params_ckksrns.pin_mut().SetScalingModSize(_scaling_mod_size);
    _cc_params_ckksrns.pin_mut().SetFirstModSize(_first_mod_size);

    // Choosing a higher degree yields better precision, but a longer runtime.
    let _poly_degree: u32 = 50;

    // The multiplicative depth depends on the polynomial degree.
    // See the [FUNCTION_EVALUATION.md](../../gitbook-docs/examples/function_evaluation.rs) file
    // for a table mapping polynomial degrees to multiplicative depths.
    let _mult_depth: u32 = 7;
    _cc_params_ckksrns.pin_mut().SetMultiplicativeDepth(_mult_depth);

    let _cc = ffi::GenCryptoContextByParamsCKKSRNS(&_cc_params_ckksrns);
    _cc.Enable(ffi::PKESchemeFeature::PKE);
    _cc.Enable(ffi::PKESchemeFeature::KEYSWITCH);
    _cc.Enable(ffi::PKESchemeFeature::LEVELEDSHE);

    // We need to enable Advanced SHE to use the Chebyshev approximation.
    _cc.Enable(ffi::PKESchemeFeature::ADVANCEDSHE);

    // We need to generate mult keys to run Chebyshev approximations.
    let _key_pair = _cc.KeyGen();
    _cc.EvalMultKeyGen(_key_pair.GetPrivateKey());
    
    let mut _input = CxxVector::<ffi::ComplexPair>::new();
    _input.pin_mut().push(ffi::ComplexPair{re: 1.0, im: 0.0});
    _input.pin_mut().push(ffi::ComplexPair{re: 2.0, im: 0.0});
    _input.pin_mut().push(ffi::ComplexPair{re: 3.0, im: 0.0});
    _input.pin_mut().push(ffi::ComplexPair{re: 4.0, im: 0.0});
    _input.pin_mut().push(ffi::ComplexPair{re: 5.0, im: 0.0});
    _input.pin_mut().push(ffi::ComplexPair{re: 6.0, im: 0.0});
    _input.pin_mut().push(ffi::ComplexPair{re: 7.0, im: 0.0});
    _input.pin_mut().push(ffi::ComplexPair{re: 8.0, im: 0.0});
    _input.pin_mut().push(ffi::ComplexPair{re: 9.0, im: 0.0});

    let _encoded_length: usize = _input.len();
    let _plain_text = _cc.MakeCKKSPackedPlaintextByVectorOfComplex(&_input, 1, 0, SharedPtr::<ffi::DCRTPolyParams>::null(), 0);
    let _cipher_text = _cc.EncryptByPublicKey(_key_pair.GetPublicKey(), &_plain_text);
    let _lower_bound: f64 = 0.0;
    let _upper_bound: f64 = 10.0;
    let _result = _cc.EvalChebyshevFunction(GetSqrt, &_cipher_text, _lower_bound, _upper_bound, _poly_degree);

    let mut _plain_text_dec = ffi::GenEmptyPlainText();
    _cc.DecryptByPrivateKeyAndCiphertext(_key_pair.GetPrivateKey(), &_result, _plain_text_dec.pin_mut());
    _plain_text_dec.SetLength(_encoded_length);

    let mut _expected_output = CxxVector::<ffi::ComplexPair>::new();
    _expected_output.pin_mut().push(ffi::ComplexPair{re: 1.0, im: 0.0});
    _expected_output.pin_mut().push(ffi::ComplexPair{re: 1.414213, im: 0.0});
    _expected_output.pin_mut().push(ffi::ComplexPair{re: 1.732050, im: 0.0});
    _expected_output.pin_mut().push(ffi::ComplexPair{re: 2.0, im: 0.0});
    _expected_output.pin_mut().push(ffi::ComplexPair{re: 2.236067, im: 0.0});
    _expected_output.pin_mut().push(ffi::ComplexPair{re: 2.449489, im: 0.0});
    _expected_output.pin_mut().push(ffi::ComplexPair{re: 2.645751, im: 0.0});
    _expected_output.pin_mut().push(ffi::ComplexPair{re: 2.828427, im: 0.0});
    _expected_output.pin_mut().push(ffi::ComplexPair{re: 3.0, im: 0.0});
    println!("Expected output\n\t[{} ]", _expected_output.iter().fold(String::new(), |acc, arg| acc + " " + "(" + &arg.re.to_string() + "," + &arg.im.to_string() + ")"));

    let _final_result = _plain_text_dec.GetCopyOfCKKSPackedValue();
    println!("Actual output\n\t[{} ]", _final_result.iter().fold(String::new(), |acc, arg| acc + " " + "(" + &arg.re.to_string() + "," + &arg.im.to_string() + ")"));
}

fn main()
{
    EvalLogisticExample();
    EvalFunctionExample();
}