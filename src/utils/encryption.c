#include "encryption.h"

char* xor_buffers(char* buf1, char* buf2, uint64_t length) {
    char* result = (char*) malloc((length + 1) * sizeof(char));

    for (uint64_t i = 0; i < length; ++i) {
        result[i] = buf1[i] ^ buf2[i];
    }
    result[length] = 0;

    return result;
}