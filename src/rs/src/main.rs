use num_complex::Complex64;

#[derive(Debug)]
struct Qubit {
    C0: Complex64,
    C1: Complex64
}

fn validate_qubit(c0: Complex64, c1: Complex64) -> bool {
    if f64::round(c0.norm()*c0.norm() + c1.norm()*c1.norm()) as i32 == 1 {
        return true;
    } else {
        return false;
    }
}

fn new_qubit(c0: Complex64, c1: Complex64) -> Qubit {
    let mut qbit = Qubit{C0: c0, C1: c1};
    if !validate_qubit(c0, c1) {
        qbit.C0 = Complex64::new(0.0, 0.0);
        qbit.C1 = Complex64::new(0.0, 0.0);
    }
    return qbit;
}

fn main() {
    let c0 = Complex64::new(1.0, 0.0);
    let c1 = Complex64::new(0.0, 1.0);
    let mut q = Qubit{C0: c0, C1: c1};
    println!("First {:?}", q);
    q = new_qubit(c1, c0);
    println!("Second {:?}", q);
    let c2 = Complex64::new(0.0, 0.0);
    q = new_qubit(c0, c2);
    println!("Third {:?}", q);
    q = new_qubit(c2, c0);
    println!("Fourth {:?}", q);
}