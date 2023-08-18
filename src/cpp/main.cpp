#include "cpp_qubits.h"

int main()
{
    Qubit q0 = singletonQubit(std::complex<float>(0.f, 0.5f), std::complex<float>(0.f, 0.5f));
    q0.toString();
    for (size_t i = 0; i < 10; i++){ // 50% chance to collapse to 0 or 1
        printf("\nSingleton Qubit Measurement %d: %d", i+1, q0.measure());
    }
    printf("\n");
    Qubit q1 = Qubit(std::complex<float>(-0.5f, 0.f), std::complex<float>(0.f, 0.5f));
    Qubit q2 = Qubit(std::complex<float>(0.f, 0.5f), std::complex<float>(-0.5f, 0.f));
    std::vector<Qubit> qbits;
    qbits.push_back(q1);
    qbits.push_back(q2);
    QuantumRegister qr = QuantumRegister(qbits); // 25% chance to collapse to 00, 01, 10, 11
    qr.toString();
    for (size_t i = 0; i < 100; i++) {
        printf("\nQuantum Register Measurement %d: %d", i+1, qr.measure());
    }
    qbits.clear();
    return 0;
}