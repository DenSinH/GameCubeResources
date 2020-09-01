#include "double_fuzzer.h"

#include "../default.h"
#include "../output.h"
#include "data.h"

#include <stdbool.h>
#include <math.h>

static const char* opcodes[7] = {
    "+", "-", "*", "/", "NEG op1 ", "MADD", "MSUB"
};

double do_test_double(s_operation_double test) {
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

void double_fuzzer_main(int argc, char **argv) {

    init_output();

    s_operation_double test;
    double got;
    for (int i = 0; i < NUMBER_OF_TESTS; i++) {
        output("Running test %d", i);
        test = double_tests[i];

        got = do_test_double(test);
        if (fabs(got - test.result) > 0.01f) {
            output("Failed test %d opc %d: %f %s %f, %f == %f (got %f)", i, test.opcode, test.op1, opcodes[test.opcode], test.op2, test.op3, test.result, got);
            stop();
        }
    }

    output("Passed all tests");
    stop();
}
