#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

#[cfg(test)]
mod tests {
    use super::*;
    use std::mem;

    #[test]
    fn testCryptoContextBFVRNSCCParams() {
        unsafe {
            let ccparams = CryptoContextBFVRNSCCParams::new();
            
            let ccparams_plaintext_modulus = ccparams.GetPlaintextModulus();

            println!("ccparams_plaintext_modulus: {}", ccparams_plaintext_modulus);

            let ccparams_scheme = ccparams.GetScheme();

            println!("ccparams_scheme: {}", ccparams_scheme);
        }
    }
}