use openfhe::ffi;

fn main() {
    let _poly_null = ffi::DCRTPolyGenNullParams();
    let _poly_params = ffi::DCRTPolyGenParamsByOrderSizeBits(2 * 16, 4, 51);
}
