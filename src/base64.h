#include <string>
#include <vector>
#include <environ.h>

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);
int base64_decode(std::string const& encoded_string, std::vector<l_uint8> target);
