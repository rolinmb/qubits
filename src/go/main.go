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

func newQubit(c0, c1 complex128) (*Qubit, error) {
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

func main() {
    c0 := complex(0.0, 0.0)
    c1 := complex(0.0, 1.0)
    q, err := newQubit(c0, c1)
    if err != nil {
        fmt.Println("Error: ", err)
        return
    }
    observation := getObservation()
    fmt.Println(observation)
    measurement := measure(q)
    fmt.Println(measurement)
    qubitToString(q)
}