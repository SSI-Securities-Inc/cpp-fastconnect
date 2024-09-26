#include "_exports.h"
#include <string>
#include <functional>
#include "fastconnect_client_config.h"
#include "http_client.h"
namespace fastconnect
{
    namespace fctrading
    {
        class api_client
        {
        public:
            FASTCONNECTCLIENT_API static api_client create(const std::string &url, const std::string &id, const std::string &secret,
             std::function<std::shared_ptr<http_client>(const fastconnect_client_config &)> http_client_factory);
             
            FASTCONNECTCLIENT_API ~api_client();

            FASTCONNECTCLIENT_API std::string get_access_token();

        private:
            std::string m_url;
            std::string m_id;
            std::string m_secret;

            std::function<std::shared_ptr<http_client>(const fastconnect_client_config &)> m_http_client_factory;
            api_client(const std::string &url, const std::string &id, const std::string &secret,
             std::function<std::shared_ptr<http_client>(const fastconnect_client_config &)> http_client_factory = nullptr);
        };
    }
}