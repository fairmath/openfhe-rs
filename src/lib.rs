#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn testCryptoContextBFVRNSCCParams() {
        unsafe {
            let ccparams = FFIParams::new1(FFISCHEME_CKKSRNS_SCHEME);

            let mut ccontext = GenCryptoContext(ccparams);

            ccontext.Enable(FFIPKESchemeFeature_PKE);
            ccontext.Enable(FFIPKESchemeFeature_KEYSWITCH);
            ccontext.Enable(FFIPKESchemeFeature_LEVELEDSHE);

            let key_pair = ccontext.KeyGen();

            println!("keypair is_allocated: {:?}", key_pair.is_allocated());
             
            ccontext.EvalMultKeyGen(key_pair.GetPrivateKey());
        }
    }

    #[test]
    fn testKeyPair() {
        unsafe {
            let key_pair = FFIKeyPair::new();
            println!("keypair is_allocated: {:?}", key_pair.is_allocated());
        }
    }
}