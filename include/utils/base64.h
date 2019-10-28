#ifndef _BASE64_H
#define _BASE64_H

#include <stdint.h>

#define ENCODING_TABLE_LENGTH 64

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};
                                
/*
Convert ASCII string to base64.
*/
char* base64_encode(char* ascii, uint64_t length);

/*
Convert base64 string to ASCII.
*/
char* base64_decode(char* encoded, uint64_t length);

/*
Get a char's index in the encoding table.
*/
char get_index(char encoded_char);

#endif