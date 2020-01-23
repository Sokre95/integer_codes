#ifndef _ELIAS_GAMMA_
#define _ELIAS_GAMMA_

#include "utils.h"
#include "types.h"

#define BITS_IN_SINGLE_WORD (sizeof(uint32_t) * 8)

uint8_t elias_gamma_encode(uint32_t number, uint32_t* encoded);
uint32_t elias_gamma_decode(uint32_t number);
uint32_t elias_gamma_encode_array(uint32_t *data, uint32_t size, uint32_t *encoded);
uint32_t elias_gamma_decode_array(uint32_t *encoded, uint32_t word_count, uint32_t *decoded);

#endif