#ifndef BASE64_H
#define BASE64_H

#include <stdlib.h>
#include <stdint.h>

#define BASE64_OK       0
#define BASE64_E_NULL   1
#define BASE64_E_LENGTH 2
#define BASE64_E_INPUT  3

int base64_encode(uint8_t* in, size_t in_len, char** out);
int base64_decode(char* in, size_t in_len, uint8_t** out);

#endif
