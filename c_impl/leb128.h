#ifndef _LEB_128_
#define _LEB_128_

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

uint8_t uleb128_encode(uint32_t *data, uint32_t size, uint8_t *encoded);
void uleb128_decode(uint8_t *data, uint32_t bytes_count, uint32_t *decoded);

#endif