#include "util.h"
#include <openssl/bn.h>
#include "fastconnect/base64.h"
#include "pugixml.hpp"
#include <exception>
#include <openssl/rsa.h>
#include <stdexcept>
BIGNUM *BN_b642bn(const std::string &str)
{
    auto b = base64_decode(str);
    return BN_bin2bn(b.data(), b.size(), NULL);
}
RSA *RSA_from_xmlb64(const std::string &private_key)
{
    auto decoded_key = base64_decode(private_key);
    std::string sprivate_key(decoded_key.begin(), decoded_key.end());
    pugi::xml_document doc;
    auto xml_parse_result = doc.load_buffer(sprivate_key.c_str(), sprivate_key.size());
    if (!xml_parse_result)
    {
        throw std::runtime_error("Failed to parse private key");
    }
    auto rsa_key = doc.child("RSAKeyValue");
    auto n = BN_b642bn(rsa_key.child("Modulus").text().get());
    auto e = BN_b642bn(rsa_key.child("Exponent").text().get());
    auto d = BN_b642bn(rsa_key.child("D").text().get());
    auto p = BN_b642bn(rsa_key.child("P").text().get());
    auto q = BN_b642bn(rsa_key.child("Q").text().get());
    auto dp = BN_b642bn(rsa_key.child("DP").text().get());
    auto dq = BN_b642bn(rsa_key.child("DQ").text().get());
    auto i = BN_b642bn(rsa_key.child("InverseQ").text().get());
    auto rsa = RSA_new();
    RSA_set0_key(rsa, n, e, d);
    RSA_set0_factors(rsa, p, q);
    RSA_set0_crt_params(rsa, dp, dq, i);
    return rsa;
}

std::string to_hex(const unsigned char *data, size_t len)
{
    std::string hex;
    for (size_t i = 0; i < len; i++)
    {
        char buf[3];
        sprintf(buf, "%02x", data[i]);
        hex += buf;
    }
    return hex;
}

std::string to_string(bool b)
{
    return b ? "true" : "false";
}
