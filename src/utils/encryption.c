#include "encryption.h"
#include "hamming.h"

char* xor_buffers(char* buf1, char* buf2, uint64_t length) {
    char* result = (char*) malloc(length + 1);

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

    free(counts);
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

    free(frequencies);
    return result;
}

char* xor_encrypt(char* plaintext, unsigned char* key, uint64_t plaintext_length,
        uint64_t key_length)
{
    char* ciphertext = malloc(plaintext_length + 1);
    char current_byte;

    for (int i = 0; i < plaintext_length; i++) {
        current_byte = plaintext[i] ^ key[i%key_length];
        ciphertext[i] = current_byte;
    }

    ciphertext[plaintext_length] = 0;
    return ciphertext;
}

char* frequency_decrypt(char* ciphertext, uint64_t ciphertext_length, unsigned char* key,
        double* score_ptr)
{
    const uint64_t key_length = 1;
    unsigned char* current_key = malloc(key_length);
    char* current_plaintext;
    char* best_plaintext = malloc((ciphertext_length + 1));
    double best_score = DBL_MAX, current_score;

    for (uint32_t i = 0; i < 256; ++i) {
        *current_key = (unsigned char) i;
        current_plaintext = xor_encrypt(ciphertext, current_key, ciphertext_length, key_length);
        current_score = score_english_frequency(current_plaintext, ciphertext_length);
        
        if (current_score < best_score) {
            strncpy(best_plaintext, current_plaintext, ciphertext_length);
            best_score = current_score;
        }

        free(current_plaintext);
    }

    if (score_ptr != 0) {
        *score_ptr = best_score;
    }

    free(current_key);
    return best_plaintext;
}

char** get_n_best_plaintexts(char** ciphertexts, uint64_t ciphertext_length, unsigned char** keys,
        uint64_t n_ciphertexts, uint64_t n, double* scores)
{
    char** result = malloc(n * sizeof(char*));
    double current_score, worst_best_score;
    char* current_plaintext;
    uint64_t worst_score_idx;

    // Decrypt the first n ciphertexts
    for (uint64_t i = 0; i < n; ++i) {
        current_plaintext = frequency_decrypt(ciphertexts[i], ciphertext_length, keys[i], &current_score);
        result[i] = current_plaintext;
        scores[i] = current_score;
    }

    // Decrypt the rest of the ciphertexts and replace worst of the best whenever a better one is found
    for (uint64_t i = n; i < n_ciphertexts; ++i) {
        current_plaintext = frequency_decrypt(ciphertexts[i], ciphertext_length, keys[i], &current_score);
        worst_best_score = find_max(scores, n, &worst_score_idx);
        if (current_score < worst_best_score) {
            strncpy(result[worst_score_idx], current_plaintext, ciphertext_length);
            scores[worst_score_idx] = current_score;
        }
    }

    free(current_plaintext);
    return result;
}

double find_max(double arr[], uint64_t length, uint64_t* idx) {
    double max_so_far = arr[0], current;
    *idx = 0;

    for (int i = 0; i < length; ++i) {
        current = arr[i];
        if (current > max_so_far) {
            max_so_far = current;
            *idx = i;
        }
    }

    return max_so_far;
}

double find_min(double arr[], uint64_t length, uint64_t* idx) {
    double min_so_far = arr[0], current;
    *idx = 0;

    for (int i = 0; i < length; ++i) {
        current = arr[i];
        if (current < min_so_far) {
            min_so_far = current;
            *idx = i;
        }
    }

    return min_so_far;
}

void get_key_sizes(char* ciphertext, uint64_t n, uint64_t* key_size_arr,
        uint64_t key_size_limit)
{
    double* distances = malloc(n * sizeof(double));
    double current_distance, worst_best_distance;
    uint64_t worst_distance_idx;

    for (uint64_t block_size = 1; block_size < n + 1; ++block_size) {
        distances[block_size-1] = normalised_hamming_distance(ciphertext, block_size);
        key_size_arr[block_size-1] = block_size;
    }

    for (uint64_t block_size = n + 1; block_size < key_size_limit; ++block_size) {
        current_distance = normalised_hamming_distance(ciphertext, block_size);
        worst_best_distance = find_max(distances, n, &worst_distance_idx);
        if (current_distance < worst_best_distance) {
            distances[worst_distance_idx] = current_distance;
            key_size_arr[worst_distance_idx] = block_size;
        }
    }
}

double normalised_hamming_distance(char* ciphertext, uint64_t block_size) {
    char* block1 = malloc(block_size);
    char* block2 = malloc(block_size);
    memcpy(block1, ciphertext, block_size);
    memcpy(block2, ciphertext + block_size, block_size);
    uint64_t distance = hamming_distance(block1, block2, block_size);
    free(block1);
    free(block2);
    return ((double) distance) / block_size;
}

char** get_blocks(char* ciphertext, uint64_t length, uint64_t key_size) {
    char** result = malloc(key_size * sizeof(char*));
    uint64_t rem = length % key_size;
    uint64_t block_size = length / key_size + (length%key_size != 0); // ceiling
    uint64_t whole_blocks = (rem == 0) ? key_size : rem; // how many blocks are complete

    for(uint64_t i = 0; i < key_size; ++i) {
        if (i < whole_blocks) {
            result[i] = malloc(block_size);
        } else {
            result[i] = malloc(block_size - 1); // incomplete block
        }
    }

    // Now that the blocks have been allocated, copy the characters
    for (uint64_t i = 0; i < length; ++i) {
        result[i%key_size][i/key_size] = ciphertext[i];
    }

    return result;
}