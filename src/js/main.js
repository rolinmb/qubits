class Complex { // Made with the help of ChatGPT
    constructor(real, imag) {
        this.real = real;
        this.imag = imag;
    }

    add(other) {
        return new Complex(this.real + other.real, this.imag + other.imag);
    }

    subtract(other) {
        return new Complex(this.real - other.real, this.imag - other.imag);
    }
  
    multiply(other) {
        const realPart = this.real * other.real - this.imag * other.imag;
        const imagPart = this.real * other.imag + this.imag * other.real;
        return new Complex(realPart, imagPart);
    }

    divide(other) {
        const denom = other.real * other.real + other.imag * other.imag;
        if (denom === 0) throw new Error("Division by zero");
        const realPart = (this.real * other.real + this.imag * other.imag) / denom;
        const imagPart = (this.imag * other.real - this.real * other.imag) / denom;
        return new Complex(realPart, imagPart);
    }

    magnitude() {
        return Math.sqrt(this.real * this.real + this.imag * this.imag);
    }

    argument() {
        return Math.atan2(this.imag, this.real);
    }

    conjugate() {
        return new Complex(this.real, -this.imag);
    }

    toString() {
        const sign = this.imag >= 0 ? "+" : "-";
        return `${this.real} ${sign} ${Math.abs(this.imag)}i`;
    }
}

function jsTrueRand() { // Generate a random float from the inclusive range [0, 1]
    const seed = new Date().getTime();
    const modulus = 2 ** 31 - 1;
    const multiplier = 48271; // Multiplier for the LCG algorithm (IDK WHAT THIS IS CHATGPT WROTE IT!)
    const randomNumber = (seed * multiplier) % modulus;
    return randomNumber / modulus;
}

const TOLERANCE = 1e-10;

class Qubit {
    constructor(c0, c1) {
        this.c0 = c0;
        this.c1 = c1;
        this.validate();
    }

    validate() {
        const magSum = this.c0.magnitude() ** 2 + this.c1.magnitude() ** 2;
        if (Math.abs(magSum - 1) > TOLERANCE) {
            throw new Error("Invalid qubit state: the sum of squares of the magnitudes of c0 and c1 must be approximately 1.");
        }
    }

    measure() {
        if (this.c0.real === 1 && this.c0.imag === 0 && this.c1.real === 0 && this.c1.imag === 0) {
            return 0;
        } else if (this.c0.real === 0 && this.c0.imag === 0 && this.c1.real === 1 && this.c1.imag === 0) {
            return 1;
        }
        const thisObs = jsTrueRand();
        const prob0 = Math.abs(this.c0.magnitude()) ** 2;
        const prob1 = Math.abs(this.c1.magnitude()) ** 2;
        const largestProb = Math.max(prob0, prob1);
        if (prob0 === prob1) {
            return int(Math.round(thisObs));
        } else {
            if (largestProb === prob0 && prob1 < thisObs) {
                return 0;
            } else if (largestProb === prob1 && prob0 < thisObs) {
                return 1;
            }
        }
    }
}
