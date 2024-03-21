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
            let bfv_params = FFIParams::new1(FFISCHEME_BFVRNS_SCHEME);

            println!("bfv_params numofparties{}", bfv_params.GetThresholdNumOfParties())
        }
    }

    #[test]
    fn testCryptoContext() {
        unsafe {
            let mut ccontext = FFICryptoContextImpl::new();
            ccontext.SetKeyGenLevel(10);
            println!("crypto_context keygenlevel: {:?}", ccontext.GetKeyGenLevel());
            // println!("crypto_context ringdimension: {:?}", ccontext.GetRingDimension())
        }
    }

    #[test]
    fn testKeyPair() {
        unsafe {
            let mut key_pair = FFIKeyPair::new();
            println!("keypair is_good: {:?}", key_pair.is_good());
        }
    }
}