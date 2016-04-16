#ifndef __BITSTRING_H_
#define __BITSTRING_H_
#include <stdint.h>

// These generate a K&R string with the bit representation of an input, num, and return a pointer to the string it produces.
// They handle up to 64 bits.
// They are not terminated with line endings.
// The string represents how the number would appear in a register of the minimum size needed to store that number: padded with 0s from the beginning, or 1s for a negative number

// Typically if num < 0 you want to use Signed, Unsigned will produce a 64 char string if num was negative.

char* GenerateBitStringUnsigned(const uint64_t num);
char* GenerateBitStringSigned(const int64_t num);

#endif
