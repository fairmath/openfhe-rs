use openfhe::ffi;

fn main() {
    let _poly_null = ffi::DCRTPolyGenNullParams();
    let _poly_params = ffi::DCRTPolyGenParamsByOrderSizeBits(2 * 16, 4, 51);

    let trapdoor = ffi::DCRTPolyTrapdoorGen(&_poly_params, 3.19, 2, false);
    // let matrix_r = trapdoor.GetMatrixR();
    // let matrix_e = trapdoor.GetMatrixE();
}
