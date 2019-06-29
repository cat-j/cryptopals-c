#ifndef _ENCRYPTION_H
#define _ENCRYPTION_H

#include <stdint.h>
#include <stdlib.h>

/*
XOR-combine two equal-length buffers.
*/
char* xor_buffers(char* buf1, char* buf2, uint64_t length);

#endif