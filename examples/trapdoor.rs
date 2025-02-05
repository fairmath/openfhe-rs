use openfhe::ffi;

fn main() {
    let _poly_null = ffi::DCRTPolyGenNullParams();
    let _params = ffi::GenILDCRTParamsByOrderSizeBits(2 * 16, 4, 51);

    let trapdoor = ffi::DCRTPolyTrapdoorGen(&_params, 3.19, 2, false);
    let matrix_r = trapdoor.GetMatrixR();
}
