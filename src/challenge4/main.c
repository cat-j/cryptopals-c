#include "../utils/fileutils.h"
#include "../utils/encryption.h"
#include <stdint.h>

#define N_BEST_PLAINTEXTS 10
#define KEY_LENGTH 1

int main() {
    char filename[] = "byteData";
    int64_t bytes_per_line, lines_read;
    double scores[N_BEST_PLAINTEXTS];
    char** ciphertexts = hex_decode_file_lines(filename, &bytes_per_line, &lines_read);
    
    unsigned char** keys = malloc(N_BEST_PLAINTEXTS * sizeof(unsigned char*));
    for (int i = 0; i < N_BEST_PLAINTEXTS; ++i) {
        keys[i] = malloc(KEY_LENGTH);
    }

    char** best_plaintexts = get_n_best_plaintexts(ciphertexts, bytes_per_line, keys,
        lines_read, N_BEST_PLAINTEXTS, scores);

    uint64_t best_plaintext_idx;
    double min_score = find_min(scores, N_BEST_PLAINTEXTS, &best_plaintext_idx);
    printf("%s", best_plaintexts[best_plaintext_idx]);
    
    for (int i = 0; i < N_BEST_PLAINTEXTS; ++i) {
        free(best_plaintexts[i]);
        free(keys[i]);
    }

    for (int i = 0; i < lines_read; ++i) {
        free(ciphertexts[i]);
    }

    free(best_plaintexts);
    free(keys);
    free(ciphertexts);
    return 0;
}