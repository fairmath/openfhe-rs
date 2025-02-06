use openfhe::ffi;

fn main() {
    let _params = ffi::GenILDCRTParamsByOrderSizeBits(2 * 16, 8, 51);
    let trapdoor = ffi::DCRTPolyTrapdoorGen(&_params, 3.19, 2, false);
    let matrix_r = trapdoor.GetMatrixR();
    let matrix_e = trapdoor.GetMatrixE();
    println!("matrix_r: {}", matrix_r.GetRows());
    println!("matrix_e: {}", matrix_e.GetRows());
    println!("matrix_r: {}", matrix_r.GetCols());
    println!("matrix_e: {}", matrix_e.GetCols());
}
