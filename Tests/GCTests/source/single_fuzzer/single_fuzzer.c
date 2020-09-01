#include "single_fuzzer.h"

#include "../default.h"
#include "../output.h"
#include "data.h"

#include <stdbool.h>
#include <math.h>

static const char* opcodes[7] = {
    "+", "-", "*", "/", "NEG op1 ", "MADD", "MSUB"
};

float do_test_single(s_operation_single test) {
    switch (test.opcode) {
        case 0:
            return test.op1 + test.op2;
        case 1:
            return test.op1 - test.op2;
        case 2:
            return test.op1 * test.op2;
        case 3:
            return test.op1 / test.op2;
        case 4:
            return -test.op1;
        case 5:
            return test.op1 * test.op2 + test.op3;
        case 6:
            return test.op1 * test.op2 - test.op3;
        default:
            output("Invalid operation: %d", test.opcode);
            stop();
            return 0;
    }
}

void single_fuzzer_main(int argc, char **argv) {

    init_output();

    s_operation_single test;
    float got;
    for (int i = 0; i < NUMBER_OF_TESTS; i++) {
        output("Running test %d", i);
        test = single_tests[i];

        // out_to_SIO(i);
        // out_to_SIO(*(u32*)&test.result);

        got = do_test_single(test);
        if (fabs(got - test.result) > 0.01f) {
            output("Failed test %d opc %d: %f %s %f, %f == %f (got %f)", i, test.opcode, test.op1, opcodes[test.opcode], test.op2, test.op3, test.result, got);
            stop();
        }
    }

    output("Passed all tests");
    stop();
}
