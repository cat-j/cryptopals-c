#include "../utils/hamming.h"
#include "../utils/base64.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main() {
    // char str1[] = "this is a test";
    // char str2[] = "wokka wokka!!!";
    // uint64_t distance = hamming_distance(str1, str2, strlen(str1));
    // printf("%ld\n", distance);

    char encoded[] = "TQ==";
    char* decoded = base64_decode(encoded, strlen(encoded));
    printf("%s\n", decoded);

    return 0;
}