#include "c_qubits.h"

int main() {
    Complex z = {1/sqrtf(2), 0};
    Complex w = {0, 1/sqrtf(2)};
    cmplxToString(z);
    printf("\n|Z| = %f\n", cmplx_abs(z));
    cmplxToString(w);
    printf("\n|W| = %f\n", cmplx_abs(w));
    Complex sum = cmplx_add(z, w);
    printf("\nZ + W = {%f + %fi}", sum.real, sum.imag);
    sum = cmplx_sub(z, w);
    printf("\nZ - W = {%f + %fi}", sum.real, sum.imag);
    sum = cmplx_mult(z, w);
    printf("\nZ x W = {%f + %fi}", sum.real, sum.imag);
    sum = cmplx_divi(z, w);
    printf("\nZ / W = {%f + %fi}", sum.real, sum.imag);
    Qubit q = singletonQubit(z, w);
    qubitToString(q);
    for (size_t i = 0; i < 10; i++) { // 50% chance to collapse to 0 or 1
        printf("\nSingleton Qubit Measurement %d: %d", i+1, measureQubit(q));
    }
    float* coords = bloch_coordinates(q);
    printf("\n\nBloch Coordinates of Qubit: [");
    for (size_t i = 0; i < 3; i++) {
        printf("%f", coords[i]);
        if (i < 2) {
            printf(", ");
        }
    }
    printf("]");
    free(coords);
    Complex b = {-0.5f, 0.f};
    Complex c = {0.f, 0.5f};
    Qubit s = {b, c};
    Qubit t = {c, b};
    Qubit* registerQubits0[2] = {&s, &t};
    QuantumRegister qRegister0 = newQuantumRegister(registerQubits0, 2);
    qRegisterToString(qRegister0);
    for (size_t i = 0; i < 100; i++) { // 25% chance to collapse to 00, 01, 10, 11
        printf("\nQuantum Register Measurement %d: %d", i+1, measureRegister(qRegister0));
    }
    free(qRegister0.qubits);
    return 0;
}