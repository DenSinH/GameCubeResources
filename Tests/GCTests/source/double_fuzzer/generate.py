from do_test import do_test, operations
import numpy as np
import random
import struct
import binascii


def float_to_hex(f):
    return hex(struct.unpack('<I', struct.pack('<f', float(f)))[0])


number_of_tests = 100000

includes = \
"""
#include "../default.h"
#include <stdbool.h>
#include <math.h>
"""

typedef = \
f"""
#define NUMBER_OF_TESTS {number_of_tests}

typedef struct s_operation_double {{
    u8 opcode;
    double op1;
    double op2;
    double op3;
    double result;
}} s_operation_double;
"""

tests = []
for i in range(number_of_tests):
    opcode = random.randint(0, len(operations) - 1)
    f1 = np.double(np.random.uniform(np.finfo(np.float32).min, np.finfo(np.float32).max))
    f2 = np.double(np.random.uniform(np.finfo(np.float32).min, np.finfo(np.float32).max))
    f3 = np.double(np.random.uniform(np.finfo(np.float32).min, np.finfo(np.float32).max))
    f4 = np.double(np.random.uniform(np.finfo(np.float32).min, np.finfo(np.float32).max))
    op1 = np.double(f1 / f2)
    op2 = np.double(f3 / f4)
    op3 = np.double(f2 / f3)
    result = do_test(opcode, op1, op2, op3)

    tests.append(
        f"{{ .opcode = {opcode}, .op1 = {op1:f}f, .op2 = {op2:f}f, .op3 = {op3:f}f, .result = {f'{result:f}'.replace('inf', 'INFINITY')} }}  /* {float_to_hex(op1)} | {float_to_hex(op2)} | {float_to_hex(result)} */"
    )

array = \
"""
static const s_operation_double double_tests[NUMBER_OF_TESTS] = {{
    {0}
}};
""".format(",\n    ".join(tests))

with open("./data.h", "w+") as f:
    f.write(
"""
#ifndef DATA_H
#define DATA_H
{0}
#endif // DATA_H
""".strip().format(includes + typedef + array))
