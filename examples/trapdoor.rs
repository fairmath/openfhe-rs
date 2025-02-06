use openfhe::ffi;

fn main() {
    let _params = ffi::GenILDCRTParamsByOrderSizeBits(2 * 16, 4, 51);
    let trapdoor = ffi::DCRTPolyTrapdoorGen(&_params, 4.57825, 8, false);
    let trapdoor_pair = trapdoor.GetTrapdoorPair();
    let uniform_matrix = trapdoor.GetUniformMatrix();
    let matrix_r = trapdoor_pair.GetMatrixR();
    let matrix_e = trapdoor_pair.GetMatrixE();
    println!(
        "uniform_matrix dimenstions: {}x{}",
        uniform_matrix.GetRows(),
        uniform_matrix.GetCols()
    );
    println!(
        "matrix_r dimenstions: {}x{}",
        matrix_r.GetRows(),
        matrix_r.GetCols()
    );
    println!(
        "matrix_e dimenstions: {}x{}",
        matrix_e.GetRows(),
        matrix_e.GetCols()
    );

    let dug = ffi::GenNullDiscreteUniformGenerator();
}
