use std::env;
use std::path::PathBuf;

fn main() {
    println!("cargo:rustc-link-search=cpp/build/src/");
    
    println!("cargo:rustc-link-lib=fhecomponents");

    let bindings = bindgen::Builder::default()
        .header("cpp/include/bindings.hpp")
        .parse_callbacks(Box::new(bindgen::CargoCallbacks))
        .generate()
        .expect("Unable to generate bindings");
    println!("cargo:rerun-if-changed=cpp/include/bindings.hpp");
    // Write the bindings to the $OUT_DIR/bindings.rs file.
    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");
}
