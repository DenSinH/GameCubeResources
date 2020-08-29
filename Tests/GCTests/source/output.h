#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>

#include "default.h"

#define SIIOBUFFER 0xCC006480
#define OUTPUT_BUFFER_LENGTH 0x100

static char output_buffer[OUTPUT_BUFFER_LENGTH];

void out_to_SIO(u32 value);
void init_output();
#define output(message, ...) sprintf(output_buffer, message, ##__VA_ARGS__)


#endif // OUTPUT_H
