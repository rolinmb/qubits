use num_complex::Complex64;
use std::thread;
use std::time::{Duration, SystemTime, UNIX_EPOCH};
use rand::{Rng, SeedableRng};

fn get_random_float() -> f64 {
    let nanoseconds = Duration::new(0, 1);
    thread::sleep(nanoseconds);
    let current_time = SystemTime::now().duration_since(UNIX_EPOCH).expect("Time went backwards").as_nanos();
    let seed = current_time as u64;
    let mut rng = rand::rngs::StdRng::seed_from_u64(seed);
    return rng.gen();
}

fn get_random_int() -> i32 {
    let nanoseconds = Duration::new(0, 1);
    thread::sleep(nanoseconds);
    let current_time = SystemTime::now().duration_since(UNIX_EPOCH).expect("Time went backwards").as_nanos();
    let seed = current_time as u64;
    let mut rng = rand::rngs::StdRng::seed_from_u64(seed);
    return rng.gen_range(0..=i32::MAX);
}

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

fn measure_qubit(q: &Qubit) -> i32 {
    if q.c0.re == 1 as f64 && q.c0.im == 0 as f64 && q.c1.re == 0 as f64 && q.c1.im == 0 as f64 {
        return 0;
    } else if q.c0.re == 0 as f64 && q.c0.im == 0 as f64 && q.c1.re == 1 as f64 && q.c1.im == 0 as f64 {
        return 1;
    }
    let observation = get_random_float();
    let prob0 = q.c0.norm()*q.c0.norm();
    let prob1 = q.c1.norm()*q.c1.norm();
    if (prob0 == 1 as f64 && prob0 == prob1) || (prob0 == 0 as f64 &&  prob0 == prob1) {
        return -1;
    }
    if prob0 == prob1 {
        return f64::round(observation) as i32;
    } else {
        let larger_prob = if prob0 > prob1 { prob0 } else { prob1 };
        if larger_prob == prob0 && prob1 < observation {
            return 0;
        } else if larger_prob == prob1 && prob0 < observation {
            return 1;
        }
    }
    return -1;
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

fn measure_qregister(qr: &QuantumRegister) -> i32 {
    let mut equal_probs = true;
    let mut probs = vec![0.0; qr.qubits.len()];
    let mut prob_sum: f64 = 0.0;
    for i in 0..qr.qubits.len() {
        probs[i] = qr.qubits[i].c0.norm()*qr.qubits[i].c0.norm() + qr.qubits[i].c1.norm()*qr.qubits[i].c1.norm();
        prob_sum += probs[i];
    }
    if f64::round(prob_sum) as i32 != 1 {
        return -1;
    }
    for i in 1..qr.qubits.len() {
        if probs[i] != probs[0] {
            equal_probs = false;
            break;
        }
    }
    if equal_probs {
        return get_random_int() % 2_i32.pow(qr.qubits.len() as u32);
    } else {
        let observation = f64::round(prob_sum) * get_random_float();
        let mut accum_prob: f64 = 0.0;
        for i in 0..qr.qubits.len() {
            accum_prob += probs[i];
            if observation <= accum_prob {
                return i as i32;
            }
        }
    }
    return -1;
}

fn main() {
    let cmp0 = Complex64::new(1.0, 0.0);
    let cmp1 = Complex64::new(0.0, 1.0);
    let mut q0 = Qubit{c0: cmp0, c1: cmp1}; // Invalid
    println!("\nFirst {:?}", q0);
    println!("First Qubit Measurement: {}", measure_qubit(&q0));
    q0 = singleton_qubit(cmp1, cmp0); // Invalid
    println!("\nSecond {:?}", q0);
    println!("Second Qubit Measurement: {}", measure_qubit(&q0));
    let cmp2 = Complex64::new(0.0, 0.0); // Always 0
    q0 = singleton_qubit(cmp0, cmp2);
    println!("\nThird {:?}", q0);
    println!("Third Qubit Measurement: {}", measure_qubit(&q0));
    q0 = singleton_qubit(cmp2, cmp0); // Always 1
    println!("\nFourth {:?}", q0);
    println!("Fourth Qbuit Measurement: {}", measure_qubit(&q0));
    let cmp3 = Complex64::new(0.5, 0.0);
    let cmp4 = Complex64::new(0.0, -0.5);
    q0 = singleton_qubit(cmp3, cmp4); // 50/50 Chance to be 0 or 1
    println!("\nFifth {:?}", q0);
    for i in 0..10 {
        println!("Fifth Qubit Measurement # {}: {}", i+1, measure_qubit(&q0));
    }
    let qbits0: Vec<Qubit> = vec![
        q0,
        Qubit {c0: cmp4, c1: cmp3}
    ];
    let qr0 = new_qregister(qbits0);
    println!("\nFirst {:?}", qr0);
    for i in 0..400 {
        println!("First QuantumRegister Measurement # {}: {}", i+1, measure_qregister(&qr0));
    }
    let cmp5 = Complex64::new(1.0 / f64::sqrt(6.0), 0.0);
    let cmp6 = Complex64::new(0.0, -1.0 / f64::sqrt(6.0));
    let cmp7 = Complex64::new(-1.0 / f64::sqrt(6.0), 0.0);
    let qbits1: Vec<Qubit> = vec![
        Qubit {c0: cmp5, c1: cmp6},
        Qubit {c0: cmp6, c1: cmp7},
        Qubit {c0: cmp7, c1: cmp5}
    ];
    let qr1 = new_qregister(qbits1);
    println!("\nSecond {:?}", qr1);
    for i in 0..800 {
        println!("Second QuantumRegister Measurement # {}: {}", i+1, measure_qregister(&qr1));
    }
}