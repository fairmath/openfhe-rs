use openfhe::cxx::{CxxVector, SharedPtr};
use openfhe::ffi as ffi;

fn main()
{
    use std::time::Instant;
    println!("\n======EXAMPLE FOR EVALPOLY========\n");

    let mut _cc_params_ckksrns = ffi::GetParamsCKKSRNS();
    _cc_params_ckksrns.pin_mut().SetMultiplicativeDepth(6);
    _cc_params_ckksrns.pin_mut().SetScalingModSize(50);

    let mut _cc = ffi::GenCryptoContextByParamsCKKSRNS(&_cc_params_ckksrns);
    _cc.Enable(ffi::PKESchemeFeature::PKE);
    _cc.Enable(ffi::PKESchemeFeature::KEYSWITCH);
    _cc.Enable(ffi::PKESchemeFeature::LEVELEDSHE);
    _cc.Enable(ffi::PKESchemeFeature::ADVANCEDSHE);

    let mut _vals = CxxVector::<ffi::ComplexPair>::new();
    _vals.pin_mut().push(ffi::ComplexPair{re: 0.5, im: 0.0});
    _vals.pin_mut().push(ffi::ComplexPair{re: 0.7, im: 0.0});
    _vals.pin_mut().push(ffi::ComplexPair{re: 0.9, im: 0.0});
    _vals.pin_mut().push(ffi::ComplexPair{re: 0.95, im: 0.0});
    _vals.pin_mut().push(ffi::ComplexPair{re: 0.93, im: 0.0});
    let _input = ffi::GenVectorOfComplex(&_vals);
    let _encoded_length = _input.len();

    let mut _coefficients_1 = CxxVector::<f64>::new();
    _coefficients_1.pin_mut().push(0.15);
    _coefficients_1.pin_mut().push(0.75);
    _coefficients_1.pin_mut().push(0.0);
    _coefficients_1.pin_mut().push(1.25);
    _coefficients_1.pin_mut().push(0.0);
    _coefficients_1.pin_mut().push(0.0);
    _coefficients_1.pin_mut().push(1.0);
    _coefficients_1.pin_mut().push(0.0);
    _coefficients_1.pin_mut().push(1.0);
    _coefficients_1.pin_mut().push(2.0);
    _coefficients_1.pin_mut().push(0.0);
    _coefficients_1.pin_mut().push(1.0);
    _coefficients_1.pin_mut().push(0.0);
    _coefficients_1.pin_mut().push(0.0);
    _coefficients_1.pin_mut().push(0.0);
    _coefficients_1.pin_mut().push(0.0);
    _coefficients_1.pin_mut().push(1.0);

    let mut _coefficients_2 = CxxVector::<f64>::new();
    _coefficients_2.pin_mut().push(1.0);
    _coefficients_2.pin_mut().push(2.0);
    _coefficients_2.pin_mut().push(3.0);
    _coefficients_2.pin_mut().push(4.0);
    _coefficients_2.pin_mut().push(5.0);
    _coefficients_2.pin_mut().push(-1.0);
    _coefficients_2.pin_mut().push(-2.0);
    _coefficients_2.pin_mut().push(-3.0);
    _coefficients_2.pin_mut().push(-4.0);
    _coefficients_2.pin_mut().push(-5.0);
    _coefficients_2.pin_mut().push(0.1);
    _coefficients_2.pin_mut().push(0.2);
    _coefficients_2.pin_mut().push(0.3);
    _coefficients_2.pin_mut().push(0.4);
    _coefficients_2.pin_mut().push(0.5);
    _coefficients_2.pin_mut().push(-0.1);
    _coefficients_2.pin_mut().push(-0.2);
    _coefficients_2.pin_mut().push(-0.3);
    _coefficients_2.pin_mut().push(-0.4);
    _coefficients_2.pin_mut().push(-0.5);
    _coefficients_2.pin_mut().push(0.1);
    _coefficients_2.pin_mut().push(0.2);
    _coefficients_2.pin_mut().push(0.3);
    _coefficients_2.pin_mut().push(0.4);
    _coefficients_2.pin_mut().push(0.5);
    _coefficients_2.pin_mut().push(-0.1);
    _coefficients_2.pin_mut().push(-0.2);
    _coefficients_2.pin_mut().push(-0.3);
    _coefficients_2.pin_mut().push(-0.4);
    _coefficients_2.pin_mut().push(-0.5);

    let mut _plain_text_1 = _cc.MakeCKKSPackedPlaintextByVectorOfComplex(&_input, 1, 0, SharedPtr::<ffi::DCRTPolyParams>::null(), 0);
    let mut _key_pair = _cc.KeyGen();
    print!("Generating evaluation key for homomorphic multiplication...");
    _cc.EvalMultKeyGen(_key_pair.GetPrivateKey());
    println!("Completed.\n");
    let mut _cipher_text_1 = _cc.Encrypt(_key_pair.GetPublicKey(), &_plain_text_1);

    let mut _start = Instant::now();
    let mut _result = _cc.EvalPoly(&_cipher_text_1, &_coefficients_1);
    let _time_eval_poly_1 = _start.elapsed();

    _start = Instant::now();
    let mut _result_2 = _cc.EvalPoly(&_cipher_text_1, &_coefficients_2);
    let _time_eval_poly_2 = _start.elapsed();

    let mut _plain_text_dec = ffi::GenEmptyPlainText();
    _cc.Decrypt(_key_pair.GetPrivateKey(), &_result, _plain_text_dec.pin_mut());
    _plain_text_dec.SetLength(_encoded_length);
    let mut _plain_text_dec_2 = ffi::GenEmptyPlainText();
    _cc.Decrypt(_key_pair.GetPrivateKey(), &_result_2, _plain_text_dec_2.pin_mut());
    _plain_text_dec_2.SetLength(_encoded_length);

    println!("\n Original Plaintext #1:");
    println!("{}", _plain_text_1.GetString());
    println!("\n Result of evaluating a polynomial with coefficients [{} ]", _coefficients_1.iter().fold(String::new(), |acc, &arg| acc + " " + &arg.to_string()));
    println!("{}", _plain_text_dec.GetString());
    println!("\n Expected result: (0.70519107, 1.38285078, 3.97211180, 5.60215665, 4.86357575)");
    println!("\n Evaluation time: {:.0?}", _time_eval_poly_1);
    println!("\n Result of evaluating a polynomial with coefficients [{} ]", _coefficients_2.iter().fold(String::new(), |acc, &arg| acc + " " + &arg.to_string()));
    println!("{}\n", _plain_text_dec_2.GetString());
    println!(" Expected result: (3.4515092326, 5.3752765397, 4.8993108833, 3.2495023573, 4.0485229982)");
    print!("\n Evaluation time: {:.0?}\n", _time_eval_poly_2);
}
