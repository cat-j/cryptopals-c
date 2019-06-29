#ifndef _FILEUTILS_H
#define _FILEUTILS_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*
Return contents of `filename` and write size to `bytes_read`.
If an error occurs, write -1.
*/
char* read_file(char filename[], int64_t* bytes_read);

#endif