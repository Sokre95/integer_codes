#ifndef _LEB_128_
#define _LEB_128_

#include <vector>
#include <iostream>

class LEB128
{
public:
  static std::vector<uint8_t> u_encode(const std::vector<uint32_t> &in){
    std::vector<uint8_t> out;

    for (uint32_t num : in) {
      while (num > 0x7f) {
        out.push_back(num | 0x80);
        num >>= 7;
      }
      out.push_back(num & 0x7f);
    }
    return out;
  }

  static std::vector<uint32_t> u_decode(const std::vector<uint8_t> &in){
    std::vector<uint32_t> out;
    uint32_t num = 0;
    uint8_t shift = 0;

    for(uint8_t byte : in){
      num |= uint32_t(byte & 0x7f) << shift;
      shift += 7;
      if (byte < 0x80){
        out.push_back(num);
        num = 0;
        shift = 0;
      }
    }
    return out;
  }
};

#endif