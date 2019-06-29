#ifndef _FILEUTILS_H
#define _FILEUTILS_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*
Return contents of `filename` and write size to `bytes_read`.
If an error occurs, write -1.
*/
char* hex_decode_file(char filename[], int64_t* bytes_read);

/*
Return contents of `filename` split into lines as array elements
and write line size to `bytes_per_line` and file lines to `lines_read`.
If an error occurs, write -1.
*/
char** hex_decode_file_lines(char filename[], int64_t* bytes_per_line, int64_t* lines_read);

#endif