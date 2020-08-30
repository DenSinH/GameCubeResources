import numpy as np

operations = [
    lambda x, y: x + y,
    lambda x, y: x - y,
    lambda x, y: x * y,
    lambda x, y: x / y,
    lambda x, y: -x,
    lambda x, y: x & y,
    lambda x, y: x | y,
    lambda x, y: x ^ y,
    lambda x, y: ~x,
    lambda x, y: x << (y & 31),
    lambda x, y: x >> (y & 31)
]


def do_test(
        opcode: int,
        op1: np.uint32,
        op2: np.uint32,
        sign: bool
) -> np.uint32:
    if sign:
        return np.uint32(operations[opcode](np.int32(op1), np.int32(op2)))
    return np.uint32(operations[opcode](op1, op2))
