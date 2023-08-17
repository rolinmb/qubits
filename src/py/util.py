import numpy as np
import os

def get_true_random():
    return int.from_bytes(os.urandom(8), byteorder="big") / ((1 << 64) - 1)

def get_true_random_int():
    return int.from_bytes(os.urandom(8), byteorder="big")