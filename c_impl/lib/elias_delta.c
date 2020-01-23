#include "elias_delta.h"

uint32_t elias_delta_encode_array(uint32_t *data, uint32_t size, uint32_t *encoded){
    uint32_t word_count = 0;
    uint32_t current_number;
    
    uint32_t encoded_number;
    uint32_t binary_part;
    uint8_t unary_digits;
    uint8_t encoded_number_length;
    
    uint32_t lower_mask;
    uint32_t upper_mask;

    uint8_t next_unused_bit_position = 0;
    uint8_t bits_left_in_word = BITS_IN_SINGLE_WORD;

    for (int i = 0; i < size; ++i){
        current_number = *(data +i);

        encoded_number_length = elias_gamma_encode(current_number, &encoded_number);

        if(next_unused_bit_position == BITS_IN_SINGLE_WORD){
            next_unused_bit_position = 0;
        }

        // check if ecoded number will fit in current word 
        bits_left_in_word = BITS_IN_SINGLE_WORD - next_unused_bit_position;
        // binary part is coded with same number of bits as unary part + delimiter
        if (bits_left_in_word >= encoded_number_length){
            *(encoded + word_count) |= (encoded_number << next_unused_bit_position);
            // subtract number of bits used 
            next_unused_bit_position += encoded_number_length; 
        }
        else{
            // calculate masks for spliting the encoded word into two halfs
            lower_mask = (0x01 << bits_left_in_word) - 1;
            upper_mask = (0x01 << encoded_number_length) - 1 - lower_mask;

            //put lower part in current word
            *(encoded + word_count) |= (encoded_number & lower_mask) << next_unused_bit_position;
            //put upper part in next word
            *(encoded + word_count + 1) = (encoded_number & upper_mask) >> bits_left_in_word;
            //increment word counter
            word_count++;
            // increment bit position
            next_unused_bit_position = encoded_number_length - bits_left_in_word;
        }
    }
    // return number of words used for coding data array
    return word_count + 1;

}
uint32_t elias_delta_decode_array(uint32_t *encoded, uint32_t word_count, uint32_t *decoded){

}
