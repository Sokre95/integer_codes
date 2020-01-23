#ifndef _ELIAS_delta_
#define _ELIAS_delta_

#include "utils.h"
#include "types.h"

#define BITS_IN_SINGLE_WORD (sizeof(uint32_t) * 8)

uint32_t elias_delta_encode_array(uint32_t *data, uint32_t size, uint32_t *encoded);
uint32_t elias_delta_decode_array(uint32_t *encoded, uint32_t word_count, uint32_t *decoded);

#endif