#include "../../utils/base64.h"
#include <stdio.h>

int main() {
    char teststr[] = "Ma";
    char* encoded = hex_to_base64(&teststr, 2);
    printf("%s\n", encoded);
    return 0;
}