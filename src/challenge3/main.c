#include "../utils/fileutils.h"
#include "../utils/encryption.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>

int main() {
    char filename[] = "byteData";
    int64_t bytes_read;
    char key;
    char* ciphertext = hex_decode_file(filename, &bytes_read);
    char* plaintext = frequency_decrypt(ciphertext, bytes_read, &key);
    printf("%s\n", plaintext);
    free(plaintext);
    return 0;
}