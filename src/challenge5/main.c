#include "../utils/fileutils.h"
#include "../utils/encryption.h"

#define KEY_LENGTH 3

int main() {
    char filename[] = "data";
    unsigned char key[] = "ICE";
    int64_t bytes_read;
    char* data = read_file(filename, &bytes_read);
    char* encrypted = xor_encrypt(data, key, bytes_read, KEY_LENGTH);
    print_hex(encrypted, bytes_read);
    free(data);
    free(encrypted);
    return 0;
}