// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

#include "stdafx.h"
#include "negotiate.h"
#include "url_builder.h"
#include "signalrclient/signalr_exception.h"
#include "json_helpers.h"
#include "cancellation_token_source.h"
#include "constants.h"
#include "json.hpp"

namespace signalr
{
    namespace negotiate
    {
        const int negotiate_version = 1;

        void negotiate(std::shared_ptr<http_client> client, const std::string& base_url, const std::string& connection_data,
            const signalr_client_config& config,
            std::function<void(negotiation_response&&, std::exception_ptr)> callback, cancellation_token token) noexcept
        {
            std::string negotiate_url;
            try
            {
                negotiate_url = url_builder::build_negotiate(base_url);
                //negotiate_url = url_builder::add_query_string(negotiate_url, "negotiateVersion=" + std::to_string(negotiate_version));
                negotiate_url = url_builder::add_query_string(negotiate_url, connection_data);
                negotiate_url = url_builder::add_query_string(negotiate_url, "clientProtocol=1.4");
            }
            catch (...)
            {
                callback({}, std::current_exception());
                return;
            }

            // TODO: signalr_client_config
            http_request request;
            request.method = http_method::GET;
            request.headers = config.get_http_headers();
#ifdef USE_CPPRESTSDK
            request.timeout = config.get_http_client_config().timeout();
#endif

            client->send(negotiate_url, request, [callback, token](const http_response& http_response, std::exception_ptr exception)
            {
                if (exception != nullptr)
                {
                    callback({}, exception);
                    return;
                }

                if (token.is_canceled())
                {
                    callback({}, std::make_exception_ptr(canceled_exception()));
                    return;
                }

                if (http_response.status_code != 200)
                {
                    callback({}, std::make_exception_ptr(
                        signalr_exception("negotiate failed with status code " + std::to_string(http_response.status_code))));
                    return;
                }

                try
                {
                    nlohmann::json negotiation_response_json = nlohmann::json::parse(http_response.content);
                    

                    negotiation_response response;

                    if (negotiation_response_json.contains("error"))
                    {
                        response.error = negotiation_response_json["error"].get<std::string>();
                        callback(std::move(response), nullptr);
                        return;
                    }

                    // int server_negotiate_version = 0;
                    // if (negotiation_response_json.isMember("negotiateVersion"))
                    // {
                    //     server_negotiate_version = negotiation_response_json["negotiateVersion"].asInt();
                    // }

                    if (negotiation_response_json.contains("ConnectionId"))
                    {
                        response.connectionId = negotiation_response_json["ConnectionId"].get<std::string>();
                    }

                    if (negotiation_response_json.contains("ConnectionToken"))
                    {
                        response.connectionToken = negotiation_response_json["ConnectionToken"].get<std::string>();
                    }

                    // if (server_negotiate_version <= 0)
                    // {
                    //     response.connectionToken = response.connectionId;
                    // }

                    // if (negotiation_response_json.isMember("availableTransports"))
                    // {
                    //     for (const auto& transportData : negotiation_response_json["availableTransports"])
                    //     {
                    //         available_transport transport;
                    //         transport.transport = transportData["transport"].asString();

                    //         for (const auto& format : transportData["transferFormats"])
                    //         {
                    //             transport.transfer_formats.push_back(format.asString());
                    //         }

                    //         response.availableTransports.push_back(transport);
                    //     }
                    // }

                    // if (negotiation_response_json.isMember("url"))
                    // {
                    //     response.url = negotiation_response_json["url"].asString();

                    //     if (negotiation_response_json.isMember("accessToken"))
                    //     {
                    //         response.accessToken = negotiation_response_json["accessToken"].asString();
                    //     }
                    // }

                    callback(std::move(response), nullptr);
                }
                catch (...)
                {
                    callback({}, std::current_exception());
                }
            }, token);
        }
    }
}
