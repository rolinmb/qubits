#include "cpp_qubits.h"
#include <iostream>

int main()
{
    Qubit q0(std::complex<float>(1.f, 0.f), std::complex<float>(0.f, 0.f));
    q0.toString();
    return 0;
}