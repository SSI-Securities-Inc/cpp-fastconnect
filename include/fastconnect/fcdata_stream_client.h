#include "_exports.h"
#include <string>
#include <functional>
#include <memory>
#include "fcdata_api_client.h"
#include "signalrclient/hub_connection.h"
namespace fastconnect
{
    namespace fcdata
    {
        class stream_client
        {
        public:
            FASTCONNECTCLIENT_API static stream_client create(const std::string &stream_url, std::shared_ptr< api_client > client);
             
            FASTCONNECTCLIENT_API ~stream_client();

            FASTCONNECTCLIENT_API void subscribe(const std::string& channel, std::function<void(const std::string &)> callback);
            FASTCONNECTCLIENT_API void start();
           

        private:
            std::string m_url;
            std::shared_ptr< api_client > m_client;
            std::function<void(const std::string &)> m_callback = nullptr;
            std::shared_ptr< signalr::hub_connection> m_connection;
            std::shared_ptr< signalr::hub_proxy> m_proxy;
            std::string m_channel;
            stream_client(const std::string &url, std::shared_ptr< api_client > client);
        };
    }
}