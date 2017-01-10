#include "base64.h"

static uint8_t
decode(char c)
{
	if (c >= 'A' && c <= 'Z') return (c - 'A');
	if (c >= 'a' && c <= 'z') return (c - 'a') + 26;
	if (c >= '0' && c <= '9') return (c - '0') + 52;
	if (c == '+')             return 62;
	if (c == '/')             return 63;

	return 255;
}

int
base64_decode(char* in, size_t in_len, uint8_t** out)
{
	size_t i;
	size_t o;
	uint32_t res;
	uint8_t d[4];

	if (in == NULL || out == NULL)
		return BASE64_E_NULL;

	if (in_len == 0)
		return BASE64_E_LENGTH;

	if (in_len % 4 != 0)
		return BASE64_E_INPUT;

	for (i = 0, o = 0; i < in_len; i += 4, o += 3) {
		d[0] = decode(in[i]);
		d[1] = decode(in[i+1]);
		d[2] = decode(in[i+2]);
		d[3] = decode(in[i+3]);

		if (d[0] == 255
		 || d[1] == 255
		 || d[2] == 255
		 || d[3] == 255)
			return BASE64_E_INPUT;

		res = 0;
		res |= d[0]; res <<= 6;
		res |= d[1]; res <<= 6;
		res |= d[2]; res <<= 6;
		res |= d[3]; res <<= 6;

		*(uint32_t*)(&out[o]) |= res;
	}

	return BASE64_OK;
}
