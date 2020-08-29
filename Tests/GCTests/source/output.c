#include "output.h"
#include "default.h"

void out_to_SIO(u32 value) {
    u32* SIO_ptr = SIIOBUFFER;
    *SIO_ptr = value;
}

void init_output() {
    out_to_SIO((u32)(&output_buffer));
}
