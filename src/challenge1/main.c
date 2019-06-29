#include "../utils/base64.h"
#include "../utils/fileutils.h"
#include <stdio.h>
#include <string.h>

int main() {
    char filename[8] = "byteData";
    int64_t bytes_read;
    char* data = hex_decode_file(filename, &bytes_read);
    char* encoded = hex_to_base64(data, strlen(data));
    printf("%s\n", encoded);
    return 0;
}