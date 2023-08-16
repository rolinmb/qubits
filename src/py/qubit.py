from util import *
import math
import cmath

class qubit:
    def __init__(self, c0, c1):
        #print(f"Qubit constructor called with parameters [{round(c0, 5)} & {round(c1, 5)}] => Sum of Probabilities: {int(round(abs(c0)**2 + abs(c1)**2, 0))}")
        if int(round(abs(c0)**2 + abs(c1)**2, 0)) != 1:
            raise Exception(f"-> Invalid qubit constructor parameters {c0} & {c1}")
        self.c0 = c0
        self.c1 = c1

    def measure(self):
        # handle classical case of |0> and |1>
        if self.c0 == 1.0j and self.c1 == 0+0j:
            return 0
        elif self.c0 == 0+0j and self.c1 == 1+0j:
            return 1        
        # if not-classical, we have a quantum superposition state
        this_obs = get_true_random()
        prob0 = abs(self.c0)**2
        prob1 = abs(self.c1)**2
        largest_prob = max(prob0, prob1)
        if prob0 == prob1: # If we have 'coinflip' superposition
            return int(round(this_obs, 0))
        else:              # Otherwise we have to use this_obs to decide outcome 
            if largest_prob == prob0 and prob1 < this_obs:   # if c0 is more likely and c1 likelyhood < this_obs
                return 0
            elif largest_prob == prob1 and prob0 < this_obs: # if c1 is more likely and c0 likelyhood < this_obs
                return 1

    def get_spherical_coords(self):
        if self.c0 == 1 and self.c1 == 0:
            return [0, 0, 1]
        elif self.c0 == 0 and self.c1 == 1:
            return [0, 0, -1]
        else:
            alpha_theta = 0
            beta_theta = 0
        # try to calculate alpha_theta & beta_theta
        try:
            alpha_theta = math.atan(self.c0.imag / self.c0.real)
            if self.c0.real < 0 and self.c0.imag > 0:
                alpha_theta = math.atan(self.c0.imag / self.c0.real) + math.pi
            
            if self.c0.real < 0 and self.c0.imag < 0:
                alpha_theta = math.atan(self.c0.imag / self.c0.real) + math.pi
        except:
            alpha_theta = 0
        
        try:
            beta_theta = math.atan(self.c1.imag / self.c1.real)
            if self.c1.real < 0 and self.c1.imag > 0:
                beta_theta = math.atan(self.c1.imag / self.c1.real) + math.pi
        
            if self.c1.real < 0 and self.c1.imag < 0:
                beta_theta = math.atan(self.c1.imag / self.c1.real) + math.pi
        except:
            beta_theta = 0

        r_alpha = math.sqrt((self.c1.real**2) + (self.c0.imag**2))
        # r_beta = math.sqrt((self.c1.real**2) + (self.c1.imag**2))

        phi = beta_theta - alpha_theta
        theta = 2 * np.arccos(r_alpha)
        return [1, theta, phi] # X, Y, Z

    def get_bloch_coords(self):
        if self.c0 == 1 and self.c1 == 0:
            return [0, 0, 1]
        elif self.c0 == 0 and self.c1 == 1:
            return [0, 0, -1]
        else:
            alpha_theta = 0
            beta_theta = 0
        # try and calculate alpha_theta & beta_theta
        try:
            alpha_theta = math.atan(self.c0.imag / self.c0.real)
            if self.c0.real < 0 and self.c0.imag > 0:
                alpha_theta = math.atan(self.c0.imag / self.c0.real) + math.pi
            
            if self.c0.real < 0 and self.c0.imag < 0:
                alpha_theta = math.atan(self.c0.imag / self.c0.real) + math.pi
        except:
            alpha_theta = 0
        
        try:
            beta_theta = math.atan(self.c1.imag / self.c1.real)
            if self.c1.real < 0 and self.c1.imag > 0:
                beta_theta = math.atan(self.c1.imag / self.c1.real) + math.pi
        
            if self.c1.real < 0 and self.c1.imag < 0:
                beta_theta = math.atan(self.c1.imag / self.c1.real) + math.pi
        except:
            beta_theta = 0

        r_alpha = math.sqrt((self.c1.real**2) + (self.c0.imag**2))
        # r_beta = math.sqrt((self.c1.real**2) + (self.c1.imag**2))

        phi = beta_theta - alpha_theta
        theta = 2 * np.arccos(r_alpha)
        return [math.sin(theta)*math.cos(phi), math.sin(theta)*math.sin(phi), math.cos(theta)] # [X, Y, Z]

    def __repr__(self):
        return f"[[{round(self.c0.real, 5)}, {round(self.c0.imag, 5)}]; [{round(self.c1.real, 5)}, {round(self.c1.imag, 5)}]]"
    
if __name__ == "__main__":
    pass