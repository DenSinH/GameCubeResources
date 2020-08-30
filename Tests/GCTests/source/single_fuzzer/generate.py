from do_test import do_test, operations
import numpy as np
import random

number_of_tests = 1000

includes = \
"""
#include "../default.h"
#include <stdbool.h>
#include <math.h>
"""

typedef = \
f"""
#define NUMBER_OF_TESTS {number_of_tests}

typedef struct s_operation_single {{
    u8 opcode;
    float op1;
    float op2;
    float result;
}} s_operation_single;
"""

tests = []
for i in range(number_of_tests):
    opcode = random.randint(0, len(operations) - 1)
    op1 = np.float32(np.random.uniform(np.finfo(np.float32).min, np.finfo(np.float32).max))
    op2 = np.float32(np.random.uniform(np.finfo(np.float32).min, np.finfo(np.float32).max))
    result = f"{do_test(opcode, op1, op2):f}".replace("inf", "INFINITY")
    if "INFINITY" not in result:
        result += "f"

    tests.append(
        f"{{ .opcode = {opcode}, .op1 = {op1:f}f, .op2 = {op2:f}f, .result = {result} }}"
    )

array = \
"""
static const s_operation_single single_tests[NUMBER_OF_TESTS] = {{
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
