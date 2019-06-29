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

double score_english_frequency(char* plaintext, uint64_t length) {
    double* frequencies = analyse_frequencies(plaintext, length);
    double result = 0;
    double difference;

    for (uint64_t i = 0; i < ALPHA_SPACE; ++i) {
        difference = frequencies[i] - english_frequencies[i];
        result += difference * difference;
    }

    return result;
}

char* xor_encrypt(char* plaintext, unsigned char* key, uint64_t plaintext_length, uint64_t key_length) {
    char* ciphertext = malloc((plaintext_length + 1) * sizeof(char));
    char current_byte;

    for (int i = 0; i < plaintext_length; i++) {
        current_byte = plaintext[i] ^ key[i%key_length];
        ciphertext[i] = current_byte;
    }

    ciphertext[plaintext_length] = 0;
    return ciphertext;
}

char* frequency_decrypt(char* ciphertext, uint64_t ciphertext_length, unsigned char* key) {
    const uint64_t key_length = 1;
    unsigned char* current_key = malloc(key_length * sizeof(char));
    char* current_plaintext;
    char* best_plaintext = malloc((ciphertext_length + 1) * sizeof(char));
    double best_score = DBL_MAX, current_score;

    for (uint32_t i = 0; i < 256; ++i) {
        *current_key = (unsigned char) i;
        current_plaintext = xor_encrypt(ciphertext, current_key, ciphertext_length, key_length);
        current_score = score_english_frequency(current_plaintext, ciphertext_length);
        
        if (current_score < best_score) {
            // I have no idea why memcpy isn't working
            for (uint64_t j = 0; j < ciphertext_length; ++j) {
                best_plaintext[j] = current_plaintext[j];
            }
            best_score = current_score;
        }
        
        free(current_plaintext);
    }

    free(current_key);
    return best_plaintext;
}