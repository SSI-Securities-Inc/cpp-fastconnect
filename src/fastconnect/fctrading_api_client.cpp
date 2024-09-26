#include "fastconnect/fctrading_api_client.h"
#include "fastconnect/http_client.h"

namespace fastconnect::fctrading
{
    api_client api_client::create(const std::string &url, const std::string &id, const std::string &secret, std::function<std::shared_ptr<http_client>(const fastconnect_client_config &)> http_client_factory)
    {
#ifndef USE_CPPRESTSDK
        if (http_client_factory == nullptr)
        {
            throw std::runtime_error("An http client must be provided");
        }
#endif
        return api_client(url, id, secret, http_client_factory);
    }
    api_client::api_client(const std::string &url, const std::string &id, const std::string &secret, std::function<std::shared_ptr<http_client>(const fastconnect_client_config &)> http_client_factory)
        : m_url(url), m_id(id), m_secret(secret)
    {
        if (http_client_factory != nullptr)
        {
            m_http_client_factory = std::move(http_client_factory);
        }
        else
        {
#ifdef USE_CPPRESTSDK
            m_http_client_factory = [](const fastconnect_client_config& fastconnect_client_config) { return std::unique_ptr<class http_client>(new default_http_client(fastconnect_client_config)); };
#endif
        }
    }

    api_client::~api_client()
    {
    }

    std::string api_client::get_access_token()
    {
        auto http_client = m_http_client_factory(fastconnect_client_config());
        http_request request;
        request.method = http_method::POST;
        http_client.send(m_url, request, [](const http_response& response, std::exception_ptr ex)
        {
            if (ex != nullptr)
            {
                std::rethrow_exception(ex);
            }
            if (response.status_code != 200)
            {
                throw std::runtime_error("Failed to get access token");
            }
        }, cancellation_token())
    }
}