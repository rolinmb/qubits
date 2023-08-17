#include "cpp_qubits.h"

int main()
{
    Qubit q0 = singletonQubit(std::complex<float>(0.f, 0.5f), std::complex<float>(0.f, 0.5f));
    q0.toString();
    for (int i = 0; i < 10; i++){
        printf("\nSingleton Qubit Measurement %d: %d", i+1, q0.measure());
    }
    printf("\n");
    Qubit q1 = Qubit(std::complex<float>(-0.5f, 0.f), std::complex<float>(0.f, 0.5f));
    Qubit q2 = Qubit(std::complex<float>(0.f, 0.5f), std::complex<float>(-0.5f, 0.f));
    std::vector<Qubit> qbits;
    qbits.push_back(q1);
    qbits.push_back(q2);
    QuantumRegister qr = QuantumRegister(qbits);
    qr.toString();
    for (int i = 0; i < 100; i++) {
        printf("\nQuantum Register Measurement %d: %d", i+1, qr.measure());
    }
    qbits.clear();
    printf("\n");
    Qubit q3 = Qubit(std::complex<float>(-1.f/sqrtf(6), 0.f), std::complex<float>(0.f, 1.f/sqrtf(6)));
    Qubit q4 = Qubit(std::complex<float>(0.f, 1.f/sqrtf(6)), std::complex<float>(1.f/sqrtf(6), 0.f));
    Qubit q5 = Qubit(std::complex<float>(1.f/sqrtf(6), 0.f), std::complex<float>(-1.f/sqrtf(6), 0.f));
    qbits.push_back(q3);
    qbits.push_back(q4);
    qbits.push_back(q5);
    qr = QuantumRegister(qbits);
    qr.toString();
    for (int i = 0; i < 100; i++) {
        printf("\nQuantum Register Measurement %d: %d", i+1, qr.measure());
    }
    qbits.clear();
    return 0;
}