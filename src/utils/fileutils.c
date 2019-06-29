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

char** hex_decode_file_lines(char filename[], int64_t* bytes_per_line, int64_t* lines_read) {
    FILE* f = fopen(filename, "rb");
    char* buffer;
    uint64_t i = 0;

    // Get number of lines to read and bytes per line
    fscanf(f, "%ld", lines_read);
    fscanf(f, "%ld", bytes_per_line);

    char** array_of_buffers = malloc(*lines_read * sizeof(char *));
    
    // Store `bytes_per_line` bytes in each array element
    while (i < *lines_read) {
        buffer = malloc(*bytes_per_line * sizeof(char));
        fread(buffer, 1, *bytes_per_line, f);
        array_of_buffers[i] = buffer;
        ++i;
    }

    fclose(f);

    return array_of_buffers;
}