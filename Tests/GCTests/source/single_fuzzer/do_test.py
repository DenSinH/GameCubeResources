import numpy as np

operations = [
    lambda x, y: x + y,
    lambda x, y: x - y,
    lambda x, y: x * y,
    lambda x, y: x / y,
    lambda x, y: -x,
]


def do_test(
        opcode: int,
        op1: np.float32,
        op2: np.float32
) -> np.uint32:
    return np.float32(operations[opcode](op1, op2))
