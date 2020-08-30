from do_test import do_test, operations
import numpy as np
import random

number_of_tests = 100000

includes = \
"""
#include "../default.h"
#include <stdbool.h>
"""

typedef = \
f"""
#define NUMBER_OF_TESTS {number_of_tests}

typedef struct s_operation {{
    u8 opcode;
    u32 op1;
    u32 op2;
    bool sign;
    u32 result;
}} s_operation;
"""

tests = []
for i in range(number_of_tests):
    opcode = random.randint(0, len(operations) - 1)
    op1 = np.uint32(random.randint(np.iinfo(np.uint32).min, np.iinfo(np.uint32).max))
    op2 = np.uint32(random.randint(np.iinfo(np.uint32).min, np.iinfo(np.uint32).max))
    sign = random.choice(["false", "true"])
    result = do_test(opcode, op1, op2, sign == "true")
    tests.append(
        f"{{ .opcode = {opcode}, .op1 = {op1:#010x}, .op2 = {op2:#010x}, .sign = {sign:5s}, .result = {result:#010x} }}"
    )

array = \
"""
static const s_operation tests[NUMBER_OF_TESTS] = {{
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
