#include "_exports.h"
#include <string>
#include <functional>
#include <openssl/rsa.h>
namespace fastconnect
{
    namespace fctrading
    {
        class api_client
        {
        public:
            FASTCONNECTCLIENT_API static api_client create(const std::string &url, const std::string &id, const std::string &secret, const std::string &private_key = "");

            FASTCONNECTCLIENT_API ~api_client();

            FASTCONNECTCLIENT_API std::string get_access_token(int twoFAType = 0, const std::string &code = "", bool save = false);
            FASTCONNECTCLIENT_API std::string sign(const std::string &data);
            FASTCONNECTCLIENT_API std::string new_order(const std::string& data);

        private:
            std::string m_url;
            std::string m_id;
            std::string m_secret;
            std::string m_private_key;
            RSA *m_rsa;
            std::string m_access_token; //TODO: need re-login after expired

            api_client(const std::string &url, const std::string &id, const std::string &secret, const std::string &private_key);
            std::string post(const std::string& url, const std::string& path, const std::string& body);
        };
    }
}