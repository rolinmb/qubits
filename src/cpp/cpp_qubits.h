#include <complex>
#include <string>
#include <vector>
#include <Windows.h>

void seedRandom() {
    LARGE_INTEGER performanceCount;
    FILETIME systemTime;
    ULONGLONG combinedTime;
    QueryPerformanceCounter(&performanceCount);
    GetSystemTimeAsFileTime(&systemTime);
    combinedTime = ((ULONGLONG)systemTime.dwHighDateTime << 32) + systemTime.dwLowDateTime + performanceCount.QuadPart;
    srand((unsigned int)combinedTime);
    Sleep(1);
}

float genRandom() {
    seedRandom();
    return (float)rand() / RAND_MAX;
}   

class Qubit
{
public:
    std::complex<float> C0;
    std::complex<float> C1;

    Qubit(std::complex<float> c0, std::complex<float> c1)
    {
        C0 = c0;
        C1 = c1;
    }

    int measure() {
        if (this->C0.real() == 1 && this->C0.imag() == 0 && this->C1.real() == 0 && this->C1.imag() == 0)
        {
            return 0;
        }
        else if (this->C0.real() == 0 && this->C0.imag() == 0 && this->C1.real() == 1 && this->C1.imag() == 0)
        {
            return 1;
        }
        float observation = genRandom();
        float prob0 = abs(this->C0)*abs(this->C0);
        float prob1 = abs(this->C1)*abs(this->C1);
        if (prob0 == prob1)
        {
            return round(observation);
        }
        else
        {
            float largerProb = (prob0 > prob1) ? prob0 : prob1;
            if (largerProb == prob0 && prob1 < observation)
            {
                return 0;
            }
            else if (largerProb == prob1 && prob0 < observation)
            {
                return 1;
            }
        }
    }

    void toString()
    {
        printf("\n[{%f + %fi}, {%f + %fi}]\n", this->C0.real(), this->C0.imag(), this->C1.real(), this->C1.imag());
    }
};

Qubit singletonQubit(std::complex<float> c0, std::complex<float> c1) {
    if (round(abs(c0)*abs(c0) + abs(c1)*abs(c1)) != 1)
        {
            throw std::invalid_argument("Invalid complex number parameters to construct Qubit.");
        }
    return Qubit(c0, c1);
}

class QuantumRegister
{
public:
    std::vector<Qubit> qubits;

    QuantumRegister(std::vector<Qubit> qbits)
    {
        if (validateRegister(qbits))
        {
            this->qubits = qbits;
        }
        else
        {
            throw std::invalid_argument("Invalid Qubits vector, cannot form QuantumRegister");
        } 
    }

    int measure() {
        bool equalProbs = true;
        float* probs = (float*)malloc(this->qubits.size() * sizeof(float));
        if (probs == NULL) {
            perror("Memory allocation failed in QuantumRegister.measure()");
            exit(EXIT_FAILURE);
        }
        float probSum = 0.f;
        for (size_t i = 0; i < this->qubits.size(); i++) {
            probs[i] = abs(this->qubits[i].C0)*abs(this->qubits[i].C0) + abs(this->qubits[i].C1)*abs(this->qubits[i].C1);
            probSum += probs[i];
        }
        if (round(probSum) != 1) { // Re-validate; A QuantumRegister has a probability sum == 1
            perror("Cannot measure an invalid QuantumRegister (probabilities sum != 1)");
            exit(EXIT_FAILURE);
        }
        for (size_t i = 1; i < this->qubits.size(); i++) { // Check for equal probability states
            if (probs[i] != probs[0]) {
                equalProbs = false;
                break;
            }
        }
        if (equalProbs) {
            free(probs);
            seedRandom();
            return rand() % (int)pow(2, this->qubits.size()); // 2^n_qubits possible states
        } else {
            float observation = round(probSum) * genRandom();
            float accumProb = 0.f;
            for (int i = 0; i < this->qubits.size(); i++) {
                accumProb += probs[i];
                if (observation <= accumProb) {
                    free(probs);
                    return i;
                }
            }
        }
        free(probs);
        return -1;
    }

    void toString()
    {
        printf("\n~\n");
        for (size_t i = 0; i < this->qubits.size(); i++) {
            printf("[{%f + %fi}, {%f + %fi}]\n", this->qubits[i].C0.real(), this->qubits[i].C0.imag(), this->qubits[i].C1.real(), this->qubits[i].C1.imag());
        }
        printf("~\n");
    }

private:
    bool validateRegister(std::vector<Qubit> qbits)
    {
        float sum = 0;
        for (size_t i = 0; i < qbits.size(); i++) {
            sum += abs(qbits[i].C0)*abs(qbits[i].C0) + abs(qbits[i].C1)*abs(qbits[i].C1);
        }
        return (round(sum) == 1) ? true : false;
    }
};