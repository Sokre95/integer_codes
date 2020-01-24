## C and C++ implementations of various integer codes

This project implements various integer encoding algorithms. For now LEB128 and Elias gamma(γ) formats for coding unsigned integers are implemented (Elias delta will be addedd soon).
LEB128 or Little Endian Base 128 is pretty simple variable length compression often used to code arbitrarily large integers in small number of bytes. 
Elias gamma code (developed by Peter Elias) is a universal code for encoding unsigned integer. It is mostly used for integers whose upper-bound cannot be determined beforehand.

Basic explainantions and examples about this algorithms can be found on wikipedia:
* [LEB128](https://en.wikipedia.org/wiki/LEB128)
* [Elias gamma](https://en.wikipedia.org/wiki/Elias_gamma_coding)

___
### Build project
1. `cd c_impl`
2. `make`

### Run test examples
1. `./bin/leb_128_test.out` or `./bin/elias_gamma_test.out`

___
Note!: This implementations are compiled and tested on STM32 microcontroller. To run `leb128.h` or `elias_gamma.h` on your embedded platform write `uint32_t` and `uint8_t` type definitions and `log2` function implementatin or just use `utils.h` and `types.h` headers.
