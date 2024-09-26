// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

#include "stdafx.h"
#include "json_helpers.h"
#include <cmath>
#include <stdint.h>

namespace signalr
{
    char record_separator = '\x1e';

    
    signalr::value createValue(const nlohmann::json& v)
    {
        
        switch (v.type())
        {
        case nlohmann::json::value_t::boolean:
            return signalr::value(v.get<bool>());
        case nlohmann::json::value_t::number_unsigned:
        case nlohmann::json::value_t::number_float:
        case nlohmann::json::value_t::number_integer:
            return signalr::value(v.get<double>());
        case nlohmann::json::value_t::string:
            return signalr::value(v.get<std::string>());
        case nlohmann::json::value_t::array:
        {
            std::vector<signalr::value> vec;
            for (auto& val : v)
            {
                vec.push_back(createValue(val));
            }
            return signalr::value(std::move(vec));
        }
        case nlohmann::json::value_t::object:
        {
            std::map<std::string, signalr::value> map;
            for (const auto& val : v.items())
            {
                map.insert({ val.key(), createValue(val.value()) });
            }
            return signalr::value(std::move(map));
        }
        case nlohmann::json::value_t::null:
        default:
            return signalr::value();
        }
    }

    char getBase64Value(uint32_t i)
    {
        char index = (char)i;
        if (index < 26)
        {
            return 'A' + index;
        }
        if (index < 52)
        {
            return 'a' + (index - 26);
        }
        if (index < 62)
        {
            return '0' + (index - 52);
        }
        if (index == 62)
        {
            return '+';
        }
        if (index == 63)
        {
            return '/';
        }

        throw std::out_of_range("base64 table index out of range: " + std::to_string(index));
    }

    std::string base64Encode(const std::vector<uint8_t>& data)
    {
        std::string base64result;

        size_t i = 0;
        while (i <= data.size() - 3)
        {
            uint32_t b = ((uint32_t)data[i] << 16) | ((uint32_t)data[i + 1] << 8) | (uint32_t)data[i + 2];
            base64result.push_back(getBase64Value((b >> 18) & 0x3F));
            base64result.push_back(getBase64Value((b >> 12) & 0x3F));
            base64result.push_back(getBase64Value((b >> 6) & 0x3F));
            base64result.push_back(getBase64Value(b & 0x3F));

            i += 3;
        }
        if (data.size() - i == 2)
        {
            uint32_t b = ((uint32_t)data[i] << 8) | (uint32_t)data[i + 1];
            base64result.push_back(getBase64Value((b >> 10) & 0x3F));
            base64result.push_back(getBase64Value((b >> 4) & 0x3F));
            base64result.push_back(getBase64Value((b << 2) & 0x3F));
            base64result.push_back('=');
        }
        else if (data.size() - i == 1)
        {
            uint32_t b = (uint32_t)data[i];
            base64result.push_back(getBase64Value((b >> 2) & 0x3F));
            base64result.push_back(getBase64Value((b << 4) & 0x3F));
            base64result.push_back('=');
            base64result.push_back('=');
        }

        return base64result;
    }

    nlohmann::json createJson(const signalr::value& v)
    {
        switch (v.type())
        {
        case signalr::value_type::boolean:
            return nlohmann::json(v.as_bool());
        case signalr::value_type::float64:
        {
            auto value = v.as_double();
            double intPart;
            // Workaround for 1.0 being output as 1.0 instead of 1
            // because the server expects certain values to be 1 instead of 1.0 (like protocol version)
            if (std::modf(value, &intPart) == 0)
            {
                if (value < 0)
                {
                    if (value >= (double)INT64_MIN)
                    {
                        // Fits within int64_t
                        return nlohmann::json(static_cast<int64_t>(intPart));
                    }
                    else
                    {
                        // Remain as double
                        return nlohmann::json(value);
                    }
                }
                else
                {
                    if (value <= (double)UINT64_MAX)
                    {
                        // Fits within uint64_t
                        return nlohmann::json(static_cast<uint64_t>(intPart));
                    }
                    else
                    {
                        // Remain as double
                        return nlohmann::json(value);
                    }
                }
            }
            return nlohmann::json(v.as_double());
        }
        case signalr::value_type::string:
            return nlohmann::json(v.as_string());
        case signalr::value_type::array:
        {
            const auto& array = v.as_array();
            nlohmann::json vec = nlohmann::json::array();
            for (auto& val : array)
            {
                vec.push_back(createJson(val));
            }
            return vec;
        }
        case signalr::value_type::map:
        {
            const auto& obj = v.as_map();
            nlohmann::json object = nlohmann::json::object();
            for (auto& val : obj)
            {
                object[val.first] = createJson(val.second);
            }
            return object;
        }
        case signalr::value_type::binary:
        {
            const auto& binary = v.as_binary();
            return nlohmann::json(base64Encode(binary));
        }
        case signalr::value_type::null:
        default:
            return nlohmann::json();
        }
    }

    
}