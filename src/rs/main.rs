use num_complex::Complex64;
use std::error::Error;
// TODO: rewrite without error handling to just get a working build
#[derive(Debug)]
enum QubitError {
    InvalidQubit,
}

impl std::fmt::Display for QubitError {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f, "Invalid complex number parameters to create Qubit")
    }
}

impl Error for QubitError {}

#[derive(Debug)]
struct Qubit {
    C0: Complex64,
    C1: Complex64
}

fn validateQubit(c0: Complex64, c1: Complex64) -> bool {
    if f64::round(f64::abs(c0)*f64::abs(c0) + f64::abs(c1)*f64::abs(c1)) as i32 == 1 {
        return true;
    } else {
        return false;
    }
}

fn newQubit(c0: Complex64, c1: Complex64) -> Result<Qubit, QubitError> {
    if !validateQubit(c0, c1) {
        return Err(QubitError::InvalidQubit);
    }
    let qbit = Qubit{C0: c0, C1: c1};
    Ok(qbit)
}

fn main() {
    let c0 = Complex64::new(1.0, 0.0);
    let c1 = Complex64::new(0.0, 1.0);
    match newQubit(c0, c1) {
        Ok(qbit) => println!("Qubit created: {:?}", qbit),
        Err(err) => println!("Error: {}", err),
    }
}