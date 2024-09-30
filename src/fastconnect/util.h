#ifndef _UTIL_H_
#define _UTIL_H_

#include <vector>
#include <string>
#include <openssl/types.h>

BIGNUM* BN_b642bn(const std::string& str);
RSA* RSA_from_xmlb64(const std::string& xml);
std::string to_hex(const unsigned char* data, size_t len);
std::string to_string(bool b);
#endif