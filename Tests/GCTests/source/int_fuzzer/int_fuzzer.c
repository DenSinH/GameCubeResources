#include "int_fuzzer.h"

#include "../default.h"
#include "../output.h"
#include "data.h"

#include <stdbool.h>

#define DO_TEST(_test, _op_macro) \
if (_test.sign) { \
    return (u32)_op_macro((i32)_test.op1, (i32)_test.op2); \
} \
return _op_macro(_test.op1, _test.op2);

#define PLUS(_op1, _op2) ((_op1) + (_op2))
#define MINUS(_op1, _op2) ((_op1) - (_op2))
#define MUL(_op1, _op2) ((_op1) * (_op2))
#define DIV(_op1, _op2) ((_op1) / (_op2))
#define NEG(_op1, _op2) (-(_op1))
#define AND(_op1, _op2) ((_op1) & (_op2))
#define OR(_op1, _op2) ((_op1) | (_op2))
#define XOR(_op1, _op2) ((_op1) ^ (_op2))
#define NOT(_op1, _op2) (~(_op1))
#define SHL(_op1, _op2) ((_op1) << ((_op2) & 31))
#define SHR(_op1, _op2) ((_op1) >> ((_op2) & 31))

static const char* opcodes[11] = {
    "+", "-", "*", "/", "NEG op1 ", "&", "|", "^", "~op1 ", "<<", ">>"
};

u32 do_test_int(s_operation_int test) {
    switch (test.opcode) {
        case 0:
            DO_TEST(test, PLUS)
        case 1:
            DO_TEST(test, MINUS)
        case 2:
            DO_TEST(test, MUL)
        case 3:
            DO_TEST(test, DIV)
        case 4:
            DO_TEST(test, NEG)
        case 5:
            DO_TEST(test, AND)
        case 6:
            DO_TEST(test, OR)
        case 7:
            DO_TEST(test, XOR)
        case 8:
            DO_TEST(test, NOT)
        case 9:
            DO_TEST(test, SHL)
        case 10:
            DO_TEST(test, SHR)
        default:
            output("Invalid operation: %d", test.opcode);
            stop();
            return 0;
    }
}

void int_fuzzer_main(int argc, char **argv) {

    init_output();

    s_operation_int test;
    u32 got;
    for (int i = 0; i < NUMBER_OF_TESTS; i++) {
        test = int_tests[i];
        got = do_test_int(test);
        out_to_SIO(i);
        if (got != test.result) {
            output("Failed test %d opc %d: (sign: %d) %08x %s %08x == %08x (got %08x)", i, test.opcode, test.sign, test.op1, opcodes[test.opcode], test.op2, test.result, got);
            stop();
        }
    }

    output("Passed all tests");
    stop();
}
