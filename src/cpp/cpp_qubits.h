#include <complex>
#include <string>
#include <Windows.h>

class Qubit
{
public:
    std::complex<float> C0;
    std::complex<float> C1;

    Qubit(std::complex<float> c0, std::complex<float> c1)
    {
        if (round(abs(c0)*abs(c0) + abs(c1)*abs(c1)) == 1)
        {
            C0 = c0;
            C1 = c1;
        }
        else {
            throw std::invalid_argument("Invalid complex number parameters to construct Qubit.");
        }
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

    int measure() {
        if (this->C0.real() == 1 && this->C0.imag() == 0 && this->C1.real() == 0 && this->C1.imag() == 0)
        {
            return 0;
        }
        else if (this->C0.real() == 0 && this->C0.imag() == 0 && this->C1.real() == 1 && this->C1.imag() == 0)
        {
            return 1;
        }
        float observation = genRandom(); // TODO: re-implement random number generator in c++
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
        printf("\n[{%f + %fi}, {%f + %fi}]", this->C0.real(), this->C0.imag(), this->C1.real(), this->C1.imag());
    }
};