#include "../utils/fileutils.h"
#include "../utils/encryption.h"
#include <stdint.h>

int main() {
    char filename[] = "byteData";
    int64_t bytes_per_line, lines_read;
    double scores[10];
    char** ciphertexts = hex_decode_file_lines(filename, &bytes_per_line, &lines_read);
    char** keys = malloc(10 * sizeof(char));
    for (int i = 0; i < 10; ++i) {
        keys[i] = malloc(1);
    }
    char** best_plaintexts = get_n_best_plaintexts(ciphertexts, bytes_per_line, keys,
        lines_read, 10, scores);
    
    for (int i = 0; i < lines_read; ++i) {
        printf("%s\n", ciphertexts[i]);
    }

    for (int i = 0; i < lines_read; ++i) {
        free(ciphertexts[i]);
    }

    free(ciphertexts);
    return 0;
}