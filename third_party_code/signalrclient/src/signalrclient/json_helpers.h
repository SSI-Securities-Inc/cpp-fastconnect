// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

#pragma once

#include "signalrclient/signalr_value.h"
#include <memory>
#include "json.hpp"

namespace signalr
{
    extern char record_separator;

    signalr::value createValue(const nlohmann::json& v);

    nlohmann::json createJson(const signalr::value& v);

    std::string base64Encode(const std::vector<uint8_t>& data);
}