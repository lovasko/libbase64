#include "base64.h"

static char
encode(uint8_t i)
{
  if (i >= 64) return '\0';
  if (i == 63) return '/';
  if (i == 62) return '+';
  if (i >= 52) return '0' + (i - 52);
  if (i >= 26) return 'a' + (i - 26);
  if (i >= 0)  return 'A' + (i);

  return '?';
}

int
base64_encode(uint8_t* in, size_t in_len, char** out)
{
  size_t i;
  size_t o;
  size_t over;
  uint32_t stage;

  if (in == NULL || out == NULL)
    return BASE64_E_NULL;

  if (in_len == 0)
    return BASE64_E_LENGTH;

  over = in_len % 3;

  for (i = 0, o = 0; i < (in_len - over); i += 3, o += 4) {
    stage = 0;
    stage |= in[i];   stage <<= 8;
    stage |= in[i+1]; stage <<= 8;
    stage |= in[i+2];

    *out[o+3] = encode(stage & 0x3f); stage >>= 6;
    *out[o+2] = encode(stage & 0x3f); stage >>= 6;
    *out[o+1] = encode(stage & 0x3f); stage >>= 6;
    *out[o]   = encode(stage & 0x3f);
  }

  if (over == 2) {
    stage = 0;
    stage |= in[i];   stage <<= 8;
    stage |= in[i+1]; stage <<= 8;

    *out[o+3] = '=';
    *out[o+2] = encode(stage & 0x3f); stage >>= 6;
    *out[o+1] = encode(stage & 0x3f); stage >>= 6;
    *out[o]   = encode(stage & 0x3f);
  }

  if (over == 1) {
    stage = (uint32_t)in[i];

    *out[o+3] = '=';
    *out[o+2] = '=';
    *out[o+1] = encode(stage & 0x3f); stage >>= 6;
    *out[o]   = encode(stage & 0x3f);
  }

  return BASE64_OK;
}
