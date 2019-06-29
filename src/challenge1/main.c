#include "../utils/base64.h"
#include "../utils/fileutils.h"
#include <stdio.h>

int main() {
    char filename[8] = "data.txt";
    int64_t bytes_read;
    char* data = read_file(filename, &bytes_read);
    printf("%s\n", data);
    // printf("%s\n", encoded);
    return 0;
}