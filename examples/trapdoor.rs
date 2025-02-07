use openfhe::ffi;

fn main() {
    // Parameters based on https://github.com/openfheorg/openfhe-development/blob/7b8346f4eac27121543e36c17237b919e03ec058/src/core/unittest/UnitTestTrapdoor.cpp#L314
    let n: u32 = 16;
    let size: u32 = 4;
    let k_res: u32 = 51;
    let base: i64 = 8;

    let params = ffi::GenILDCRTParamsByOrderSizeBits(2 * n, size, k_res);

    let u = ffi::DCRTPolyGenFromDug(&params);

    let trapdoor = ffi::DCRTPolyTrapdoorGen(&params, base, false);

    let k = 68; // to calculate

    ffi::DCRTPolyGaussSamp(n.try_into().unwrap(), k, base);
}
