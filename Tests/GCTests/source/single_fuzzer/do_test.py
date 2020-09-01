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
        op1: np.float32,
        op2: np.float32,
        op3: np.float32,
) -> np.float32:
    return np.float32(operations[opcode](op1, op2, op3))
