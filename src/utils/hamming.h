#ifndef _HAMMING_H
#define _HAMMING_H

#include <stdint.h>

/*
Compute the Hamming distance (number of differing bits)
between `str1` and `str2`, which must be of equal length.
*/
uint64_t hamming_distance(char* str1, char* str2, uint64_t length);

/*
Count the number of 1s in the binary representation of `n`.
*/
uint64_t count_ones(unsigned char n);

#endif