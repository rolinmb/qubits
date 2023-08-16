from qubit import *

def validateRegister(qbits):
    sum = 0;
    for q in qbits:
        sum += (abs(q.c0)**2 + abs(q.c1)**2)
    return True if int(round(sum, 0)) == 1 else False

class qRegister:
    def __init__(self, qbits):
        if validateRegister(qbits):
            raise Exception(f"-> Qubits not valid to form a Quantum Register.")
        self.qubits = qbits
        self.n_qubits = len(qbits)
        self.n_states = 2**self.n_qubits

if __name__ == "__main__":
    register = qRegister([qubit(1/np.sqrt(2), -1/np.sqrt(2)), qubit(-1/np.sqrt(2), 1/np.sqrt(2))])
    for i in range(0, len(register.qubits)):
        prob0 = round(abs(register.qubits[i].c0)**2, 2)
        prob1 = round(abs(register.qubits[i].c1)**2, 2)
        print(f"Qubit: {register.qubits[i]} Amplitudes: (0) {prob0} (1): {prob1}")