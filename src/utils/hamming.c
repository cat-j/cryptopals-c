#include "hamming.h"

uint64_t hamming_distance(char* str1, char* str2, uint64_t length) {
    uint64_t result = 0;
    for (int i = 0; i < length; ++i) {
        result += count_ones(str1[i] ^ str2[i]);
    }
    return result;
}

uint64_t count_ones(unsigned char n) {
    uint64_t count = 0;
    while (n > 0) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}