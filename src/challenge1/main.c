#include "../utils/base64.h"
#include <stdio.h>

int main() {
    char teststr[] = "Man";
    char* encoded = hex_to_base64((char*) &teststr, 3);
    printf("%s\n", encoded);
    return 0;
}