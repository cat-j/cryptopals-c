#include "../utils/fileutils.h"
#include "../utils/encryption.h"
#include "../utils/hamming.h"
#include <string.h>
#include <stdio.h>

#define KEY_LENGTH 3

int main() {
    char filename[] = "data";
    unsigned char key[] = "ICE";
    int64_t bytes_read;
    char* data = read_file(filename, &bytes_read);
    char* encrypted = xor_encrypt(data, key, bytes_read, KEY_LENGTH);
    print_hex(encrypted, bytes_read);
    free(data);
    free(encrypted);

    char str1[] = "this is a test";
    char str2[] = "wokka wokka!!!";
    uint64_t distance = hamming_distance(str1, str2, strlen(str1));
    printf("%ld\n", distance);
    return 0;
}