#include "fastconnect/fctrading_stream_client.h"
// #include "signalrclient/hub_connection.h"
#include "signalrclient/hub_connection.h"
#include "cpprest/http_client.h"


namespace fastconnect
{
    namespace fctrading
    {
        stream_client stream_client::create(const std::string &stream_url, std::shared_ptr< api_client > client)
        {
            return stream_client(stream_url, client);
        }
        stream_client::stream_client(const std::string &url, std::shared_ptr< api_client > client)
            : m_url(url)
        {
            m_client = client; 
        }

        stream_client::~stream_client()
        {
        }
        void stream_client::start()
        {
            
            web::http::uri_builder builder(utility::conversions::to_string_t(m_url));
            builder.append_path(U("/v2.0/signalr"));
            auto url = utility::conversions::to_utf8string(builder.to_string());
            std::cout << "stream_url: " << url << std::endl;


            m_connection = std::make_shared<signalr::hub_connection>( utility::conversions::to_string_t(url), U(""), signalr::trace_level::info, nullptr, false);
            auto client_config = signalr::signalr_client_config();
            auto http_header = web::http::http_headers();
            http_header.add(U("Authorization"), U("Bearer " + utility::conversions::to_string_t(m_client->get_access_token())));
            http_header.add(U("NotifyID"), utility::conversions::to_string_t(std::to_string(m_last_id)));
            client_config.set_http_headers(http_header);

            m_connection->set_client_config(client_config);
            m_proxy = std::make_shared<signalr::hub_proxy>(m_connection->create_hub_proxy(U("BroadcastHubV2")));
           
            
            m_proxy->on(U("Broadcast"), [this](const web::json::value &m)
                          {
                                 if(m_callback != nullptr)
                                    m_callback(utility::conversions::to_utf8string(m.at(0).as_string()));
                              });
            m_connection->start().wait();
        }
        void stream_client::subscribe(long last_id, std::function<void(const std::string &)> callback){
            m_last_id = last_id;
            m_callback = callback;
        }
    }
}