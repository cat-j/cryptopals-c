#include "../utils/fileutils.h"
#include "../utils/encryption.h"
#include <stdint.h>

#define N_BEST_PLAINTEXTS 10

int main() {
    char filename[] = "byteData";
    int64_t bytes_per_line, lines_read;
    double scores[N_BEST_PLAINTEXTS];
    char** ciphertexts = hex_decode_file_lines(filename, &bytes_per_line, &lines_read);
    
    char** keys = malloc(N_BEST_PLAINTEXTS * sizeof(char));
    for (int i = 0; i < N_BEST_PLAINTEXTS; ++i) {
        keys[i] = malloc(1);
    }

    char** best_plaintexts = get_n_best_plaintexts(ciphertexts, bytes_per_line, keys,
        lines_read, N_BEST_PLAINTEXTS, scores);
    
    for (int i = 0; i < lines_read; ++i) {
        printf("%s\n", ciphertexts[i]);
    }

    for (int i = 0; i < lines_read; ++i) {
        free(ciphertexts[i]);
    }

    free(ciphertexts);
    return 0;
}