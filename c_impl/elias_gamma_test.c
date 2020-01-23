#include <stdio.h>
#include "lib/elias_gamma.h"

#define DATA_SIZE 3

int main(int argc, char const *argv[])
{   
    uint32_t data[DATA_SIZE] = { 2, 25, 17};
    uint32_t encoded[DATA_SIZE * 2] = { 0 }; // must init with zeros
    uint32_t decoded[DATA_SIZE] = { 0 }; // must init with zeros
    int i;

    printf("Data:\n");
    for(i = 0; i < DATA_SIZE; i++){
        printf("%u ", data[i]);
    }

    uint32_t encoded_size = elias_gamma_encode_array(data, DATA_SIZE, encoded);

    uint32_t decoded_size = elias_gamma_decode_array(encoded, encoded_size, decoded);
    printf("\nDecoded:\n");
    for(i = 0; i < decoded_size; i++){
        printf("%u ", *(decoded + i));
    }
    // Make sure decoded and input data are equal
    ensure_equal(data, decoded, DATA_SIZE);
    float compression = (float) (DATA_SIZE  / encoded_size);
    printf("\nCompression ratio: %.2f\n", compression);
}