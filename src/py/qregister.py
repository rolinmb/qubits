from qubit import *
"""
def validateRegister(qbits):
    sum = 0
    for q in qbits:
        sum += (abs(q.c0)**2 + abs(q.c1)**2)
    return True if int(round(sum, 0)) == 1 else False

class qRegister:
    def __init__(self, qbits):
        if not validateRegister(qbits):
            raise Exception("-> Qubits not valid to form a Quantum Register.")
        self.qubits = qbits
        self.n_qubits = len(qbits)
        self.n_states = 2**self.n_qubits
    
    def measure(self):
        equalProbs = True
        probs = []
        probSum = 0
        for i in range(0, self.n_qubits):
            probs.append(abs((self.qubits[i].c0)**2) + (abs(self.qubits[i].c1)**2))
            probSum += probs[i]
        if round(probSum, 0) != 1:
            raise Exception("-> Invalid qubits to form Quantum Register")
        for i in range(1, self.n_qubits):
            if probs[i] != probs[0]:
                equalProbs = False
        if equalProbs:
            return get_true_random_int() % 2**self.n_qubits
        else: 
            observation = round(probSum, 0) * get_true_random()
            accumProb = 0
            for i in range(0, self.n_qubits):
                accumProb += probs[i]
                if observation <= accumProb:
                    return i

        return -1

    def __repr__(self):
        representation = "\n~\n"
        for i in range(0, self.n_qubits):
            representation += f"([{round(self.qubits[i].c0.real, 5)} + {round(self.qubits[i].c0.imag, 5)}i]; [{round(self.qubits[i].c1.real, 5)} + {round(self.qubits[i].c1.imag, 5)}i])\n"
        return representation+"~\n"
"""
class qRegister:
    def __init__(self, qubits):
        self.qubits = qubits
        self.n_qubits = len(qubits)

    def measure(self):
        collapsed_state = ""
        for qubit in self.qubits:
            outcome = qubit.measure()
            collapsed_state += str(outcome)
        return collapsed_state
    """
    def __repr__(self):
        representation = ""
        for qubit in self.qubits:
            representation += f"{qubit}\n"
        return representation
    """
    def __repr__(self):
        representation = "\n"
        for i in range(0, self.n_qubits):
            representation += f"([{round(self.qubits[i].c0.real, 5)} + {round(self.qubits[i].c0.imag, 5)}i]; [{round(self.qubits[i].c1.real, 5)} + {round(self.qubits[i].c1.imag, 5)}i])\n"
        return representation
        
if __name__ == "__main__":
    qubits = [qubit(0.5+0j, 0-0.5j), qubit(-0.5+0j, 0+0.5j)]
    register = qRegister(qubits) # 25% chance to collapse to 00, 01, 10, 11
    print(register)
    for i in range(0, 100):
        collapsed_state = register.measure()
        print(f"Quantum Register Measurement {i}: {collapsed_state}")