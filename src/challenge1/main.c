#include <stdio.h>
#include <string.h>

#include "base64.h"
#include "fileutils.h"

int main() {
    char filename[8] = "byteData";
    int64_t bytes_read;
    char* data = read_file(filename, &bytes_read);
    char* encoded = base64_encode(data, strlen(data));
    printf("%s\n", encoded);
    return 0;
}