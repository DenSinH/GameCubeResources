#include "single_fuzzer.h"

#include "../default.h"
#include "../output.h"
#include "data.h"

#include <stdbool.h>

static const char* opcodes[5] = {
    "+", "-", "*", "/", "NEG op1 "
};

u32 do_test_single(s_operation_single test) {
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
        test = single_tests[i];
        got = do_test_single(test);
        out_to_SIO(i);
        if (got != test.result) {
            output("Failed test %d opc %d: %f %s %f == %f (got %f)", i, test.opcode, test.op1, opcodes[test.opcode], test.op2, test.result, got);
            stop();
        }
    }

    output("Passed all tests");
    stop();
}
