#ifndef _UTILS_
#define _UTILS_

#include <math.h>
#include <stdio.h>
#include <assert.h>
#include "types.h"

double log2(double n);
void bin(unsigned n);
void ensure_equal(uint32_t *data, uint32_t *decoded, const uint32_t size);

#endif