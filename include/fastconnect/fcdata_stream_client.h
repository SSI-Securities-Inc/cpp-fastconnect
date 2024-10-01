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
            /// @brief Create stream client
            /// @param stream_url Streaming url we provide at https://guide.ssi.com.vn/ssi-products/fastconnect-data/connection-guide
            /// @param client API client to authenticate and authorize with server
            /// @return Streaming client
            FASTCONNECTCLIENT_API static stream_client create(const std::string &stream_url, std::shared_ptr< api_client > client);
             
            FASTCONNECTCLIENT_API ~stream_client();
            /// @brief Subcrible to channel realtime
            /// @param channel with partern X:ALL, F:SSI-PAN ... more at https://guide.ssi.com.vn/ssi-products/fastconnect-data/streaming-data
            /// @param callback fuction to receive data from stream
            /// @return 
            FASTCONNECTCLIENT_API void subscribe(const std::string& channel, std::function<void(const std::string &)> callback);
            /// @brief start listen to stream
            /// @return 
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