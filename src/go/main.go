package main

import (
    "fmt"
    "math"
    "math/cmplx"
    "math/rand"
    "time"
)

type Qubit struct {
    C0 complex128
    C1 complex128
}

func singletonQubit(c0, c1 complex128) (*Qubit, error) {
    if math.Round(cmplx.Abs(c0)*cmplx.Abs(c0) +  cmplx.Abs(c1)*cmplx.Abs(c1)) == 1 {
        q := &Qubit{C0: c0, C1: c1}
        return q, nil
    }
    return nil, fmt.Errorf("Invalid complex numbers to contruct Qubit")
}

func getObservationFloat() float64 {
    time.Sleep(1 * time.Nanosecond)
    rand.Seed(time.Now().UnixNano())
    return rand.Float64()
}

func getObservationInt() int {
    time.Sleep(1 * time.Nanosecond)
    rand.Seed(time.Now().UnixNano())
    return rand.Intn(math.MaxInt32)
}

func measureQubit(q *Qubit) int {
    if real(q.C0) == 1 && imag(q.C0) == 0 && real(q.C1) == 0 && imag(q.C1) == 0 {
        return 0
    } else if real(q.C0) == 0 && imag(q.C0) == 0 && real(q.C1) == 1 && imag(q.C1) == 0 {
        return 1
    }
    observation := getObservationFloat()
    prob0 := cmplx.Abs(q.C0)*cmplx.Abs(q.C0)
    prob1 := cmplx.Abs(q.C1)*cmplx.Abs(q.C1)
    if prob0 == prob1 {
        return int(math.Round(observation))
    } else {
        largerProb := math.Max(prob0, prob1)
        if largerProb == prob0 && prob1 < observation {
            return 0
        } else if largerProb == prob1 && prob0 < observation {
            return 1
        }
    }
    return -1
}

func qubitToString(q *Qubit) {
    fmt.Printf("\n[{%f + %fi}, {%f + %fi]\n\n", real(q.C0), imag(q.C0), real(q.C1), imag(q.C1))
}

type QuantumRegister struct {
    qubits []Qubit
}

func validateRegister(qbits []Qubit) bool {
    sum := 0.0
    for i := 0; i < len(qbits); i++ {
        sum += cmplx.Abs(qbits[i].C0)*cmplx.Abs(qbits[i].C0) + cmplx.Abs(qbits[i].C1)*cmplx.Abs(qbits[i].C1)
    }
    if math.Round(sum) == 1 {
        return true
    } else {
        return false
    }
}

func newRegister(qbits []Qubit) (*QuantumRegister, error) {
    if validateRegister(qbits) {
        register := &QuantumRegister{qubits: qbits}
        return register, nil
    }
    return nil, fmt.Errorf("Invalid qubits to form Quantum Register")
}

func measureRegister(qr *QuantumRegister) (int, error) {
    var equalProbs bool = true
    probs := make([]float64, len(qr.qubits))
    var probSum float64 = 0
    for i := 0; i < len(qr.qubits); i++ {
        probs[i] = cmplx.Abs(qr.qubits[i].C0)*cmplx.Abs(qr.qubits[i].C0) + cmplx.Abs(qr.qubits[i].C1)*cmplx.Abs(qr.qubits[i].C1)
        probSum += probs[i]
    }
    if math.Round(probSum) != 1 {
        return -1, fmt.Errorf("Invalid qubits to form Quantum Register, cannot measure")
    }
    for i := 1; i < len(qr.qubits); i++ {
        if probs[i] != probs[0] {
            equalProbs = false
            break
        }
    }
    if equalProbs {
        return getObservationInt() % int(math.Pow(2, float64(len(qr.qubits)))), nil
    } else {
        observation := math.Round(probSum) * getObservationFloat()
        var accumProb float64 = 0
        for i := 0; i < len(qr.qubits); i++ {
            accumProb += probs[i]
            if observation <= accumProb {
                return int(i), nil
            }
        }
    }
    return -1, fmt.Errorf("Could not measure Quantum Register")
}

func registerToString(qr *QuantumRegister) {
    fmt.Println("\n~")
    for i:= 0; i < len(qr.qubits); i++ {
        fmt.Printf("[{%f + %fi}, {%f + %fi]\n", real(qr.qubits[i].C0), imag(qr.qubits[i].C0), real(qr.qubits[i].C1), imag(qr.qubits[i].C1))
    }
    fmt.Println("~\n")
}

func main() {
    c0 := complex(0.5, 0.0)
    c1 := complex(0.0, 0.5)
    q0, err := singletonQubit(c0, c1)
    if err != nil {
        fmt.Println("Error: ", err)
        return
    }
    qubitToString(q0)
    for i := 0; i < 100; i++ {
        fmt.Printf("Singleton Qubit Measurement %d: %d\n", i+1, measureQubit(q0))
    }
    c2 := complex(-0.5, 0.0)
    c3 := complex(0.0, 0.5)
    q1 := Qubit{C0: c2, C1: c3}
    q2 := Qubit{C0: c3, C1: c2}
    qbits0 := []Qubit{q1, q2}
    qr0, err := newRegister(qbits0)
    if err != nil {
        fmt.Println("Error: ", err)
        return
    }
    registerToString(qr0)
    for i := 0; i < 400; i++ {
        regiMeasurement, err := measureRegister(qr0)
        if err != nil {
            break
        }
        fmt.Printf("Quantum Register Measurement %d: %d\n", i+1, regiMeasurement)
    }
    c4 := complex(1/math.Sqrt(float64(6)), 0)
    c5 := complex(0, -1/math.Sqrt(float64(6)))
    c6 := complex(-1/math.Sqrt(float64(6)), 0)
    q3 := Qubit{C0: c4, C1: c5}
    q4 := Qubit{C0: c5, C1: c6}
    q5 := Qubit{C0: c4, C1: c6}
    qbits1 := []Qubit{q3, q4, q5}
    qr1, err := newRegister(qbits1)
    if err != nil {
        fmt.Println("Error: ", err)
        return
    }
    registerToString(qr1)
    for i := 0; i < 800; i++ {
        regiMeasurement, err := measureRegister(qr1)
        if err != nil {
            break
        }
        fmt.Printf("Quantum Register Measurement %d: %d\n", i+1, regiMeasurement)
    }
}