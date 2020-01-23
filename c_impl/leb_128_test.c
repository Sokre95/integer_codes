#include <stdio.h>

#include "lib/utils.h"
#include "lib/leb128.h"

#define DATA_SIZE 8

int main(int argc, char const *argv[])
{
  uint32_t data[DATA_SIZE] = { 123, 12, 451, 1, 10000000, 800, 45, 150 };
  uint8_t encoded[DATA_SIZE * sizeof(uint32_t)];
  uint32_t decoded[DATA_SIZE];
  int i;

  uint32_t encoded_size = uleb128_encode(data, DATA_SIZE, encoded);
  printf("Encoded bytes: ");
  for (i = 0; i < encoded_size; i++){
    printf("%d ", encoded[i]);
  }

  uleb128_decode(encoded, encoded_size, decoded);
  printf("\nDecoded: ");
  for(i = 0; i < DATA_SIZE; i++){
    printf("%d ", *(decoded + i));
  }
  // Make sure decoded and input data are equal
  ensure_equal(data, decoded, DATA_SIZE);

  float compression = (float) ( DATA_SIZE * sizeof(uint32_t) ) / encoded_size;
  printf("\nCompression ratio: %.2f\n", compression);
  
  return 0;
}