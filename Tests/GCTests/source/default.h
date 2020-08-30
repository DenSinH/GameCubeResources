#ifndef DEFAULT_H
#define DEFAULT_H

#include <stdint.h>

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;


static void stop() {
    while (1) {}
}

#endif // DEFAULT_H
