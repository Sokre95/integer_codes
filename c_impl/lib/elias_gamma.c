#include "elias_gamma.h"

uint32_t elias_gamma_encode_array(uint32_t *data, uint32_t size, uint32_t *encoded){
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

uint32_t elias_gamma_decode_array(uint32_t *encoded, uint32_t word_count, uint32_t *decoded){
    uint8_t unary_digits = 0;
    uint32_t binary_part;
    uint32_t decoded_word = 0;
    uint32_t current_word;
    uint32_t size = 0;
    uint8_t current_bit_position = 0;
    uint8_t next_word = FALSE;

    for (int i = 0; i < word_count; ++i){
        current_word = *(encoded + i);
        current_bit_position = 0;

        while( current_bit_position < BITS_IN_SINGLE_WORD){
            
            // count number of unary digits
            while(current_word & 0x01 == 0x01){
                unary_digits++;
                // increment bit position
                current_bit_position++;
                // shift word right to check next bit
                current_word >>= 1;
                // if end of current_word is reached go to next word and continue counting unary digits
                if (current_bit_position == BITS_IN_SINGLE_WORD){
                    next_word = TRUE;
                    break;
                }
            }
            // if there is no unary digits -> end of decoding
            if(unary_digits == 0){
                break;
            }
            // goto next word --> back to foor loop
            if (next_word){
                next_word = FALSE;
                break;
            }
            // remove delimiter
            current_word >>= 1; 
            // after removing delimiter binary part is left in lower unary_digits bits
            binary_part = current_word & ((0x1 << unary_digits) - 1);
            // shift word right - prepare next encoded word for decoding (counting unary digits)
            current_word >>= unary_digits;
            // reconstruct number by unary and binary part
            decoded_word = (int)pow(2, unary_digits) + binary_part;
            // save to output array
            *(decoded + size) = decoded_word;
            // increment current_bit_position fir delimiter + binary part size (same as unary)
            current_bit_position += unary_digits + 1;
            // increment total count of decoded numbers
            size++;
            unary_digits = 0;
        }
    }
    return size;
}

uint8_t elias_gamma_encode(uint32_t number, uint32_t* encoded){
    uint8_t unary_digits;
    uint32_t binary_part;


    unary_digits = (uint8_t)floor(log2(number));
    binary_part = number - (uint8_t)pow(2, unary_digits);

    *encoded = 0;                // reset temp variable
    *encoded |= binary_part;     // bbbb 
    *encoded <<= 1;              // bbbb[0] - zero as delimiter
    *encoded <<= unary_digits;   // bbbb[0]0000 - shift left to make space for unary bits
    *encoded |= ((0x1 << unary_digits) - 1); // bbbb[0]uuuu - add unary bits 

    return unary_digits * 2 + 1; // lenght
}

uint32_t elias_gamma_decode(uint32_t number){
    uint8_t unary_digits;
    uint32_t binary_part;

    while(number & 0x01 == 0x01){
        unary_digits++;
        // shift encoded number right to check next bit
        number >>= 1;
    }
    // remove delimiter
    number >>= 1; 
    // after removing delimiter binary part is left in lower unary_digits bits
    binary_part = number & ((0x1 << unary_digits) - 1);
    // reconstruct number by unary and binary part
    return (uint32_t)pow(2, unary_digits) + binary_part;
}