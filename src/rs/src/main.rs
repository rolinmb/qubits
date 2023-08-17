use num_complex::Complex64;

#[derive(Debug)]
struct Qubit {
    c0: Complex64,
    c1: Complex64
}

fn validate_qubit(cmp0: Complex64, cmp1: Complex64) -> bool {
    if f64::round(cmp0.norm()*cmp0.norm() + cmp1.norm()*cmp1.norm()) as i32 == 1 {
        return true;
    } else {
        return false;
    }
}

fn singleton_qubit(cmp0: Complex64, cmp1: Complex64) -> Qubit {
    let mut qbit = Qubit{c0: cmp0, c1: cmp1};
    if !validate_qubit(cmp0, cmp1) {
        qbit.c0 = Complex64::new(0.0, 0.0);
        qbit.c1 = Complex64::new(0.0, 0.0);
    }
    return qbit;
}

#[derive(Debug)]
struct QuantumRegister {
    qubits: Vec<Qubit>
}

fn validate_register(qbits: &Vec<Qubit>) -> bool {
    let mut sum = 0.0;
    for q in qbits {
        sum += q.c0.norm()*q.c0.norm() + q.c1.norm()*q.c1.norm();
    }
    (f64::round(sum)) as i32 == 1
}

fn new_qregister(qbits: Vec<Qubit>) -> QuantumRegister {
    if validate_register(&qbits) {
        return QuantumRegister{qubits: qbits};
    } else {
        return QuantumRegister{qubits: Vec::new()};
    }
}

fn main() {
    let cmp0 = Complex64::new(1.0, 0.0);
    let cmp1 = Complex64::new(0.0, 1.0);
    let mut q0 = Qubit{c0: cmp0, c1: cmp1};
    println!("First {:?}", q0);
    q0 = singleton_qubit(cmp1, cmp0);
    println!("Second {:?}", q0);
    let cmp2 = Complex64::new(0.0, 0.0);
    q0 = singleton_qubit(cmp0, cmp2);
    println!("Third {:?}", q0);
    q0 = singleton_qubit(cmp2, cmp0);
    println!("Fourth {:?}", q0);
    let cmp3 = Complex64::new(0.5, 0.0);
    let cmp4 = Complex64::new(0.0, -0.5);
    let qbits: Vec<Qubit> = vec![
        Qubit {c0: cmp3, c1: cmp4},
        Qubit {c0: cmp4, c1: cmp3}
    ];
    let qr = new_qregister(qbits);
    println!("{:?}", qr)
}