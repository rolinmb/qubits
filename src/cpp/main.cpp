#include "cpp_qubits.h"

int main()
{
    Qubit q0 = singletonQubit(std::complex<float>(1.f, 0.f), std::complex<float>(0.f, 0.f));
    q0.toString();
    Qubit q1 = Qubit(std::complex<float>(-1.f/2.f, 0.f), std::complex<float>(0.f, 1.f/2.f));
    Qubit q2 = Qubit(std::complex<float>(0.f, 1.f/2.f), std::complex<float>(-1.f/2.f, 0.f));
    std::vector<Qubit> qbits;
    qbits.push_back(q1);
    qbits.push_back(q2);
    QuantumRegister qr = QuantumRegister(qbits);
    qr.toString();
    return 0;
}