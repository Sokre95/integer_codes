#include <vector>
#include "leb128.h"

using namespace std;

int main(int argc, char const *argv[])
{
  std::vector<uint32_t> data = { 123, 12, 451, 1, 10000000, 800, 45, 150 };
  
  std::vector<uint8_t> encoded = LEB128::u_encode(data);
  std::vector<uint32_t> decoded = LEB128::u_decode(encoded);

  printf("Encoded: ");
  for (uint8_t byte : encoded){
    printf("%d ", byte);
  }

  printf("\nDecoded: ");
  for(uint32_t num: decoded){
    printf("%d ", num);
  }

  float compression = float( data.size() * sizeof(uint32_t) ) / encoded.size();
  printf("\nCompression ratio: %.2f\n", compression);
  return 0; 
}