#include "fileutils.h"

char* hex_decode_file(char filename[], int64_t* bytes_read) {
    FILE* f = fopen(filename, "rb");
    char* buffer;
    int64_t length = -1;

    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length * sizeof(char));
        
        if (buffer) {
            fread(buffer, 1, length, f);
        } else {
            length = -1;
        }

        fclose(f);
    }

    *bytes_read = length;
    return buffer;
}