#include "base64.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/*
Convert ASCII string to base64.
Designed with readability (rather than speed) in mind.
*/
char* hex_to_base64(char* ascii, uint64_t len) {
    uint64_t k = 0;
    uint64_t n_bits = len << 3;
    uint64_t n_sextets = n_bits / 6;
    uint64_t remaining_bits = n_bits % 6; // either 0, 2 or 4
    char data, next_highest_bits, sextet;
    
    uint64_t encoded_len = n_sextets + (remaining_bits >> 1);
    char* encoded = malloc((encoded_len + 1) * sizeof(char));
    
    for (uint64_t i = 0; i < len; ++i) {
        data = ascii[i];

        if (i%3 == 0) {
            sextet = data >> 2; // higher 6 bits
            next_highest_bits = (data & 0x3) << 4; // keep lower 2
        } else if (i%3 == 1) {
            sextet = (data >> 4) | next_highest_bits; // 2 lower prev ++ 4 higher
            next_highest_bits = (data & 0xF) << 2; // keep lower 4
        } else {
            sextet = (data >> 6) | next_highest_bits; // 4 lower prev ++ 2 higher
        }

        encoded[k++] = encoding_table[sextet];
        if (i%3 == 2) encoded[k++] = encoding_table[data & 0x3F]; // extra 6 bits to process
    }

    if (remaining_bits != 0) {
        encoded[k++] = encoding_table[next_highest_bits];
        encoded[k++] = '=';
        if (remaining_bits == 4) encoded[k++] = '=';
    }

    encoded[k++] = 0;
    return encoded;
}