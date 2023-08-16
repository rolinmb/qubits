#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <Windows.h>

#define PI 3.14159265358979323846

typedef struct {
    float real;
    float imag;
} Complex;

float cmplx_abs(Complex z) {
    return sqrtf((z.real*z.real) + (z.imag*z.imag));
}

float argument(Complex z) {
    return atan2f(z.imag, z.real);
}

Complex cmplx_add(Complex z, Complex w) {
    Complex result = {0, 0};
    result.real = z.real+w.real;
    result.imag = z.imag+w.imag;
    return result;
}

Complex cmplx_sub(Complex z, Complex w) {
    Complex result = {0, 0};
    result.real = z.real-w.real;
    result.imag = z.imag-w.imag;
}

Complex cmplx_mult(Complex z, Complex w) {
    Complex result = {0, 0};
    result.real = (z.real*w.real) - (z.imag*w.imag);
    result.imag = (z.real*w.imag) + (z.imag*w.real);
    return result;
}

Complex cmplx_divi(Complex z, Complex w) {
    Complex result = {0, 0};
    result.real = ((z.real*w.real) + (z.imag*w.imag))/((w.real*w.real) + (w.imag*w.imag));
    result.imag = ((z.imag*w.real) - (z.real*w.imag))/((w.real*w.real) + (w.imag*w.imag));
    return result;
}

Complex cmplx_exp(Complex z) {
    Complex result = {0, 0};
    result.real = expf(z.real)*cosf(z.imag);
    result.imag = expf(z.real)*sinf(z.imag);
    return result;
}

Complex cmplx_ln(Complex z) {
    Complex result = {0, 0};
    result.real = logf(cmplx_abs(z));
    result.imag = argument(z);
    return result;
}

void cmplxToString(Complex c) {
    printf("\n{%f + %fi}", c.real, c.imag);
}

typedef struct {
    Complex C0;
    Complex C1;
} Qubit;

bool validateQubit(Qubit q) {
    if (round(cmplx_abs(q.C0)*cmplx_abs(q.C0) + cmplx_abs(q.C1)*cmplx_abs(q.C1)) != 1) {
        printf("\nInvalid complex numbers to create a qubit.");
        return false;
    } else {
        return true;
    }
}

Qubit newQubit(Complex c0, Complex c1) {
    Qubit qbit = {c0, c1};
    if (!validateQubit(qbit)) {
        qbit.C0.real = 0;
        qbit.C0.imag = 0;
        qbit.C1.real = 0;
        qbit.C1.imag = 0;
    }
    return qbit;
}

float genRandom() {
    LARGE_INTEGER performanceCount;
    FILETIME systemTime;
    ULONGLONG combinedTime;
    QueryPerformanceCounter(&performanceCount);
    GetSystemTimeAsFileTime(&systemTime);
    combinedTime = ((ULONGLONG)systemTime.dwHighDateTime << 32) + systemTime.dwLowDateTime + performanceCount.QuadPart;
    srand((unsigned int)combinedTime);
    Sleep(1);
    return (float)rand() / RAND_MAX;
}

int measure(Qubit q) {
    if (q.C0.real == 1 && q.C0.imag == 0 && q.C1.real == 0 && q.C1.imag == 0) {
        return 0;
    } else if (q.C0.real == 0 && q.C0.imag == 0 && q.C1.real == 1 && q.C1.imag == 0) {
        return 1;
    }
    float observation = genRandom();
    float prob0 = cmplx_abs(q.C0)*cmplx_abs(q.C0);
    float prob1 = cmplx_abs(q.C1)*cmplx_abs(q.C1);
    if (prob0 == prob1) {
        return round(observation);
    } else {
        float largerProb = max(prob0, prob1);
        if (largerProb == prob0 && prob1 < observation) {
            return 0;
        } else if (largerProb == prob1 && prob0 < observation) {
            return 1;
        }
    }
}

float* bloch_coordinates(Qubit q) {
    float* arr = (float *)malloc(sizeof(float) * 3);
    if (arr == NULL) {
        perror("Memory allocation failed in bloch_coordinates.");
        exit(EXIT_FAILURE);
    }
    if (q.C0.real == 1 && q.C0.imag == 0 && q.C1.real == 0 && q.C1.imag == 0) {
        arr[0] = 0;
        arr[1] = 0;
        arr[2] = 1;
        return arr;
    } else if (q.C0.real == 0 && q.C0.imag == 0 && q.C1.real == 1 && q.C1.imag == 0) {
        arr[0] = 0;
        arr[1] = 0;
        arr[2] = -1;
        return arr;
    } else {
        float a_theta = atan2f(q.C0.imag, q.C0.real);
        if (q.C0.real < 0  && q.C0.imag > 0 || q.C0.real < 0 && q.C0.imag < 0) {
            a_theta = atan2f(q.C0.imag, q.C0.real) + (float)PI;
        }
        float b_theta = atan2f(q.C1.imag, q.C1.real);
        if (q.C1.real < 0 && q.C1.imag > 0 || q.C1.real < 0 && q.C1.imag < 0) {
            b_theta = atan2f(q.C1.imag, q.C1.real) + (float)PI;
        }
        float r_alpha = sqrtf((q.C1.real*q.C1.real) + (q.C0.imag*q.C0.imag));
        float phi = b_theta - a_theta;
        float theta = 2 * acosf(r_alpha);
        arr[0] = sinf(theta)*cosf(phi);
        arr[1] = sinf(theta)*sinf(phi);
        arr[2] = cosf(theta);
        return arr;
    }
}

void qubitToString(Qubit q) {
    if (q.C0.real == 0 && q.C0.imag == 0 && q.C1.real == 0 && q.C1.imag == 0)
        printf("\n[Invalid Qubit: {%f + %fi}, {%f + %fi}]", q.C0.real, q.C0.imag, q.C1.real, q.C1.imag);
    else {
        printf("\n[{%f + %fi}, {%f + %fi}]", q.C0.real, q.C0.imag, q.C1.real, q.C1.imag);
    }
}

typedef struct {
	Qubit* qubits;
    size_t n_qubits;
} QuantumRegister;

bool validateRegister(Qubit** newQubits, size_t numQubits) {
    float sum = 0;
    for (size_t i = 0; i < numQubits; i++) {
        sum += (cmplx_abs((*newQubits[i]).C0)*cmplx_abs((*newQubits[i]).C0) + cmplx_abs((*newQubits[i]).C1)*cmplx_abs((*newQubits[i]).C1));
    }
    return round(sum) == 1;
}

QuantumRegister newQuantumRegister(Qubit** qubitArr, size_t arrSize) {
	QuantumRegister qRegister;
	qRegister.qubits = (Qubit*)malloc(sizeof(Qubit) * arrSize);
    qRegister.n_qubits = arrSize;
	if (!qRegister.qubits) {
		perror("\nMemory allocation failed in newQuantumRegister.");
        exit(EXIT_FAILURE);
	}
	if (validateRegister(qubitArr, arrSize)) {
        for (size_t i = 0; i < arrSize; i++) {
            qRegister.qubits[i] = *(qubitArr[i]);
        }
	} else {
		printf("\nInvalid qubits for creating a quantum register.");
	}
	return qRegister;
}

void qRegisterToString(QuantumRegister r) {

}