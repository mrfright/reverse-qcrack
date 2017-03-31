#ifndef REVERSE_BITS
#define REVERSE_BITS
#include <stdint.h>

uint32_t reverse_bits(uint32_t val, uint32_t num_bits) {
    uint32_t reversed = 0;
    while(num_bits) {
        reversed = (val & 1) | (reversed << 1); //asm adds to itself, that faster?
        val >>= 1;
        --num_bits;
    }

    return reversed;
}
#endif
