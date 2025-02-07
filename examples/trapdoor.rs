use openfhe::ffi;

fn main() {
    // Parameters based on https://github.com/openfheorg/openfhe-development/blob/7b8346f4eac27121543e36c17237b919e03ec058/src/core/unittest/UnitTestTrapdoor.cpp#L314
    let n = 16;
    let size = 4;
    let k_res = 51;

    let params = ffi::GenILDCRTParamsByOrderSizeBits(2 * n, size, k_res);

    let u = ffi::DCRTPolyGenFromDug(&params);
}
