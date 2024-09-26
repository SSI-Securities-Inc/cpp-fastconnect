// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

#include "stdafx.h"
#include "handshake_protocol.h"
#include "json_helpers.h"
#include "signalrclient/signalr_exception.h"
#include "json.hpp"

namespace signalr
{
    namespace handshake
    {
        std::string write_handshake(const std::unique_ptr<hub_protocol>& protocol)
        {
            auto map = std::map<std::string, signalr::value>
            {
                { "protocol", signalr::value(protocol->name()) },
                { "version", signalr::value((double)protocol->version()) }
            };
            nlohmann::json j;
            j["protocol"] = protocol->name();
            j["version"] = protocol->version();
            return j.dump() + record_separator;
        }

        std::tuple<std::string, signalr::value> parse_handshake(const std::string& response)
        {
            auto pos = response.find(record_separator);
            if (pos == std::string::npos)
            {
                throw signalr_exception("incomplete message received");
            }
            auto message = response.substr(0, pos);
            nlohmann::json j = nlohmann::json::parse(message);
            auto remaining_data = response.substr(pos + 1);
            return std::forward_as_tuple(remaining_data, createValue(j));
        }
    }
}