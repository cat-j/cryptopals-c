#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "encryption.h"
#include "fileutils.h"

int main() {
    char filename[] = "byteData";
    int64_t bytes_read;
    unsigned char key;
    char* ciphertext = read_file(filename, &bytes_read);
    char* plaintext = frequency_decrypt(ciphertext, bytes_read, &key, 0);
    printf("%s\n", plaintext);
    free(ciphertext);
    free(plaintext);
    return 0;
}