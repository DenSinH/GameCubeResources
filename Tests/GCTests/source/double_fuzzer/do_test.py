import numpy as np

operations = [
    lambda x, y, z: x + y,
    lambda x, y, z: x - y,
    lambda x, y, z: x * y,
    lambda x, y, z: x / y,
    lambda x, y, z: -x,
    lambda x, y, z: x * y + z,
    lambda x, y, z: x * y - z,
]


def do_test(
        opcode: int,
        op1: np.double,
        op2: np.double,
        op3: np.double,
) -> np.double:
    return np.double(operations[opcode](op1, op2, op3))
