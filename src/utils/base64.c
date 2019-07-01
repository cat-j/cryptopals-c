#include "base64.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/*
Convert ASCII string to base64.
Designed with readability (rather than speed) in mind.
*/
char* base64_encode(char* ascii, uint64_t length) {
    uint64_t k = 0;
    uint64_t n_bits = length << 3;
    uint64_t n_sextets = n_bits / 6;
    uint64_t remaining_bits = n_bits % 6; // either 0, 2 or 4
    char data, next_highest_bits, sextet;
    
    uint64_t encoded_len = n_sextets + (remaining_bits >> 1);
    char* encoded = malloc((encoded_len + 1));
    
    for (uint64_t i = 0; i < length; ++i) {
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

        encoded[k++] = encoding_table[(uint64_t) sextet];
        if (i%3 == 2) encoded[k++] = encoding_table[data & 0x3F]; // extra 6 bits to process
    }

    if (remaining_bits != 0) {
        encoded[k++] = encoding_table[(uint64_t) next_highest_bits];
        encoded[k++] = '=';
        if (remaining_bits == 2) encoded[k++] = '=';
    }

    encoded[k++] = 0;
    return encoded;
}

char* base64_decode(char* encoded, uint64_t length) {
    uint64_t decoded_length = (length*6) >> 3;
    if (encoded[length-1] == '=') {
        decoded_length--;
    }
    if (encoded[length-2] == '=') {
        decoded_length--;
    }

    char* decoded = malloc(decoded_length + 1);

    uint64_t idx = 0;
    unsigned char data, current_byte;

    for (int i = 0; i < length; ++i) {
        current_byte = get_index(encoded[i]);

        switch (i%4) {
        case 0:
            data = current_byte << 2;
            break;

        case 1:
            data |= (current_byte >> 4) & 0x3; // higher 2 bits of sextet
            decoded[idx] = data;
            data = current_byte << 4;
            ++idx;
            break;

        case 2:
            data |= (current_byte >> 2) & 0xF; // higher 4 bits of sextet
            decoded[idx] = data;
            data = current_byte << 6;
            ++idx;
            break;

        case 3:
            data |= current_byte; // whole sextet
            decoded[idx] = data;
            ++idx;
            break;
        
        default:
            break;
        }
    }
    
    decoded[decoded_length] = 0;

    return decoded;
}

char get_index(char encoded_char) {
    for (int i = 0; i < ENCODING_TABLE_LENGTH; ++i) {
        if (encoding_table[i] == encoded_char)
            return i;
    }
    // Not found
    return -1;
}