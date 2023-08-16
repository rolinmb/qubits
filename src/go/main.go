package main

import (
    "fmt"
    "math"
    "math/cmplx"
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

func main() {
    c0 := complex(1.0, 0.0)
    c1 := complex(0.0, 0.0)
    qubit, err := newQubit(c0, c1)
    if err != nil {
        fmt.Println("Error: ", err)
        return
    }
    fmt.Printf("Qubit: C0 = %f + %fi, C1 = %f + %fi\n", real(qubit.C0), imag(qubit.C0), real(qubit.C1), imag(qubit.C1))
}