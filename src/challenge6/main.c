#include "../utils/hamming.h"
#include "../utils/base64.h"
#include "../utils/fileutils.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main() {
    // char str1[] = "this is a test";
    // char str2[] = "wokka wokka!!!";
    // uint64_t distance = hamming_distance(str1, str2, strlen(str1));
    // printf("%ld\n", distance);

    // char encoded[] = "b3BhYmluaWE=";
    // char* decoded = base64_decode(encoded, strlen(encoded));
    // printf("%s\n", decoded);

    char filename[] = "data";
    int64_t bytes_read;
    char* data = read_file(filename, &bytes_read);
    char* decoded = base64_decode(data, bytes_read);
    uint64_t length = (strlen(data) * 6) >> 3;
    for (uint64_t i = 0; i < length; ++i) {
        printf("%c", decoded[i]);
    }
    printf("\n");
    // printf("%d\n", strlen(decoded));
    free(data);
    free(decoded);

    return 0;
}