#include "default.h"
#include "output.h"

#include <stdbool.h>


u32 getCR() {
    u32 out;
    __asm__(
        "mfcr %0" : "=b"(out)
    );
    return out;
}

bool isPrime(i32 value) {
    for (int i = 2; i * i < value; i++) {
        if (!(value % i))
            return false;
    }
    return true;
}

int main(int argc, char **argv) {

    init_output();

    register i32 i = 2;
    register u32 u = 0;

    while(1) {
        output("%d\n", i);
        i++;
        u--;
    }
	return 0;
}
