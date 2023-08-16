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
    printf("\nZ / W = {%f + %fi}\n", sum.real, sum.imag);
    Qubit q = newQubit(z, w);
    qubitToString(q);
    printf("\nRNG Result: %f", genRandom());
    for (int i = 0; i < 10; i++) {
        printf("\nQubit Measurement %d: %d", i+1, measure(q));
    }
    float* coords = bloch_coordinates(q);
    printf("\n\nBloch Coordinates of Qubit: [");
    for (int i = 0; i < 3; i++) {
        printf("%f", coords[i]);
        if (i < 2) {
            printf(", ");
        }
    }
    printf("]");
    free(coords);
    Complex b = {-1/sqrtf(2), 0};
    Qubit s = newQubit(z, b);
    Qubit t = newQubit(b, z);
    Qubit* registerQubits[] = {&s, &t};
    QuantumRegister qRegister = newQuantumRegister(registerQubits, 2);
    return 0;
}