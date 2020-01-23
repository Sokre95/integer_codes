#include "utils.h"

double log2(double n){  
    return log(n)/log(2);  
}  

void bin(unsigned n) { 
    unsigned i; 
    for (i = 1 << 31; i > 0; i = i / 2) 
        (n & i)? printf("1"): printf("0"); 
}

void ensure_equal(uint32_t *data, uint32_t *decoded, const uint32_t size){
  for (int i = 0; i < size; ++i){
    assert(data[i] == decoded[i]);
  }
}