#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "encryption.h"
#include "fileutils.h"

int main() {
    char filename1[] = "buffer1";
    char filename2[] = "buffer2";
    int64_t bytes_read;
    
    char* buffer1 = read_file(filename1, &bytes_read);
    char* buffer2 = read_file(filename2, &bytes_read);
    char* result = xor_buffers(buffer1, buffer2, strlen(buffer2));
    for (uint64_t i = 0; i < strlen(result); ++i) {
        printf("%x", result[i]);
    }
    printf("\n");
    
    free(buffer1);
    free(buffer2);
    free(result);
    return 0;
}