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

func getObservation() float64 {
    rand.Seed(time.Now().UnixNano())
    return rand.Float64()
}

func measure(q *Qubit) int {
    if real(q.C0) == 1 && imag(q.C0) == 0 && real(q.C1) == 0 && imag(q.C1) == 0 {
        return 0
    } else if real(q.C0) == 0 && imag(q.C0) == 0 && real(q.C1) == 1 && imag(q.C1) == 0 {
        return 1
    }
    observation := getObservation()
    prob0 := cmplx.Abs(q.C0)*cmplx.Abs(q.C0)
    prob1 := cmplx.Abs(q.C1)*cmplx.Abs(q.C1)
    if prob0 == prob1 {
        return int(observation)
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
    fmt.Printf("\n[{%f + %fi}, {%f + %fi]\n", real(q.C0), imag(q.C0), real(q.C1), imag(q.C1))
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

func registerToString(qr QuantumRegister) {
    fmt.Println("\n~")
    for i:= 0; i < len(qr.qubits); i++ {
        fmt.Printf("\n[{%f + %fi}, {%f + %fi]\n", real(qr.qubits[i].C0), imag(qr.qubits[i].C0), real(qr.qubits[i].C1), imag(qr.qubits[i].C1))
    }
    fmt.Println("~\n")
}

func main() {
    c0 := complex(0.0, 0.0)
    c1 := complex(0.0, 1.0)
    q0, err := singletonQubit(c0, c1)
    if err != nil {
        fmt.Println("Error: ", err)
        return
    }
    measurement := measure(q0)
    fmt.Println(measurement)
    qubitToString(q0)
    c2 := complex(-0.5, 0.0)
    c3 := complex(0.0, 0.5)
    q1 := Qubit{C0: c2, C1: c3}
    q2 := Qubit{C0: c3, C1: c2}
    qbits := []Qubit{q1, q2}
    qr := QuantumRegister{qubits: qbits}
    registerToString(qr)
}