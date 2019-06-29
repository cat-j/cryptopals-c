#include "encryption.h"

char* xor_buffers(char* buf1, char* buf2, uint64_t length) {
    char* result = (char*) malloc((length + 1) * sizeof(char));

    for (uint64_t i = 0; i < length; ++i) {
        result[i] = buf1[i] ^ buf2[i];
    }
    result[length] = 0;

    return result;
}

uint64_t get_idx(char my_char) {
    if (my_char >= 'A' && my_char <= 'Z') {
        return my_char - 'A';
    } else if (my_char >= 'a' && my_char <= 'z') {
        return my_char - 'a';
    } else {
        return 26;
    }
}

int is_alpha_or_space(char my_char) {
    return (my_char >= 'A' && my_char <= 'Z') || (my_char >= 'a' && my_char <= 'z') || my_char == ' ';
}

double* analyse_frequencies(char* plaintext, uint64_t length) {
    uint64_t* counts = malloc(ALPHA_SPACE * sizeof(uint64_t));
    for (uint64_t i = 0; i < ALPHA_SPACE; ++i) {
        counts[i] = 0;
    }    

    uint64_t idx;
    char current_char;
    for (uint64_t i = 0; i < length; ++i) {
        current_char = plaintext[i];
        if (is_alpha_or_space(current_char)) {
            idx = get_idx(current_char);
            ++counts[idx];
        }
    }

    double* result = malloc(ALPHA_SPACE * sizeof(double));
    for(uint64_t i = 0; i < ALPHA_SPACE; ++i) {
        result[i] = (double) counts[i] / length;
    }

    return result;
}