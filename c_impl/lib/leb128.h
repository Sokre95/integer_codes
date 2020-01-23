#ifndef _LEB_128_
#define _LEB_128_

#include "types.h"

uint32_t uleb128_encode(uint32_t *data, uint32_t size, uint8_t *encoded);
uint32_t uleb128_decode(uint8_t *data, uint32_t bytes_count, uint32_t *decoded);

#endif