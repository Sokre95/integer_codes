#include "leb128.h"

uint32_t uleb128_encode(uint32_t *data, uint32_t size, uint8_t *encoded){
  uint32_t num;
  uint8_t byte;
  uint32_t i;
  
  uint32_t bytes_count = 0;

  for (i = 0; i < size; i++){
    num = *(data + i);

    while(num > 0){
      byte = (uint8_t)(num & 0x7F);
      num = num >> 7;
      if(num > 0){
        byte = byte | 0x80;
      }
      *(encoded + bytes_count) = byte;
      bytes_count++;
    }
  }
  return bytes_count;
}

uint32_t uleb128_decode(uint8_t *data, uint32_t bytes_count, uint32_t *decoded){
  uint32_t num = 0;
  uint8_t byte;
  uint32_t i; 
  uint8_t shift = 0;
  uint32_t size = 0;

  for(i = 0; i < bytes_count; i++){
    byte = *(data + i);
    
    num |= (uint32_t)(byte & 0x7f) << shift;
    shift += 7;

    if(byte < 0x80){
      *decoded++ = num;
      size++;
      num = 0;
      shift = 0;
    }
  }

  return size;
}
