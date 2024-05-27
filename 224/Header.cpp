#include "Header.h"

unsigned long long/*size_t*/ operator""_b(const char* dec) {
    unsigned long long tmp{};
    for (size_t i = 0; i < strlen(dec); i++) 
        tmp = tmp * 2 + (dec[i] - '0');
    return tmp;
}

std::string operator""_toBinStr(unsigned long long in) {
    std::string ret{};
    while (in != 0)
    {
        
        ret = ret + ((in % 2) ? std::string("1") : std::string("0"));
        in = in / 2;
    }
    return ret.size() ?
         std::string("0b") + std::string(ret.rbegin(), ret.rend()) :
         std::string("0b0");
}